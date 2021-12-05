#pragma once

#include "BasicConstants.h"

#include "Vector.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Box
{

    Vector<Type> position;
    Vector<Type> size;

    constexpr Box()
    {

    }

    constexpr explicit Box(Type width, Type height, Type depth):
        size(width, height, depth)
    {

    }

    constexpr explicit Box(Type x, Type y, Type z, Type width, Type height, Type depth):
        position(x, y, z),
        size(width, height, depth)
    {

    }

    /*constexpr explicit Box(const APoint3D<Type> &position):
        position(position)
    {

    }

    constexpr explicit Box(const ASize3D<Type> &size):
        size(size)
    {

    }*/

    constexpr explicit Box(const Vector<Type> &position, const Vector<Type> &size):
        position(position),
        size(size)
    {

    }

};

}
    using FloatBox = Templates::Box<float>;
    using DoubleBox = Templates::Box<double>;
    using IntegerBox = Templates::Box<int32_t>;
#if defined(ADoublePrecision)
    using Box = DoubleBox;
#else
    using Box = FloatBox;
#endif
}
