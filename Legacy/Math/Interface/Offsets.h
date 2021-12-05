#pragma once

#include <stdint.h>
#include "Vector.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Offsets
{
    union
    {
        struct
        {
            Type top;
            Type right;
            Type bottom;
            Type left;
        };
        struct
        {
            Type Top;
            Type Right;
            Type Bottom;
            Type Left;
        };
    };

    Offsets getHalfOffsets() const
    {
        return {
            top / Type(2),
            right / Type(2),
            bottom / Type(2),
            left / Type(2),
        };
    }

    Type getHorizontalSpace() const { return left + right; }
    Type getVerticalSpace() const { return top + bottom; }
    Vector<Type> getSpace() const { return { getHorizontalSpace(), getVerticalSpace() }; }
};

}

using FloatOffsets = Templates::Offsets<float>;
using DoubleOffsets = Templates::Offsets<double>;
using IntegerOffsets = Templates::Offsets<int32_t>;
using Offsets = IntegerOffsets; //TODO: should be replaced with Templates::Offsets<FloatType>;

}

using UIOffsets = Math::IntegerOffsets;
