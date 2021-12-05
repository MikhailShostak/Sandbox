#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

#include "ATime.h"

using AMutex = std::mutex;
using ARecursiveMutex = std::recursive_mutex;
using ATimedMutex = std::timed_mutex;
using ARecursiveTimedMutex = std::recursive_timed_mutex;

using AWaitCondition = std::condition_variable;
using AVariantWaitCondition = std::condition_variable_any;

using AThreadId = std::thread::id;

template <typename Mutex>
using ALock = std::lock_guard<Mutex>;
using AMutexLock = ALock<AMutex>;
using ARecursiveMutexLock = ALock<ARecursiveMutex>;
using ATimedMutexLock = ALock<ATimedMutex>;
using ARecursiveTimedMutexLock = ALock<ARecursiveTimedMutex>;

template <typename Mutex>
using AUniqueLock = std::unique_lock<Mutex>;
using AUniqueMutexLock = AUniqueLock<AMutex>;
using AUniqueRecursiveMutexLock = AUniqueLock<ARecursiveMutex>;
using AUniqueTimedMutexLock = AUniqueLock<ATimedMutex>;
using AUniqueRecursiveTimedMutexLock = AUniqueLock<ARecursiveTimedMutex>;

class AThread final
{

    std::thread handle;

public:

    static void sleep(uint64_t milliseconds)
    {
        std::this_thread::sleep_for(AMilliseconds(milliseconds));
    }

    template <typename Type, typename Period>
    static void sleep(const ADuration<Type, Period> &duration)
    {
        std::this_thread::sleep_for(duration);
    }

    template <typename Duration>
    static void sleepUntil(const ATimePoint<ASteadyClock, Duration> &point)
    {
        std::this_thread::sleep_until(point);
    }

    template <typename Clock, typename Duration>
    static void sleepUntil(const ATimePoint<Clock, Duration> &point)
    {
        std::this_thread::sleep_until(point);
    }

    static void yield()
    {
        std::this_thread::yield();
    }

    static AThreadId currentThreadId()
    {
        return std::this_thread::get_id();
    }

    template<typename FirstMutex, typename SecondMutex>
    static void lock(FirstMutex &firstMutex, SecondMutex &secondMutex)
    {
        std::lock(firstMutex, secondMutex);
    }

    AThread() {}
    AThread(const AThread &thread) = delete;
    AThread(AThread &&thread):handle(std::move(thread.handle)) {}
    template<class Function, class ...Arguments>
    explicit AThread(Function function, Arguments ...arguments): handle(function, arguments...) {}

    AThread &operator =(AThread &&thread)
    {
        handle = std::move(thread.handle);
        return *this;
    }

    AThreadId id() const
    {
        return handle.get_id();
    }

    bool isJoinable() const
    {
        return handle.joinable();
    }

    void join()
    {
        handle.join();
    }

    void detach()
    {
        handle.detach();
    }

    void swap(AThread &thread)
    {
        handle.swap(thread.handle);
    }

};

class ASemaphore {

    uint32_t count = 0;
    AMutex mutex;
    AWaitCondition condition;

public:

    ASemaphore(uint32_t count = 0): count(count) {}

    uint32_t getCount() const
    {
        return count;
    }

    void lock()
    {
        AUniqueLock<std::mutex> lock(mutex);
        while(count == 0)
        {
            condition.wait(lock);
        }
        --count;
    }

    bool tryLock()
    {
        ALock<std::mutex> lock(mutex);
        if(count == 1)
        {
            --count;
            return true;
        }
        else
        {
            return false;
        }
    }

    void unlock()
    {
        ALock<std::mutex> lock(mutex);
        ++count;
        condition.notify_one();
    }

};
