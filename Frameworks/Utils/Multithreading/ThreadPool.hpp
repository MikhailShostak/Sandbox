#pragma once

#include "Containers/Array.hpp"

#include "Multithreading/Thread.hpp"
#include "Multithreading/Synchronization/Semaphore.hpp"

#include "Debug/Profiler.hpp"

namespace Multithreading
{

struct ThreadState
{
    Thread m_Thread;
    Semaphore m_Semaphore;
    bool m_Active = true;
};

template<typename ThreadStateType = ThreadState>
struct ThreadPool
{
    Array<ThreadStateType> m_ThreadStates;
    std::function<void(size_t index)> m_EntryPoint;

    template<typename Functor>
    ThreadPool(Functor &&entryPoint) :
        m_EntryPoint(std::forward<Functor>(entryPoint))
    {

    }

    ~ThreadPool()
    {
        Clear();
    }

    void Notify(size_t index)
    {
        m_ThreadStates[index].m_Semaphore.Release();
    }

    void Start(size_t size = std::thread::hardware_concurrency() * 1)
    {
        Array<ThreadStateType> states(size);
        m_ThreadStates.swap(states);
        for (size_t i = 0; i < m_ThreadStates.size(); ++i)
        {
            fmt::print("Allocate Thread: {}\n", i);
            m_ThreadStates[i].m_Thread = Thread(&ThreadPool::Main, this, i);
        }
    }

    void Restart()
    {
        Clear();
        Start();
    }

    void Clear()
    {
        Stop();
        Join();
        m_ThreadStates.clear();
    }

    void Stop()
    {
        for (size_t i = 0; i < m_ThreadStates.size(); ++i)
        {
            m_ThreadStates[i].m_Active = false;
            m_ThreadStates[i].m_Semaphore.Release();
        }
    }

    void Join()
    {
        for (size_t i = 0; i < m_ThreadStates.size(); ++i)
        {
            fmt::print("Waiting for Thread: {}\n", i);
            m_ThreadStates[i].m_Thread.join();
        }
    }

    void Main(size_t index)
    {
        ThreadState &state = m_ThreadStates[index];
        while (state.m_Active)
        {
            {
                Debug::ProfilerScopeRecord r{ "Wait" };
                state.m_Semaphore.Acquire();
            }
            if (state.m_Active)
            {
                m_EntryPoint(index);
            }
        }
    }
};

}
