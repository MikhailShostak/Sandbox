#pragma once

#include "DateTime/Duration.hpp"
#include "DateTime/Time.hpp"

namespace Multithreading
{

using Thread = std::thread;
using ThreadID = std::thread::id;

inline ThreadID GetThreadID()
{
    return std::this_thread::get_id();
}

inline void Sleep(const DateTime::Unix::Timestamp &timestamp)
{
    std::this_thread::sleep_until(DateTime::Unix::GetTime(timestamp));
}

template <typename Clock, typename Duration>
inline void Sleep(const DateTime::Templates::Time<Clock, Duration> &time)
{
    std::this_thread::sleep_until(time);
}

template <typename Type, typename Period>
inline void Sleep(const DateTime::Templates::Duration<Type, Period> &duration)
{
    std::this_thread::sleep_for(duration);
}

inline void Sleep(DateTime::Milliseconds::rep milliseconds)
{
    std::this_thread::sleep_for(DateTime::Milliseconds(milliseconds));
}

inline void Sleep(DateTime::SecondRatio::rep seconds)
{
    std::this_thread::sleep_for(DateTime::SecondRatio(seconds));
}

}
