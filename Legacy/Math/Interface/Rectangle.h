#pragma once

#include "BasicConstants.h"
#include "Vector.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Rectangle
{
    union
    {
        Vector<Type> position;
        Vector<Type> Position;
    };

    union
    {
        Vector<Type> size;
        Vector<Type> Size;
    };

    constexpr Rectangle()
    {

    }

    constexpr explicit Rectangle(Type width, Type height):
        size{ width, height }
    {

    }

    constexpr explicit Rectangle(Type x, Type y, Type width, Type height):
        position{ x, y },
        size{ width, height }
    {

    }

    /*constexpr explicit Rectangle(const APoint2D<Type> &position):
        position(position)
    {

    }

    constexpr explicit Rectangle(const ASize2D<Type> &size):
        size(size)
    {

    }*/

    constexpr explicit Rectangle(const Vector<Type> &position, const Vector<Type> &size):
        position(position),
        size(size)
    {

    }

    /*constexpr explicit Rectangle(const APoint2D<Type> &topLeft, const APoint2D<Type> &bottomRight):
        position{ topLeft },
        size{ bottomRight.x - topLeft.x, bottomRight.y - topLeft.y }
    {

    }*/

    constexpr Type getTop() const { return position.y; }
    constexpr void setTop(Type top) { size.y += position.y - top; position.y = top; }
    constexpr Type getRight() const { return position.x + size.x; }
    constexpr void setRight(Type right) { size.x = right - position.x; }
    constexpr Type getBottom() const { return position.y + size.y; }
    constexpr void setBottom(Type bottom) { size.height = bottom - position.y; }
    constexpr Type getLeft() const { return position.x; }
    constexpr void setLeft(Type left) { size.x += position.x - left; position.x = left; }

    constexpr Type getStart(size_t sideIndex) const { return position[sideIndex]; }
    constexpr void setStart(size_t sideIndex, Type start) { size[sideIndex] += position[sideIndex] - start; position[sideIndex] = start; }
    constexpr Type getEnd(size_t sideIndex) const { return position[sideIndex]; }
    constexpr void setEnd(size_t sideIndex, Type end) { size[sideIndex] = end - position[sideIndex]; }

};

}

using FloatRectangle = Templates::Rectangle<float>;
using DoubleRectangle = Templates::Rectangle<double>;
using IntegerRectangle = Templates::Rectangle<int32_t>;
using Rectangle = Templates::Rectangle<FloatType>;

}
