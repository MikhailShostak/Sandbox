#pragma once

template <typename RepresentationType, typename Period>
using Duration = std::chrono::duration<RepresentationType, Period>;

using Nanoseconds = std::chrono::nanoseconds;
using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Seconds = std::chrono::seconds;
using Minutes = std::chrono::minutes;
using Hours = std::chrono::hours;
#if __cplusplus > 202000
using Days = std::chrono::days;
using Weeks = std::chrono::weeks;
using Months = std::chrono::months;
using Years = std::chrono::years;
#endif

using NanosecondRatio = std::chrono::duration<float, Nanoseconds::period>;
using MicrosecondRatio = std::chrono::duration<float, Microseconds::period>;
using MillisecondRatio = std::chrono::duration<float, Milliseconds::period>;
using SecondRatio = std::chrono::duration<float, Seconds::period>;
using MinuteRatio = std::chrono::duration<float, Minutes::period>;
using HourRatio = std::chrono::duration<float, Hours::period>;
#if __cplusplus > 202000
using DayRatio = std::chrono::duration<float, Days::period>;
using WeekRatio = std::chrono::duration<float, Weeks::period>;
using MonthRatio = std::chrono::duration<float, Months::period>;
using YearRatio = std::chrono::duration<float, Years::period>;
#endif
