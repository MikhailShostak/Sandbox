#pragma once

#include "BasicConstants.h"

namespace Math
{

namespace Templates
{

template<typename _Type>
struct Vector
{
    using Type = _Type;

    union
    {
        struct
        {
            Type x;
            Type y;
            Type z;
            Type w;
        };
        struct
        {
            Type X;
            Type Y;
            Type Z;
            Type W;
        };
        Type data[4] = {};
    };

    constexpr bool isEmpty() const { return x == 0 && y == 0 && z == 0 && w == 0; }
    constexpr explicit operator bool() const { return !isEmpty(); }

    constexpr void clear() { x = 0; y = 0; z = 0; w = 0; }

    constexpr Type &operator[](size_t index) { return data[index]; }
    constexpr const Type &operator[](size_t index) const { return data[index]; }

    constexpr Vector<Type> operator -() const { return Vector<Type>{ -x, -y, -z, -w }; }

    constexpr Vector<Type> &operator +=(const Vector<Type> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    constexpr Vector<Type> &operator -=(const Vector<Type> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    constexpr Vector<Type> &operator *=(const Vector<Type> &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    constexpr Vector<Type> &operator /=(const Vector<Type> &v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXX() const { return ReturnType{ x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXY() const { return ReturnType{ static_cast<ReturnType::Type>(x), static_cast<ReturnType::Type>(y) }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZ() const { return ReturnType{ x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXW() const { return ReturnType{ x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYX() const { return ReturnType{ y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYY() const { return ReturnType{ y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZ() const { return ReturnType{ y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYW() const { return ReturnType{ y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZX() const { return ReturnType{ z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZY() const { return ReturnType{ z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZ() const { return ReturnType{ z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZW() const { return ReturnType{ z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWX() const { return ReturnType{ w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWY() const { return ReturnType{ w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZ() const { return ReturnType{ w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWW() const { return ReturnType{ w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXX() const { return ReturnType{ x, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXY() const { return ReturnType{ x, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXZ() const { return ReturnType{ x, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXW() const { return ReturnType{ x, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYX() const { return ReturnType{ x, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYY() const { return ReturnType{ x, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYZ() const { return ReturnType{ x, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYW() const { return ReturnType{ x, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZX() const { return ReturnType{ x, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZY() const { return ReturnType{ x, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZZ() const { return ReturnType{ x, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZW() const { return ReturnType{ x, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWX() const { return ReturnType{ x, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWY() const { return ReturnType{ x, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWZ() const { return ReturnType{ x, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWW() const { return ReturnType{ x, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXX() const { return ReturnType{ y, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXY() const { return ReturnType{ y, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXZ() const { return ReturnType{ y, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXW() const { return ReturnType{ y, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYX() const { return ReturnType{ y, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYY() const { return ReturnType{ y, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYZ() const { return ReturnType{ y, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYW() const { return ReturnType{ y, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZX() const { return ReturnType{ y, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZY() const { return ReturnType{ y, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZZ() const { return ReturnType{ y, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZW() const { return ReturnType{ y, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWX() const { return ReturnType{ y, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWY() const { return ReturnType{ y, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWZ() const { return ReturnType{ y, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWW() const { return ReturnType{ y, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXX() const { return ReturnType{ z, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXY() const { return ReturnType{ z, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXZ() const { return ReturnType{ z, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXW() const { return ReturnType{ z, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYX() const { return ReturnType{ z, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYY() const { return ReturnType{ z, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYZ() const { return ReturnType{ z, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYW() const { return ReturnType{ z, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZX() const { return ReturnType{ z, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZY() const { return ReturnType{ z, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZZ() const { return ReturnType{ z, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZW() const { return ReturnType{ z, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWX() const { return ReturnType{ z, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWY() const { return ReturnType{ z, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWZ() const { return ReturnType{ z, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWW() const { return ReturnType{ z, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXX() const { return ReturnType{ w, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXY() const { return ReturnType{ w, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXZ() const { return ReturnType{ w, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXW() const { return ReturnType{ w, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYX() const { return ReturnType{ w, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYY() const { return ReturnType{ w, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYZ() const { return ReturnType{ w, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYW() const { return ReturnType{ w, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZX() const { return ReturnType{ w, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZY() const { return ReturnType{ w, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZZ() const { return ReturnType{ w, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZW() const { return ReturnType{ w, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWX() const { return ReturnType{ w, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWY() const { return ReturnType{ w, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWZ() const { return ReturnType{ w, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWW() const { return ReturnType{ w, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXXX() const { return ReturnType{ x, x, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXXY() const { return ReturnType{ x, x, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXXZ() const { return ReturnType{ x, x, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXXW() const { return ReturnType{ x, x, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXYX() const { return ReturnType{ x, x, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXYY() const { return ReturnType{ x, x, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXYZ() const { return ReturnType{ x, x, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXYW() const { return ReturnType{ x, x, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXZX() const { return ReturnType{ x, x, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXZY() const { return ReturnType{ x, x, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXZZ() const { return ReturnType{ x, x, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXZW() const { return ReturnType{ x, x, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXWX() const { return ReturnType{ x, x, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXWY() const { return ReturnType{ x, x, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXWZ() const { return ReturnType{ x, x, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXXWW() const { return ReturnType{ x, x, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYXX() const { return ReturnType{ x, y, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYXY() const { return ReturnType{ x, y, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYXZ() const { return ReturnType{ x, y, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYXW() const { return ReturnType{ x, y, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYYX() const { return ReturnType{ x, y, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYYY() const { return ReturnType{ x, y, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYYZ() const { return ReturnType{ x, y, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYYW() const { return ReturnType{ x, y, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYZX() const { return ReturnType{ x, y, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYZY() const { return ReturnType{ x, y, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYZZ() const { return ReturnType{ x, y, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYZW() const { return ReturnType{ x, y, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYWX() const { return ReturnType{ x, y, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYWY() const { return ReturnType{ x, y, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYWZ() const { return ReturnType{ x, y, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXYWW() const { return ReturnType{ x, y, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZXX() const { return ReturnType{ x, z, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZXY() const { return ReturnType{ x, z, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZXZ() const { return ReturnType{ x, z, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZXW() const { return ReturnType{ x, z, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZYX() const { return ReturnType{ x, z, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZYY() const { return ReturnType{ x, z, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZYZ() const { return ReturnType{ x, z, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZYW() const { return ReturnType{ x, z, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZZX() const { return ReturnType{ x, z, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZZY() const { return ReturnType{ x, z, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZZZ() const { return ReturnType{ x, z, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZZW() const { return ReturnType{ x, z, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZWX() const { return ReturnType{ x, z, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZWY() const { return ReturnType{ x, z, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZWZ() const { return ReturnType{ x, z, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXZWW() const { return ReturnType{ x, z, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWXX() const { return ReturnType{ x, w, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWXY() const { return ReturnType{ x, w, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWXZ() const { return ReturnType{ x, w, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWXW() const { return ReturnType{ x, w, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWYX() const { return ReturnType{ x, w, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWYY() const { return ReturnType{ x, w, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWYZ() const { return ReturnType{ x, w, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWYW() const { return ReturnType{ x, w, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWZX() const { return ReturnType{ x, w, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWZY() const { return ReturnType{ x, w, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWZZ() const { return ReturnType{ x, w, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWZW() const { return ReturnType{ x, w, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWWX() const { return ReturnType{ x, w, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWWY() const { return ReturnType{ x, w, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWWZ() const { return ReturnType{ x, w, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getXWWW() const { return ReturnType{ x, w, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXXX() const { return ReturnType{ y, x, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXXY() const { return ReturnType{ y, x, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXXZ() const { return ReturnType{ y, x, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXXW() const { return ReturnType{ y, x, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXYX() const { return ReturnType{ y, x, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXYY() const { return ReturnType{ y, x, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXYZ() const { return ReturnType{ y, x, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXYW() const { return ReturnType{ y, x, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXZX() const { return ReturnType{ y, x, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXZY() const { return ReturnType{ y, x, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXZZ() const { return ReturnType{ y, x, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXZW() const { return ReturnType{ y, x, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXWX() const { return ReturnType{ y, x, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXWY() const { return ReturnType{ y, x, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXWZ() const { return ReturnType{ y, x, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYXWW() const { return ReturnType{ y, x, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYXX() const { return ReturnType{ y, y, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYXY() const { return ReturnType{ y, y, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYXZ() const { return ReturnType{ y, y, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYXW() const { return ReturnType{ y, y, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYYX() const { return ReturnType{ y, y, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYYY() const { return ReturnType{ y, y, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYYZ() const { return ReturnType{ y, y, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYYW() const { return ReturnType{ y, y, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYZX() const { return ReturnType{ y, y, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYZY() const { return ReturnType{ y, y, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYZZ() const { return ReturnType{ y, y, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYZW() const { return ReturnType{ y, y, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYWX() const { return ReturnType{ y, y, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYWY() const { return ReturnType{ y, y, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYWZ() const { return ReturnType{ y, y, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYYWW() const { return ReturnType{ y, y, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZXX() const { return ReturnType{ y, z, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZXY() const { return ReturnType{ y, z, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZXZ() const { return ReturnType{ y, z, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZXW() const { return ReturnType{ y, z, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZYX() const { return ReturnType{ y, z, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZYY() const { return ReturnType{ y, z, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZYZ() const { return ReturnType{ y, z, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZYW() const { return ReturnType{ y, z, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZZX() const { return ReturnType{ y, z, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZZY() const { return ReturnType{ y, z, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZZZ() const { return ReturnType{ y, z, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZZW() const { return ReturnType{ y, z, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZWX() const { return ReturnType{ y, z, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZWY() const { return ReturnType{ y, z, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZWZ() const { return ReturnType{ y, z, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYZWW() const { return ReturnType{ y, z, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWXX() const { return ReturnType{ y, w, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWXY() const { return ReturnType{ y, w, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWXZ() const { return ReturnType{ y, w, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWXW() const { return ReturnType{ y, w, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWYX() const { return ReturnType{ y, w, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWYY() const { return ReturnType{ y, w, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWYZ() const { return ReturnType{ y, w, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWYW() const { return ReturnType{ y, w, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWZX() const { return ReturnType{ y, w, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWZY() const { return ReturnType{ y, w, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWZZ() const { return ReturnType{ y, w, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWZW() const { return ReturnType{ y, w, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWWX() const { return ReturnType{ y, w, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWWY() const { return ReturnType{ y, w, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWWZ() const { return ReturnType{ y, w, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getYWWW() const { return ReturnType{ y, w, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXXX() const { return ReturnType{ z, x, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXXY() const { return ReturnType{ z, x, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXXZ() const { return ReturnType{ z, x, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXXW() const { return ReturnType{ z, x, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXYX() const { return ReturnType{ z, x, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXYY() const { return ReturnType{ z, x, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXYZ() const { return ReturnType{ z, x, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXYW() const { return ReturnType{ z, x, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXZX() const { return ReturnType{ z, x, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXZY() const { return ReturnType{ z, x, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXZZ() const { return ReturnType{ z, x, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXZW() const { return ReturnType{ z, x, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXWX() const { return ReturnType{ z, x, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXWY() const { return ReturnType{ z, x, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXWZ() const { return ReturnType{ z, x, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZXWW() const { return ReturnType{ z, x, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYXX() const { return ReturnType{ z, y, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYXY() const { return ReturnType{ z, y, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYXZ() const { return ReturnType{ z, y, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYXW() const { return ReturnType{ z, y, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYYX() const { return ReturnType{ z, y, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYYY() const { return ReturnType{ z, y, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYYZ() const { return ReturnType{ z, y, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYYW() const { return ReturnType{ z, y, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYZX() const { return ReturnType{ z, y, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYZY() const { return ReturnType{ z, y, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYZZ() const { return ReturnType{ z, y, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYZW() const { return ReturnType{ z, y, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYWX() const { return ReturnType{ z, y, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYWY() const { return ReturnType{ z, y, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYWZ() const { return ReturnType{ z, y, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZYWW() const { return ReturnType{ z, y, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZXX() const { return ReturnType{ z, z, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZXY() const { return ReturnType{ z, z, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZXZ() const { return ReturnType{ z, z, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZXW() const { return ReturnType{ z, z, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZYX() const { return ReturnType{ z, z, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZYY() const { return ReturnType{ z, z, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZYZ() const { return ReturnType{ z, z, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZYW() const { return ReturnType{ z, z, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZZX() const { return ReturnType{ z, z, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZZY() const { return ReturnType{ z, z, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZZZ() const { return ReturnType{ z, z, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZZW() const { return ReturnType{ z, z, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZWX() const { return ReturnType{ z, z, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZWY() const { return ReturnType{ z, z, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZWZ() const { return ReturnType{ z, z, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZZWW() const { return ReturnType{ z, z, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWXX() const { return ReturnType{ z, w, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWXY() const { return ReturnType{ z, w, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWXZ() const { return ReturnType{ z, w, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWXW() const { return ReturnType{ z, w, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWYX() const { return ReturnType{ z, w, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWYY() const { return ReturnType{ z, w, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWYZ() const { return ReturnType{ z, w, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWYW() const { return ReturnType{ z, w, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWZX() const { return ReturnType{ z, w, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWZY() const { return ReturnType{ z, w, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWZZ() const { return ReturnType{ z, w, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWZW() const { return ReturnType{ z, w, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWWX() const { return ReturnType{ z, w, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWWY() const { return ReturnType{ z, w, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWWZ() const { return ReturnType{ z, w, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getZWWW() const { return ReturnType{ z, w, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXXX() const { return ReturnType{ w, x, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXXY() const { return ReturnType{ w, x, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXXZ() const { return ReturnType{ w, x, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXXW() const { return ReturnType{ w, x, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXYX() const { return ReturnType{ w, x, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXYY() const { return ReturnType{ w, x, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXYZ() const { return ReturnType{ w, x, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXYW() const { return ReturnType{ w, x, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXZX() const { return ReturnType{ w, x, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXZY() const { return ReturnType{ w, x, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXZZ() const { return ReturnType{ w, x, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXZW() const { return ReturnType{ w, x, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXWX() const { return ReturnType{ w, x, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXWY() const { return ReturnType{ w, x, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXWZ() const { return ReturnType{ w, x, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWXWW() const { return ReturnType{ w, x, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYXX() const { return ReturnType{ w, y, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYXY() const { return ReturnType{ w, y, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYXZ() const { return ReturnType{ w, y, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYXW() const { return ReturnType{ w, y, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYYX() const { return ReturnType{ w, y, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYYY() const { return ReturnType{ w, y, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYYZ() const { return ReturnType{ w, y, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYYW() const { return ReturnType{ w, y, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYZX() const { return ReturnType{ w, y, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYZY() const { return ReturnType{ w, y, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYZZ() const { return ReturnType{ w, y, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYZW() const { return ReturnType{ w, y, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYWX() const { return ReturnType{ w, y, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYWY() const { return ReturnType{ w, y, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYWZ() const { return ReturnType{ w, y, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWYWW() const { return ReturnType{ w, y, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZXX() const { return ReturnType{ w, z, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZXY() const { return ReturnType{ w, z, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZXZ() const { return ReturnType{ w, z, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZXW() const { return ReturnType{ w, z, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZYX() const { return ReturnType{ w, z, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZYY() const { return ReturnType{ w, z, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZYZ() const { return ReturnType{ w, z, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZYW() const { return ReturnType{ w, z, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZZX() const { return ReturnType{ w, z, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZZY() const { return ReturnType{ w, z, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZZZ() const { return ReturnType{ w, z, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZZW() const { return ReturnType{ w, z, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZWX() const { return ReturnType{ w, z, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZWY() const { return ReturnType{ w, z, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZWZ() const { return ReturnType{ w, z, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWZWW() const { return ReturnType{ w, z, w, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWXX() const { return ReturnType{ w, w, x, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWXY() const { return ReturnType{ w, w, x, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWXZ() const { return ReturnType{ w, w, x, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWXW() const { return ReturnType{ w, w, x, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWYX() const { return ReturnType{ w, w, y, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWYY() const { return ReturnType{ w, w, y, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWYZ() const { return ReturnType{ w, w, y, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWYW() const { return ReturnType{ w, w, y, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWZX() const { return ReturnType{ w, w, z, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWZY() const { return ReturnType{ w, w, z, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWZZ() const { return ReturnType{ w, w, z, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWZW() const { return ReturnType{ w, w, z, w }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWWX() const { return ReturnType{ w, w, w, x }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWWY() const { return ReturnType{ w, w, w, y }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWWZ() const { return ReturnType{ w, w, w, z }; }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getWWWW() const { return ReturnType{ w, w, w, w }; }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getHalfX() const
    {
        return x / ReturnType(2);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getHalfY() const
    {
        return y / ReturnType(2);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getHalfZ() const
    {
        return z / ReturnType(2);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getHalfW() const
    {
        return w / ReturnType(2);
    }

    template<typename ReturnType = Vector<FloatType>>
    constexpr ReturnType getHalf2() const
    {
        return ReturnType{ 
            static_cast<ReturnType::Type>(getHalfX()),
            static_cast<ReturnType::Type>(getHalfY()),
            static_cast<ReturnType::Type>(z),
            static_cast<ReturnType::Type>(w)
        };
    }

    template<typename ReturnType = Vector<FloatType>>
    constexpr ReturnType getHalf3() const
    {
        return ReturnType{ getHalfX(), getHalfY(), getHalfZ(), w };
    }

    template<typename ReturnType = Vector<FloatType>>
    constexpr ReturnType getHalf4() const
    {
        return ReturnType{ getHalfX(), getHalfY(), getHalfZ(), getHalfW() };
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getXYAspectRatio() const
    {
        return ReturnType(x) / ReturnType(y);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getXZAspectRatio() const
    {
        return ReturnType(x) / ReturnType(z);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getXWAspectRatio() const
    {
        return ReturnType(x) / ReturnType(w);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getYXAspectRatio() const
    {
        return ReturnType(y) / ReturnType(x);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getYZAspectRatio() const
    {
        return ReturnType(y) / ReturnType(z);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getYWAspectRatio() const
    {
        return ReturnType(y) / ReturnType(w);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getZXAspectRatio() const
    {
        return ReturnType(z) / ReturnType(x);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getZYAspectRatio() const
    {
        return ReturnType(z) / ReturnType(y);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getZWAspectRatio() const
    {
        return ReturnType(z) / ReturnType(w);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getWXAspectRatio() const
    {
        return ReturnType(w) / ReturnType(x);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getWYAspectRatio() const
    {
        return ReturnType(w) / ReturnType(y);
    }

    template<typename ReturnType = FloatType>
    constexpr ReturnType getWZAspectRatio() const
    {
        return ReturnType(w) / ReturnType(z);
    }

    constexpr Vector<Type> &reflectX()
    {
        x = -x;
        return *this;
    }

    constexpr Vector<Type> &reflectY()
    {
        y = -y;
        return *this;
    }

    constexpr Vector<Type> &reflectZ()
    {
        z = -z;
        return *this;
    }

    constexpr Vector<Type> &reflectW()
    {
        w = -w;
        return *this;
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflectedX() const
    {
        return ReturnType{
            static_cast<ReturnType::Type>(-x),
            static_cast<ReturnType::Type>(y),
            static_cast<ReturnType::Type>(z),
            static_cast<ReturnType::Type>(w)
        };
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflectedY() const
    {
        return ReturnType{
            static_cast<ReturnType::Type>(x),
            static_cast<ReturnType::Type>(-y),
            static_cast<ReturnType::Type>(z),
            static_cast<ReturnType::Type>(w)
        };
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflectedZ() const
    {
        return ReturnType{
            static_cast<ReturnType::Type>(x),
            static_cast<ReturnType::Type>(y),
            static_cast<ReturnType::Type>(-z),
            static_cast<ReturnType::Type>(w)
        };
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflectedW() const
    {
        return ReturnType{
            static_cast<ReturnType::Type>(x),
            static_cast<ReturnType::Type>(y),
            static_cast<ReturnType::Type>(z),
            static_cast<ReturnType::Type>(-w)
        };
    }

    constexpr Vector<Type> &reflect2()
    {
        x = -x;
        y = -y;
        return *this;
    }

    constexpr Vector<Type> &reflect3()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    constexpr Vector<Type> &reflect4()
    {
        x = -x;
        y = -y;
        z = -z;
        w = -w;
        return *this;
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflected2() const
    {
        return ReturnType{ -x, -y, z, w };
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflected3() const
    {
        return ReturnType{ -x, -y, -z, w };
    }

    template<typename ReturnType = Vector<Type>>
    constexpr ReturnType getReflected4() const
    {
        return ReturnType{ -x, -y, -z, -w };
    }

    constexpr Vector<Type> &reflect2(const Vector<Type> &normal)
    {
        *this -= 2 * getDot2(normal) * normal; return *this;
    }

    constexpr Vector<Type> &reflect3(const Vector<Type> &normal)
    {
        *this -= 2 * getDot3(normal) * normal; return *this;
    }

    constexpr Vector<Type> &reflect4(const Vector<Type> &normal)
    {
        *this -= 2 * getDot4(normal) * normal; return *this;
    }

    constexpr Vector<Type> getReflected2(const Vector<Type> &normal) const
    {
        return Vector<Type>{ *this - 2 * getDot2(normal) * normal };
    }

    constexpr Vector<Type> getReflected3(const Vector<Type> &normal) const
    {
        return Vector<Type>{ *this - 2 * getDot3(normal) * normal };
    }

    constexpr Vector<Type> getReflected4(const Vector<Type> &normal) const
    {
        return Vector<Type>{ *this - 2 * getDot4(normal) * normal };
    }

    constexpr Type getArea2() const
    {
        return x * y;
    }

    constexpr Type getArea3() const
    {
        return x * y * z;
    }

    constexpr Type getArea4() const
    {
        return x * y * z * w;
    }

    //TODO: add constexpr
    Vector &normalize2()
    {
        FloatType l = getLenght2();
        x /= l;
        y /= l;
        return *this;
    }

    //TODO: add constexpr
    Vector &normalize3()
    {
        FloatType l = getLenght3();
        x /= l;
        y /= l;
        z /= l;
        return *this;
    }

    //TODO: add constexpr
    Vector &normalize4()
    {
        FloatType l = getLenght4();
        x /= l;
        y /= l;
        z /= l;
        w /= l;
        return *this;
    }

    //TODO: add constexpr
    Vector getNormalized2() const
    {
        FloatType l = getLenght2();
        return Vector{ x / l, y / l, z, w };
    }

    //TODO: add constexpr
    Vector getNormalized3() const
    {
        FloatType l = getLenght3();
        return Vector{ x / l, y / l, z / l, w };
    }

    //TODO: add constexpr
    Vector getNormalized4() const
    {
        FloatType l = getLenght4();
        return Vector{ x / l, y / l, z / l, w / l };
    }

    FloatType getLenght2() const
    {
        //TODO: replace with constexpr
        return std::sqrt(getDot2());
    }

    FloatType getLenght3() const
    {
        //TODO: replace with constexpr
        return std::sqrt(getDot3());
    }

    FloatType getLenght4() const
    {
        //TODO: replace with constexpr
        return std::sqrt(getDot4());
    }

    constexpr FloatType getDistance2(const Vector<Type> &v) const
    {
        return (*this - v).getLenght2();
    }

    constexpr FloatType getDistance3(const Vector<Type> &v) const
    {
        return (*this - v).getLenght3();
    }

    constexpr FloatType getDistance4(const Vector<Type> &v) const
    {
        return (*this - v).getLenght4();
    }

    constexpr FloatType getDot2(const Vector<Type> &v) const
    {
        return x * v.x + y * v.y;
    }

    constexpr FloatType getDot3(const Vector<Type> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    constexpr FloatType getDot4(const Vector<Type> &v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    constexpr FloatType getDot2() const
    {
        return getDot2(*this);
    }

    constexpr FloatType getDot3() const
    {
        return getDot3(*this);
    }

    constexpr FloatType getDot4() const
    {
        return getDot4(*this);
    }

    constexpr Type getCross2(const Vector<Type> &v) const
    {
        return x * v.y - y * v.x;
    }

    constexpr Vector<Type> getCross3(const Vector<Type> &v) const
    {
        return Vector<Type>{ y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, w };
    }

    constexpr Vector<Type> getCross4(const Vector<Type> &v) const
    {
        return Vector<Type>{ y * v.z - z * v.y, z * v.w - w * v.z, w * v.x - x * v.w, x * v.y - y * v.x };
    }
};

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator +(const Vector<Type> &l, ArithmeticType r)
{
    return Vector<Type>{ l.x + r, l.y + r, l.z + r, l.w + r, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator +(ArithmeticType l, const Vector<Type> &r)
{
    return Vector<Type>{ l + r.x, l + r.y, l + r.z, l + r.w, };
}

template<typename Type>
constexpr inline Vector<Type> operator +(const Vector<Type> &l, const Vector<Type> &r)
{
    return Vector<Type>{ l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator -(const Vector<Type> &l, ArithmeticType r)
{
    return Vector<Type>{ l.x - r, l.y - r, l.z - r, l.w - r, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator -(ArithmeticType l, const Vector<Type> &r)
{
    return Vector<Type>{ l - r.x, l - r.y, l - r.z, l - r.w, };
}

template<typename Type>
constexpr inline Vector<Type> operator -(const Vector<Type> &l, const Vector<Type> &r)
{
    return Vector<Type>{ l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator *(const Vector<Type> &l, ArithmeticType r)
{
    return Vector<Type>{ l.x * r, l.y * r, l.z * r, l.w * r, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator *(ArithmeticType l, const Vector<Type> &r)
{
    return Vector<Type>{ l * r.x, l * r.y, l * r.z, l * r.w, };
}

template<typename Type>
constexpr inline Vector<Type> operator *(const Vector<Type> &l, const Vector<Type> &r)
{
    return Vector<Type>{ l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator /(const Vector<Type> &l, ArithmeticType r)
{
    return Vector<Type>{ l.x / r, l.y / r, l.z / r, l.w / r, };
}

template<typename Type, typename ArithmeticType>
constexpr inline Vector<Type> operator /(ArithmeticType l, const Vector<Type> &r)
{
    return Vector<Type>{ l / r.x, l / r.y, l / r.z, l / r.w, };
}

template<typename Type>
constexpr inline Vector<Type> operator /(const Vector<Type> &l, const Vector<Type> &r)
{
    return Vector<Type>{ l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w, };
}

}

template<typename Type>
constexpr inline Type getDot2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getDot2(v2);
}

template<typename Type>
constexpr inline Type getDot3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getDot3(v2);
}

template<typename Type>
constexpr inline Type getDot4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getDot4(v2);
}

template<typename Type>
constexpr inline Type getDot2(const Templates::Vector<Type> &v)
{
    return v.getDot2();
}

template<typename Type>
constexpr inline Type getDot3(const Templates::Vector<Type> &v)
{
    return v.getDot3();
}

template<typename Type>
constexpr inline Type getDot4(const Templates::Vector<Type> &v)
{
    return v.getDot4();
}

template<typename Type>
constexpr inline Type getCross2(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getCross2(r);
}

template<typename Type>
constexpr inline Type cross3(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getCross3(r);
}

template<typename Type>
constexpr inline Type cross4(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getCross4(r);
}

template<typename Type>
inline Type getLenght2(const Templates::Vector<Type> &v) //TODO: add constexpr
{
    return v.getLenght2();
}

template<typename Type>
inline Type getLenght3(const Templates::Vector<Type> &v) //TODO: add constexpr
{
    return v.getLenght3();
}

template<typename Type>
inline Type getLenght4(const Templates::Vector<Type> &v) //TODO: add constexpr
{
    return v.getLenght4();
}

template<typename Type>
inline Type getDistance2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    return v1.getDistance2(v2);
}

template<typename Type>
inline Type getDistance3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    return v1.getDistance3(v2);
}

template<typename Type>
inline Type getDistance4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    return v1.getDistance4(v2);
}

template<typename Type>
constexpr inline int8_t compareDot2(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2, Type &dot)
{
    auto d1 = getDot2(v, v1);
    auto d2 = getDot2(v, v2);

    if (d1 == d2)
    {
        dot = d1;
        return 0;
    }

    if (d1 < d2)
    {
        dot = d1;
        return -1;
    }

    dot = d2;
    return 1;
}

template<typename Type>
constexpr inline int8_t compareDot3(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2, Type &dot)
{
    auto d1 = getDot3(v, v1);
    auto d2 = getDot3(v, v2);

    if (d1 == d2)
    {
        dot = d1;
        return 0;
    }

    if (d1 < d2)
    {
        dot = d1;
        return -1;
    }

    dot = d2;
    return 1;
}

template<typename Type>
constexpr inline int8_t compareDot4(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2, Type &dot)
{
    auto d1 = getDot4(v, v1);
    auto d2 = getDot4(v, v2);

    if (d1 == d2)
    {
        dot = d1;
        return 0;
    }

    if (d1 < d2)
    {
        dot = d1;
        return -1;
    }

    dot = d2;
    return 1;
}

template<typename Type>
constexpr inline Type compareLenght2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    auto l1 = v1.getLenght2();
    auto l2 = v2.getLenght2();
    return l1 == l2 ? 0 : (l1 < l1 ? -l1 : l2);
}

template<typename Type>
constexpr inline Type compareLenght3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    auto l1 = v1.getLenght3();
    auto l2 = v2.getLenght3();
    return l1 == l2 ? 0 : (l1 < l1 ? -l1 : l2);
}

template<typename Type>
constexpr inline Type compareLenght4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    auto l1 = v1.getLenght4();
    auto l2 = v2.getLenght4();
    return l1 == l2 ? 0 : (l1 < l1 ? -l1 : l2);
}

template<typename Type>
inline Type compareDistance2(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    auto d1 = getDistance2(v, v1);
    auto d2 = getDistance2(v, v2);
    return d1 == d2 ? 0 : (d1 < d2 ? -d1 : d2);
}

template<typename Type>
inline Type compareDistance3(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    auto d1 = getDistance3(v, v1);
    auto d2 = getDistance3(v, v2);
    return d1 == d2 ? 0 : (d1 < d2 ? -d1 : d2);
}

template<typename Type>
inline Type compareDistance4(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2) //TODO: add constexpr
{
    auto d1 = getDistance4(v, v1);
    auto d2 = getDistance4(v, v2);
    return d1 == d2 ? 0 : (d1 < d2 ? -d1 : d2);
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getShortest2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght2() < v2.getLenght2() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getShortest3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght3() < v2.getLenght3() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getShortest4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght4() < v2.getLenght4() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getLongest2(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght2() > v2.getLenght2() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getLongest3(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght3() > v2.getLenght3() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getLongest4(const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v1.getLenght4() > v2.getLenght4() ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getNearest2(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot2(v1) < v.getDot2(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getNearest3(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot3(v1) < v.getDot3(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getNearest4(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot4(v1) < v.getDot4(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getFarest2(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot2(v1) > v.getDot2(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getFarest3(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot3(v1) > v.getDot3(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline const Templates::Vector<Type> &getFarest4(const Templates::Vector<Type> &v, const Templates::Vector<Type> &v1, const Templates::Vector<Type> &v2)
{
    return v.getDot4(v1) > v.getDot4(v2) ? v1 : v2;
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflectedX(const Templates::Vector<Type> &v)
{
    return v.getReflectedX();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflectedY(const Templates::Vector<Type> &v)
{
    return v.getReflectedY();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflectedZ(const Templates::Vector<Type> &v)
{
    return v.getReflectedZ();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflectedW(const Templates::Vector<Type> &v)
{
    return v.getReflectedW();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected2(const Templates::Vector<Type> &v)
{
    return v.getReflected2();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected3(const Templates::Vector<Type> &v)
{
    return v.getReflected3();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected4(const Templates::Vector<Type> &v)
{
    return v.getReflected4();
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected2(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getReflected2(r);
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected3(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getReflected3(r);
}

template<typename Type>
constexpr inline Templates::Vector<Type> getReflected4(const Templates::Vector<Type> &l, const Templates::Vector<Type> &r)
{
    return l.getReflected4(r);
}

using FloatVector = Templates::Vector<float>;
using DoubleVector = Templates::Vector<double>;
using IntegerVector = Templates::Vector<int32_t>;
using Vector = Templates::Vector<FloatType>;

}
