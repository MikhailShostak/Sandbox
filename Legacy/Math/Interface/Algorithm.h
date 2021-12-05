#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Rectangle.h"

#include "BasicConstants.h"
#include "VectorConstants.h"

#include <algorithm>

namespace Math
{

template<typename Type>
constexpr inline const Type &getMin(const Type &l, const Type &r)
{
    return std::min<Type>(l, r);
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMin2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMin(v1.x, v2.x), getMin(v1.y, v2.y), 0, 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMin3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMin(v1.x, v2.x), getMin(v1.y, v2.y), getMin(v1.z, v2.z), 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMin4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMin(v1.x, v2.x), getMin(v1.y, v2.y), getMin(v1.z, v2.z), getMin(v1.w, v2.w) };
}

template<typename Type>
constexpr inline const Type &getMax(const Type &l, const Type &r)
{
    return std::max<Type>(l, r);
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMax2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMax(v1.x, v2.x), getMax(v1.y, v2.y), 0, 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMax3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMax(v1.x, v2.x), getMax(v1.y, v2.y), getMax(v1.z, v2.z), 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> getMax4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return Templates::Vector<Type>{ getMax(v1.x, v2.x), getMax(v1.y, v2.y), getMax(v1.z, v2.z), getMax(v1.w, v2.w) };
}

template<typename Type>
constexpr inline const Type &clamp(Type v, Type min = 0, Type max = 1)
{
    return std::clamp<Type>(v, min, max);
}

template<typename Type>
constexpr inline Templates::Vector<Type> clamp2(const Templates::Vector<Type> &v, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return Templates::Vector<Type>{ clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), 0, 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> clamp3(const Templates::Vector<Type> &v, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return Templates::Vector<Type>{ clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), 0 };
}

template<typename Type>
constexpr inline Templates::Vector<Type> clamp4(const Templates::Vector<Type> &v, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return Templates::Vector<Type>{ clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w) };
}

template<typename Type>
constexpr inline Type inverseInRange(Type value, Type min = 0, Type max = 1)
{
    return min + max - value;
}

template<typename Type>
constexpr inline Templates::Vector<Type> inverseInRange2(const Templates::Vector<Type> &value, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return min.getXY() + max.getXY() - value.getXY();
}

template<typename Type>
constexpr inline Templates::Vector<Type> inverseInRange3(const Templates::Vector<Type> &value, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return min.getXYZ() + max.getXYZ() - value.getXYZ();
}

template<typename Type>
constexpr inline Templates::Vector<Type> inverseInRange4(const Templates::Vector<Type> &value, const Templates::Vector<Type> &min = Math::Constants::NullVector, const Templates::Vector<Type> &max = Math::Constants::PositiveVectorSpace)
{
    return min + max - value;
}

template<typename Type>
constexpr inline Type remap(Type value, Type sourceMin, Type sourceMax, Type targetMin = 0, Type targetMax = 1)
{
    return targetMin + (value - sourceMin) * (targetMax - targetMin) / (sourceMax - sourceMin);
};

template<typename Type>
constexpr inline Templates::Vector<Type> remap2(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return targetMin.getXY() + (value.getXY() - sourceMin.getXY()) * (targetMax.getXY() - targetMin.getXY()) / (sourceMax.getXY() - sourceMin.getXY());
};

template<typename Type>
constexpr inline Templates::Vector<Type> remap3(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return targetMin.getXYZ() + (value.getXYZ() - sourceMin.getXYZ()) * (targetMax.getXYZ() - targetMin.getXYZ()) / (sourceMax.getXYZ() - sourceMin.getXYZ());
};

template<typename Type>
constexpr inline Templates::Vector<Type> remap4(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return targetMin + (value - sourceMin) * (targetMax - targetMin) / (sourceMax - sourceMin);
};

template<typename Type>
constexpr inline Type remapAndClamp(Type value, Type sourceMin, Type sourceMax, Type targetMin = 0, Type targetMax = 1)
{
    return clamp<Type>(remap(value, sourceMin, sourceMax, targetMin, targetMax), targetMin, targetMax);
};

template<typename Type>
constexpr inline Templates::Vector<Type> remapAndClamp2(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return clamp2<Type>(remap2(value, sourceMin, sourceMax, targetMin, targetMax), targetMin, targetMax);
};

template<typename Type>
constexpr inline Templates::Vector<Type> remapAndClamp3(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return clamp3<Type>(remap3(value, sourceMin, sourceMax, targetMin, targetMax), targetMin, targetMax);
};

template<typename Type>
constexpr inline Templates::Vector<Type> remapAndClamp4(const Templates::Vector<Type> &value, const Templates::Vector<Type> &sourceMin, const Templates::Vector<Type> &sourceMax, const Templates::Vector<Type> &targetMin = Math::Constants::NullVector, const Templates::Vector<Type> &targetMax = Math::Constants::PositiveVectorSpace)
{
    return clamp4<Type>(remap4(value, sourceMin, sourceMax, targetMin, targetMax), targetMin, targetMax);
};

template<typename Type>
constexpr inline Type lerp(Type start, Type end, FloatType percent)
{
    return start + (end - start) * percent;
}

template<typename Type>
constexpr inline Templates::Vector<Type> lerp2(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent)
{
    return start.getXY() + (end.getXY() - start.getXY()) * percent;
}

template<typename Type>
constexpr inline Templates::Vector<Type> lerp3(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent)
{
    return start.getXYZ() + (end.getXYZ() - start.getXYZ()) * percent;
}

template<typename Type>
constexpr inline Templates::Vector<Type> lerp4(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent)
{
    return start + (end - start) * percent;
}

template<typename Type>
inline Templates::Vector<Type> slerp2(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    FloatType dot = start.getDot2(end);
    dot = Math::clamp2(dot, FloatType(-1), FloatType(1));
    FloatType theta = acos(dot) * percent;
    return start * cos(theta) + Templates::Vector<Type>(end - start * percent).normalize2() * sin(theta);
}

template<typename Type>
inline Templates::Vector<Type> slerp3(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    FloatType dot = start.getDot3(end);
    dot = Math::clamp3(dot, FloatType(-1), FloatType(1));
    FloatType theta = acos(dot) * percent;
    return start * cos(theta) + Templates::Vector<Type>(end - start * percent).normalize3() * sin(theta);
}

template<typename Type>
inline Templates::Vector<Type> slerp4(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    FloatType dot = start.getDot4(end);
    dot = Math::clamp4(dot, FloatType(-1), FloatType(1));
    FloatType theta = acos(dot) * percent;
    return start * cos(theta) + Templates::Vector<Type>(end - start * percent).normalize4() * sin(theta);
}

template<typename Type>
inline Type nlerp2(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    return lerp2(start, end, percent).normalize2();
}

template<typename Type>
inline Type nlerp3(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    return lerp3(start, end, percent).normalize3();
}

template<typename Type>
inline Type nlerp4(const Templates::Vector<Type> &start, const Templates::Vector<Type> &end, FloatType percent) //TODO: add constexpr
{
    return lerp4(start, end, percent).normalize4();
}

template<typename Type = FloatType, typename ...Types>
constexpr inline Type getAverage(const Types &...elements)
{
    auto sum = (elements + ...);
    return Type(sum) / sizeof...(elements);
}

template<typename Type>
constexpr inline Templates::Rectangle<Type> getCenteredRectangle(const Templates::Vector<Type> &size, const Templates::Vector<Type> &rectangleSize)
{
    return Templates::Rectangle<Type>{ { (size.x - rectangleSize.x) / 2, (size.y - rectangleSize.y) / 2 }, { rectangleSize.x, rectangleSize.y } };
};

template<typename Type>
inline Type snapToGrid(Type value, Type gridSize) //TODO: add constexpr
{
    return gridSize > 0 ? value.x - std::fmod(value.x, gridSize) : value;
}

template<typename Type>
inline Templates::Vector<Type> snapToGrid2(const Templates::Vector<Type> &value, Type gridSize) //TODO: add constexpr
{
    return gridSize > 0 ? Templates::Vector<Type>{
        static_cast<Type>(value.x - std::fmod(value.x, gridSize)),
        static_cast<Type>(value.y - std::fmod(value.y, gridSize)),
    } : value;
}

template<typename Type>
inline Templates::Vector<Type> snapToGrid3(const Templates::Vector<Type> &value, Type gridSize) //TODO: add constexpr
{
    return gridSize > 0 ? Templates::Vector<Type>{
        static_cast<Type>(value.x - std::fmod(value.x, gridSize)),
        static_cast<Type>(value.y - std::fmod(value.y, gridSize)),
        static_cast<Type>(value.z - std::fmod(value.z, gridSize)),
    } : value;
}

template<typename Type>
inline Templates::Vector<Type> snapToGrid4(const Templates::Vector<Type> &value, Type gridSize) //TODO: add constexpr
{
    return gridSize > 0 ? Templates::Vector<Type>{
        static_cast<Type>(value.x - std::fmod(value.x, gridSize)),
        static_cast<Type>(value.y - std::fmod(value.y, gridSize)),
        static_cast<Type>(value.z - std::fmod(value.z, gridSize)),
        static_cast<Type>(value.w - std::fmod(value.w, gridSize)),
    } : value;
}

}
