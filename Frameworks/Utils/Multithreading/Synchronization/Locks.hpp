#pragma once

#include "Multithreading/Synchronization/Mutexes.hpp"

namespace Multithreading
{

using ConditionVariable = std::condition_variable;
using GenericConditionVariable = std::condition_variable_any;

template<typename Mutex>
using Lock = std::lock_guard<Mutex>;
using MutexLock = Lock<Mutex>;
using RecursiveMutexLock = Lock<RecursiveMutex>;
using TimedMutexLock = Lock<TimedMutex>;
using RecursiveTimedMutexLock = Lock<RecursiveTimedMutex>;

template<typename Mutex>
using UniqueLock = std::unique_lock<Mutex>;
using UniqueMutexLock = UniqueLock<Mutex>;
using UniqueRecursiveMutexLock = UniqueLock<RecursiveMutex>;
using UniqueTimedMutexLock = UniqueLock<TimedMutex>;
using UniqueRecursiveTimedMutexLock = UniqueLock<RecursiveTimedMutex>;

struct ReadLock
{
    ReadWriteMutex &m_Mutex;

    ReadLock(ReadWriteMutex &mutex):
        m_Mutex(mutex)
    {
        m_Mutex.LockForReading();
    }

    ~ReadLock()
    {
        m_Mutex.UnlockForReading();
    }
};

struct WriteLock
{
    ReadWriteMutex &m_Mutex;

    WriteLock(ReadWriteMutex &mutex):
        m_Mutex(mutex)
    {
        m_Mutex.LockForWriting();
    }

    ~WriteLock()
    {
        m_Mutex.UnlockForWriting();
    }
};

}
