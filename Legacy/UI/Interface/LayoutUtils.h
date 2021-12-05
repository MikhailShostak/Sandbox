#pragma once

#include "Foundation"
#include "Includes/Direction.gen.h"

struct AxisIndexes
{
    size_t Primary = 0;
    size_t Secondary = 1;
};

struct AxisOffsets
{
    int32_t X = 1;
    int32_t Y = 0;
};

struct AxisData
{
    AxisIndexes Indexes;
    AxisOffsets Offsets;
};

inline bool isHorizontal(UI::Direction direction) //TODO: constexpr
{
    return direction == UI::Direction::Horizontal || direction == UI::Direction::ReverseHorizontal;
}

inline bool isVertical(UI::Direction direction) //TODO: constexpr
{
    return direction == UI::Direction::Vertical || direction == UI::Direction::ReverseVertical;
}

inline size_t getPrimaryAxisIndex(UI::Direction direction) //TODO: constexpr
{
    return isHorizontal(direction) ? 0 : 1;
}

inline size_t getSecondaryAxisIndex(UI::Direction direction) //TODO: constexpr
{
    return isHorizontal(direction) ? 1 : 0;
}

inline size_t getInvertedAxisIndex(size_t axis) //TODO: constexpr
{
    return 1 - axis;
}

inline AxisIndexes getAxisIndexes(UI::Direction direction) //TODO: constexpr
{
    return isHorizontal(direction) ? AxisIndexes{ 0, 1 } : AxisIndexes{ 1, 0 };
}

inline AxisOffsets getAxisOffsets(UI::Direction direction) //TODO: constexpr
{
    switch (direction)
    {
    case UI::Direction::Horizontal:
        return { 1, 0 };
    case UI::Direction::Vertical:
        return { 0, 1 };
    case UI::Direction::ReverseHorizontal:
        return { -1, 0 };
    case UI::Direction::ReverseVertical:
        return { 0, -1 };
    default:
        return { 0, 0 };
    }
}

inline AxisData getAxisData(UI::Direction direction) //TODO: constexpr
{
    return { getAxisIndexes(direction), getAxisOffsets(direction) };
}

template<typename Type>
inline Type getAligned(Type contentSize, Type containerSize, Core::Alignment alignment)
{
    switch (alignment)
    {
    case Core::Alignment::Start:
        return Type{};
    case Core::Alignment::Center:
        return (containerSize - contentSize) / 2;
    case Core::Alignment::End:
        return containerSize - contentSize;
    }
}
