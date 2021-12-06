#pragma once

#include <boost/coroutine2/coroutine.hpp>

struct Task
{
public:
    std::function<void()> m_Function;
private:
    using TaskCoroutine = boost::coroutines2::coroutine<Task &>;
    TaskCoroutine::push_type m_Coroutine{ &Task::Main };
    TaskCoroutine::pull_type *m_Context = nullptr;
    bool m_Awaiting = false;
    inline static thread_local Task *m_CurrentTask = nullptr;
public:
    Task(const Task &) = delete;

    Task(Task &&task) = default;// : m_Function(std::move(task.m_Function)), m_Coroutine(std::move(task.m_Coroutine)), m_Context(task.m_Context) {}
    Task &operator =(Task &&task) = default;

    Task(const std::function<void()> &f) : m_Function(f) {}
    Task(std::function<void()> &&f) : m_Function(std::move(f)) {}

    static Task *GetCurrentTask()
    {
        return m_CurrentTask;
    }

    static void Suspend()
    {
        (*m_CurrentTask->m_Context)();
    }

    static void Main(TaskCoroutine::pull_type &context)
    {
        Task &task = context.get();
        task.m_Context = &context;
        task.m_Function();
    }

    bool IsFinished() const
    {
        return bool(!m_Coroutine);
    }

    bool IsAwaiting() const
    {
        return m_Awaiting;
    }

    void Await()
    {
        m_Awaiting = true;
    }

    void Resume()
    {
        m_Awaiting = false;
    }

    void Execute()
    {
        auto task = m_CurrentTask;
        m_CurrentTask = this;
        m_Coroutine(*this);
        m_CurrentTask = task;
    }

    void ExecuteIfNeeded()
    {
        if (!IsFinished())
        {
            Execute();
        }
    }

    void ExecuteUntilFinished()
    {
        while (!IsFinished())
        {
            Execute();
        }
    }
};
