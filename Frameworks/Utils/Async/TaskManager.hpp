#pragma once

#include "Memory/References.hpp"

#include "Multithreading/SafeQueue.hpp"
#include "Multithreading/ThreadPool.hpp"

#include "Debug/DebugUtils.hpp"
#include "Debug/Profiler.hpp"

template<typename Type>
void Remove(Array<Type> &container, size_t index)
{
    size_t lastIndex = container.size() - 1;
    if (index != lastIndex)
    {
        container[index] = std::move(container[lastIndex]);
    }
    container.resize(container.size() - 1);
}

template<typename Type>
Type Pop(Array<Type> &container, size_t index)
{
    Type element = std::move(container[index]);
    Remove(container, index);
    return std::move(element);
}

struct TaskManager
{
    struct TaskThreadState : public Multithreading::ThreadState
    {
        Multithreading::Mutex m_Mutex;
        Array<UniqueReference<Task>> m_Tasks;

        TaskThreadState()
        {
            m_Tasks.reserve(64);
        }
    };

    Multithreading::ThreadPool<TaskThreadState> m_AsyncWorkers;
    Array<UniqueReference<Task>> m_Tasks;
    Multithreading::Mutex m_Mutex;

    size_t m_TaskBatchSize = 1;
    size_t m_NextAsyncWorker = 0;
    bool m_IsRunning = true;

    void PushAsyncTask(std::function<void()> &&functor)
    {
        {
            Multithreading::MutexLock lock{ m_AsyncWorkers.m_ThreadStates[m_NextAsyncWorker].m_Mutex };
            m_AsyncWorkers.m_ThreadStates[m_NextAsyncWorker].m_Tasks.push_back(std::make_unique<Task>(std::move(functor)));
        }
        m_AsyncWorkers.Notify(m_NextAsyncWorker);
        m_NextAsyncWorker = (m_NextAsyncWorker + 1) % m_AsyncWorkers.m_ThreadStates.size();
    }

    void PushAsyncTask(size_t count, const std::function<void(size_t index)> &functor)
    {
        for (auto &state : m_AsyncWorkers.m_ThreadStates)
        {
            state.m_Mutex.lock();
        }
        for (size_t i = 0; i < count; ++i)
        {
            m_AsyncWorkers.m_ThreadStates[m_NextAsyncWorker].m_Tasks.push_back(std::make_unique<Task>(std::bind(functor, i)));
            m_AsyncWorkers.Notify(m_NextAsyncWorker);
            m_NextAsyncWorker = (m_NextAsyncWorker + 1) % m_AsyncWorkers.m_ThreadStates.size();
        }
        for (auto &state : m_AsyncWorkers.m_ThreadStates)
        {
            state.m_Mutex.unlock();
        }
    }

    TaskManager() :
        m_AsyncWorkers(std::bind(&TaskManager::ExecuteAsyncTask, this, std::placeholders::_1))
    {
        m_Tasks.reserve(1024 * 100);
        m_AsyncWorkers.Start();
    }

    ~TaskManager()
    {
        Clear();
    }

    void Clear()
    {
        m_AsyncWorkers.Clear();
    }

    void Run()
    {
        while (m_IsRunning)
        {
            Process();
        }
    }

    void Process()
    {
        for (size_t i = 0; i < m_TaskBatchSize; ++i)
        {
            ExecuteMainTask();
        }
    }

    void Dispatch(const std::function<void()> &task)
    {
        Multithreading::MutexLock lock{ m_Mutex };
        m_Tasks.emplace_back(std::make_unique<Task>(task));
    }

    void Dispatch(std::function<void()> &&task)
    {
        Multithreading::MutexLock lock{ m_Mutex };
        m_Tasks.emplace_back(std::make_unique<Task>(std::move(task)));
    }

    template<typename Functor>
    auto AwaitAsync(const Functor &functor) -> std::invoke_result_t<Functor>
    {
        std::invoke_result_t<Functor> result;
        Task *task = Task::GetCurrentTask();
        task->Await();
        PushAsyncTask([&functor, &result, &task]() {
            result = functor();
            task->Resume();
        });
        Task::Suspend();
        return result;
    }

    template<typename CoroutineType>
    struct ForEachWrapper //TODO: Remove after updating on boost 1.78.0
    {
        CoroutineType coroutine;
        auto begin() { return std::begin(coroutine); }
        auto end() { return std::end(coroutine); }
    };

    template<typename Functor>
    auto AwaitAsync(const std::vector<Functor> &functors)
    {
        using FunctorType = std::function<size_t(size_t)>;
        using ResultType = std::invoke_result_t<FunctorType, size_t>;
        constexpr static bool HasResult = !std::is_same_v<ResultType, void>;
        using CoroutineResultType = std::conditional_t<HasResult, std::pair<size_t, ResultType>, size_t>;
        using TaskCoroutine = boost::coroutines2::coroutine<CoroutineResultType>;
        using PullCoroutineType = typename TaskCoroutine::pull_type;
        using PushCoroutineType = typename TaskCoroutine::push_type;

        PullCoroutineType coroutine{ [this, &functors] (PushCoroutineType &context) {
            size_t done = 0;

            Task *task = Task::GetCurrentTask();
            task->Await();

            PushAsyncTask(functors.size(), [this, &done, &task, &context, &functors](size_t i) {
                auto result = [&]()
                {
                    Debug::ProfilerScopeRecord r{ "{}", typeid(Functor).name() };
                    if constexpr (HasResult)
                    {
                        CoroutineResultType result = { i, functors[i](i) };
                        return result;
                    }
                    else
                    {
                        functors[i](i);
                        return i;
                    }
                }();
                
                Dispatch([&, result = std::move(result)]()
                {
                    context(result);
                    ++done;
                    if (done == functors.size())
                    {
                        task->Resume();
                    }
                });
            });

            Task::Suspend();

        } };

        return ForEachWrapper<PullCoroutineType>{ std::move(coroutine) };
    }

protected:
    void ExecuteTask(Array<UniqueReference<Task>> &tasks, Multithreading::Mutex &mutex)
    {
        mutex.lock();
        if (tasks.empty())
        {
            mutex.unlock();
            return;
        }

        auto task = Pop(tasks, 0);

        if (task->IsAwaiting())
        {
            tasks.push_back(std::move(task));
            mutex.unlock();
        }
        else
        {
            mutex.unlock();
            task->Execute();
            if (!task->IsFinished())
            {
                mutex.lock();
                tasks.push_back(std::move(task));
                mutex.unlock();
            }
        }
    }

    void ExecuteMainTask() {
        ExecuteTask(m_Tasks, m_Mutex);
    }

    void ExecuteAsyncTask(size_t index)
    {
        ExecuteTask(m_AsyncWorkers.m_ThreadStates[index].m_Tasks, m_AsyncWorkers.m_ThreadStates[index].m_Mutex);
    }
};
