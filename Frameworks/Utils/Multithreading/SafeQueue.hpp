#pragma once

#include "Containers/Queue.hpp"

#include "Multithreading/Synchronization/Locks.hpp"

namespace Multithreading
{

template<typename Type, typename MutexType = RecursiveMutex>
struct SafeQueue
{
    void Push(const Type &value)
    {
        Lock<MutexType> lock{ m_Mutex };
        m_Queue.push(value);
    }

    void Push(Type &&value)
    {
        Lock<MutexType> lock{ m_Mutex };
        m_Queue.emplace(std::move(value));
    }

    std::optional<Type> Pop()
    {
        Lock<MutexType> lock{ m_Mutex };
        if (m_Queue.empty())
        {
            return {};
        }

        Type f = std::move(m_Queue.front());
        m_Queue.pop();
        return f;
    }

    template<typename Functor>
    void Pop(Functor &&functor)
    {
        Lock<MutexType> lock{ m_Mutex };
        if (!m_Queue.empty())
        {
            if (functor(std::move(m_Queue.front())))
            {
                m_Queue.pop();
            }
        }
    }
private:
    std::queue<Type> m_Queue;
    MutexType m_Mutex;
};

}
