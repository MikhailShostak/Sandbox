#pragma once

#include "Multithreading/Synchronization/Locks.hpp"

namespace Multithreading
{

class Semaphore
{
    Mutex m_Mutex;
    ConditionVariable m_CV;
    size_t m_Count = 0;
public:

    Semaphore(size_t count = 0) :
        m_Count(count)
    {

    }

    size_t GetCount() const
    {
        return m_Count;
    }

    void SetCount(size_t count)
    {
        MutexLock lock{ m_Mutex };
        if (m_Count > count)
        {
            size_t diff = m_Count - count;
            for (size_t i = 0; i < diff; ++i)
            {
                ++m_Count;
                m_CV.notify_one();
            }
        }
        else
        {
            m_Count = count;
        }
    }

    void Acquire()
    {
        UniqueMutexLock lock{ m_Mutex };
        m_CV.wait(lock, [&]() { return m_Count > 0; });
        --m_Count;
    }

    void Release(size_t count = 1)
    {
        MutexLock lock{ m_Mutex };
        for (size_t i = 0; i < count; ++i)
        {
            ++m_Count;
            m_CV.notify_one();
        }
    }
};

}
