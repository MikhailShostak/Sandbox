#pragma once

template<typename ClockType>
class Stopwatch
{
public:
    using Clock = ClockType;
    using Time = typename Clock::duration;
    using Duration = typename Clock::time_point;

    [[nodiscard]] const Time &GetStartTime() const noexcept { return m_Time; }
    [[nodiscard]] Time GetCurrentTime() const noexcept { return Clock::now(); }
    [[nodiscard]] Duration GetLapTime() noexcept { return m_Counter.GetTotalTime(); }
    [[nodiscard]] Duration GetTotalTime() noexcept { return GetCurrentTime() - GetStartTime(); }

    [[nodiscard]] bool IsStarted() const noexcept { return GetStartTime() != nullptr; }

    void Start() noexcept
    {
        m_Counter.Start();
        m_Time = m_Counter.GetStartTime();
    }
    void Reset() noexcept
    {
        m_Counter.Reset();
        m_Time = {};
    }

    [[nodiscard]] Duration Lap() noexcept { return m_Counter.Count(); }

    template<typename DurationType>
    [[nodiscard]] auto LapAs() noexcept
    {
        return std::chrono::duration_cast<DurationType>(Lap());
    }

    template<typename DurationType>
    [[nodiscard]] auto LapValueAs() noexcept
    {
        return std::chrono::duration_cast<DurationType>(Lap()).count();
    }

private:

    Counter<Clock> m_Counter{};
    Time m_Time{};
};
