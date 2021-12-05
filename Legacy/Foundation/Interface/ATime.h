#pragma once

#include <chrono>

using ATime = time_t;

template <typename Type, typename Period>
using ADuration = std::chrono::duration<Type, Period>;
using ANanoseconds = std::chrono::nanoseconds;
using AMicroseconds = std::chrono::microseconds;
using AMilliseconds = std::chrono::milliseconds;
using ASeconds = std::chrono::seconds;
using AMinutes = std::chrono::minutes;
using AHours = std::chrono::hours;

using ASystemClock = std::chrono::system_clock;
using ASteadyClock = std::chrono::steady_clock;

template <class Clock, class Duration = typename Clock::duration>
using ATimePoint = std::chrono::time_point<Clock, Duration>;
