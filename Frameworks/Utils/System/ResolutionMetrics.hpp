#pragma once

namespace System
{

template<typename Representation, typename Period>
struct ResolutionMetric
{
    using RepresentationType = Representation;
    using PeriodType = Period;

    ResolutionMetric(const RepresentationType& value) :
        m_Value(value)
    {

    }

    template<typename OtherRepresentationType, typename OtherPeriodType>
    ResolutionMetric(const ResolutionMetric<OtherRepresentationType, OtherPeriodType>& metric) :
        m_Value(metric.Count()* Ratio::DividedValue<OtherPeriodType, PeriodType>)
    {

    }

    [[nodiscard]] RepresentationType Count() const noexcept
    {
        return m_Value;
    }

    operator RepresentationType() const noexcept { return Count(); }

private:
    RepresentationType m_Value;
};

namespace Details
{

inline constexpr std::intmax_t DefaultPrintingDPI = 72;
inline constexpr std::intmax_t DefaultScreenPPI = 96;

template<typename Type, std::intmax_t DPI = DefaultPrintingDPI>
using point_t = ResolutionMetric<Type, Ratio::Number<1, DPI>>;
template<typename Type, std::intmax_t PPI = DefaultScreenPPI>
using pixel_t = ResolutionMetric<Type, Ratio::Number<1, PPI>>;

}

template<typename Type, std::intmax_t DPI = Details::DefaultPrintingDPI>
inline auto ToPoints(const Type &Pixels)
{
    return Details::point_t<typename Type::RepresentationType, DPI>(Pixels);
}

template<typename Type, std::intmax_t PPI = Details::DefaultScreenPPI>
inline auto ToPixels(const Type &Points)
{
    return Details::pixel_t<typename Type::RepresentationType, PPI>(Points);
}

}

using ipoint_t = System::Details::point_t<std::intmax_t>;
using fpoint_t = System::Details::point_t<float>;
using point_t = System::Details::point_t<double>;

using ipixel_t = System::Details::pixel_t<std::intmax_t>;
using fpixel_t = System::Details::pixel_t<float>;
using pixel_t = System::Details::pixel_t<double>;

inline ipoint_t operator "" _pt(unsigned long long value) { return value; }
inline ipixel_t operator "" _px(unsigned long long value) { return value; }

inline point_t operator "" _pt(long double value) { return value; }
inline pixel_t operator "" _px(long double value) { return value; }
