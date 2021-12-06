#pragma once

namespace Multithreading
{

using Mutex = std::mutex;
using RecursiveMutex = std::recursive_mutex;
using TimedMutex = std::timed_mutex;
using RecursiveTimedMutex = std::recursive_timed_mutex;

struct ReadWriteMutex
{
    Mutex ReadMutex;
    Mutex WriteMutex;

    void LockForReading()
    {
        WriteMutex.lock();
    }

    bool TryLockForReading()
    {
        return WriteMutex.try_lock();
    }

    void UnlockForReading()
    {
        WriteMutex.unlock();
    }

    void LockForWriting()
    {
        WriteMutex.lock();
        ReadMutex.lock();
    }

    bool TryLockForWriting()
    {
        if (!WriteMutex.try_lock())
        {
            return false;
        }

        if (!ReadMutex.try_lock())
        {
            WriteMutex.unlock();
            return false;
        }

        return true;
    }

    void UnlockForWriting()
    {
        WriteMutex.unlock();
        ReadMutex.unlock();
    }
};

}
