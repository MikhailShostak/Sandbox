#pragma once

template<typename Clock, typename Duration = typename Clock::duration>
using Time = std::chrono::time_point<Clock, Duration>;

namespace System
{
using Clock = std::chrono::system_clock;
using Time = ::Time<Clock>;
}

namespace Steady
{
using Clock = std::chrono::steady_clock;
using Time = ::Time<Clock>;
}

namespace HighResolution
{
using Clock = std::chrono::high_resolution_clock;
using Time = ::Time<Clock>;
}

#if __cplusplus > 202000
namespace UTC
{
using Clock = std::chrono::utc_clock;
using Time = ::Time<Clock>;
}

namespace TAI
{
using Clock = std::chrono::tai_clock;
using Time = ::Time<Clock>;
}

namespace GPS
{
using Clock = std::chrono::gps_clock;
using Time = ::Time<Clock>;
}

namespace File
{
using Clock = std::chrono::file_clock;
using Time = ::Time<Clock>;
}

namespace Local
{
template<typename Duration>
using Time = ::Time<std::chrono::local_t, Duration>;
}
#endif

namespace Unix
{

using Timestamp = std::time_t;

inline Timestamp GetTimestamp(const System::Time &time = System::Clock::now()) noexcept
{
    return System::Clock::to_time_t(time);
}

inline System::Time GetTime(Timestamp time) noexcept
{
    return System::Clock::from_time_t(time);
}

}

template<typename Clock, typename Duration = typename Clock::duration>
inline bool operator ==(const Time<Clock, Duration> &time, std::nullptr_t) noexcept
{
    return time == Time<Clock, Duration>{};
}
