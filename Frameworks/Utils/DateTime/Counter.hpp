#pragma once

namespace DateTime
{

template<typename ClockType>
class Counter
{
public:

    using Clock = ClockType;
    using Time = typename Clock::time_point;
    using Duration = typename Clock::duration;

    [[nodiscard]] const Time &GetStartTime() const noexcept { return m_Time; }
    [[nodiscard]] Time GetCurrentTime() const noexcept { return Clock::now(); }
    [[nodiscard]] Duration GetTotalTime() noexcept { return GetCurrentTime() - GetStartTime(); }

    [[nodiscard]] bool IsStarted() const noexcept { return GetStartTime() != nullptr; }

    void Start() noexcept { m_Time = GetCurrentTime(); }
    void Reset() noexcept { m_Time = {}; }

    [[nodiscard]] Duration Count() noexcept
    {
        Time previousStartTime = std::move(m_Time);
        Start();
        return GetStartTime() - previousStartTime;
    }

    template<typename DurationType>
    [[nodiscard]] auto CountAs() noexcept
    {
        return std::chrono::duration_cast<DurationType>(Count());
    }

    template<typename DurationType>
    [[nodiscard]] auto CountValueAs() noexcept
    {
        return std::chrono::duration_cast<DurationType>(Count()).count();
    }

private:

    Time m_Time{};
};

}
