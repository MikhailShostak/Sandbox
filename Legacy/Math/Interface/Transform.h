#pragma once

#include "BasicConstants.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Transform
{
    Vector<Type> Position = Vector<Type>();
    Quaternion<Type> Rotation = Quaternion<Type>();
    
    Transform(const Vector<Type> &Position = {}, const Quaternion<Type> &Rotation = {})
    {
        this->Position = Position;
        this->Rotation = Rotation;
    }

    Matrix<Type> getMatrix() const
    {
        return Rotation.toMatrix().getTranslated(Position);
    }

    void reflectPosition()
    {
        Position.reflect3();
    }

    void reflectRotation()
    {
        Rotation.reflect();
    }

    void reflect()
    {
        Position.reflect3();
        Rotation.reflect();
    }

    Transform getReflectedPosition() const
    {
        return {
            Position.getReflected3(),
            Rotation,
        };
    }

    Transform getReflectedRotation() const
    {
        return {
            Position,
            Rotation.getReflected(),
        };
    }

    Transform getReflected() const
    {
        return {
            Position.getReflected3(),
            Rotation.getReflected(),
        };
    }

    Vector<Type> getDirection() const
    {
        return {
            -sinf(Rotation.y * (Constants::Pi / Type(180.0f))) * cosf(Rotation.x * (Constants::Pi / Type(180.0f))),
            sinf(Rotation.x * (Constants::Pi / Type(180.0f))),
            -cosf(Rotation.y * (Constants::Pi / Type(180.0f))) * cosf(Rotation.x * (Constants::Pi / Type(180.0f))),
            0.0f,
        };
    }

};

}

using FloatTransform = Templates::Transform<float>;
using DoubleTransform = Templates::Transform<double>;
using IntegerTransform = Templates::Transform<int32_t>;
using Transform = Templates::Transform<FloatType>;

}
