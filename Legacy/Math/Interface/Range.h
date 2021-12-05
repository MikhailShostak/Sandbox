#pragma once

#include "BasicConstants.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Range
{

    Type lowest;
    Type highest;

    constexpr Range():lowest(), highest() {}

    constexpr explicit Range(const Type &length):lowest(0), highest(length) {}
    constexpr explicit Range(const Type &lowest, const Type &highest):lowest(lowest), highest(highest) {}

    constexpr bool contains(Type value) const { return lowest <= value && value <= highest; }

    constexpr Type getStartOffset(Type value) const { return value - lowest; }
    constexpr Type getEndOffset(Type value) const { return highest - value; }

    constexpr Type getLength() const { return this->highest - this->lowest; }

    constexpr Type interpolate(FloatType position) const { return (this->highest - this->lowest) * position + this->lowest; }
};

}
    
using FloatRange = Templates::Range<float>;
using DoubleRange = Templates::Range<double>;
using IntegerRange = Templates::Range<int32_t>;
using Range = Templates::Range<FloatType>;

}
