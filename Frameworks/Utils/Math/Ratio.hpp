#pragma once

namespace Ratio
{

template<std::intmax_t Numerator, std::intmax_t Denominator = 1>
using Number = std::ratio<Numerator, Denominator>;

template<typename LeftRatioNumberType, typename RightRatioNumberType>
using Add = std::ratio_add<LeftRatioNumberType, RightRatioNumberType>;

template<typename LeftRatioNumberType, typename RightRatioNumberType>
using Subtract = std::ratio_subtract<LeftRatioNumberType, RightRatioNumberType>;

template<typename LeftRatioNumberType, typename RightRatioNumberType>
using Multiply = std::ratio_multiply<LeftRatioNumberType, RightRatioNumberType>;

template<typename LeftRatioNumberType, typename RightRatioNumberType>
using Divide = std::ratio_divide<LeftRatioNumberType, RightRatioNumberType>;

template<typename RatioNumberType>
[[nodiscard]] inline constexpr long double ToDecimal() noexcept
{
    return (long double)(RatioNumberType::num) / (long double)(RatioNumberType::den);
}

template<typename LeftRatioNumberType, typename RightRatioNumberType>
inline constexpr long double AddedValue = ToDecimal<Add<LeftRatioNumberType, RightRatioNumberType>>();

template<typename LeftRatioNumberType, typename RightRatioNumberType>
inline constexpr long double SubtractedValue = ToDecimal<Subtract<LeftRatioNumberType, RightRatioNumberType>>();

template<typename LeftRatioNumberType, typename RightRatioNumberType>
inline constexpr long double MultipliedValue = ToDecimal<Multiply<LeftRatioNumberType, RightRatioNumberType>>();

template<typename LeftRatioNumberType, typename RightRatioNumberType>
inline constexpr long double DividedValue = ToDecimal<Divide<LeftRatioNumberType, RightRatioNumberType>>();

}
