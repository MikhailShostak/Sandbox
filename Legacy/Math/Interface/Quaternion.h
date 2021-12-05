#pragma once

#include "BasicConstants.h"
#include "Vector.h"
#include "RotationOrder.h"

namespace Math
{

namespace Templates
{

template<typename Type>
struct Matrix;

template<typename Type>
struct Quaternion
{
    union
    {
        Type data[4] = { 0, 0, 0, 1 };
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
    };

    static Quaternion<Type> getRotationFromVector()
    {
        /*rotate_vector = normal(rotate_vector)
        create_quat.w = Cos(rotate_angle / 2)
        create_quat.x = rotate_vector.x * Sin(rotate_angle / 2)
        create_quat.y = rotate_vector.y * Sin(rotate_angle / 2)
        create_quat.z = rotate_vector.z * Sin(rotate_angle / 2)*/
    }

    static Quaternion<Type> getRotation(Type x, Type y, Type z, Type angle)
    {
        angle *= Math::Constants::DegreeToRadianRatio;
        auto a = sinf(angle * 0.5f);
        return { a * x, a * y, a * z, cosf(angle * 0.5f) };
    }

    static Quaternion<Type> getXRotation(Type angle)
    {
        return getRotation(Type(1), Type(0), Type(0), angle);
    }

    static Quaternion<Type> getYRotation(Type angle)
    {
        return getRotation(Type(0), Type(1), Type(0), angle);
    }

    static Quaternion<Type> getZRotation(Type angle)
    {
        return getRotation(Type(0), Type(0), Type(1), angle);
    }

    static Quaternion<Type> getEulerRotation(Type xAngle, Type yAngle, Type zAngle, RotationOrder rotationOrder);
    static Quaternion<Type> getXYZEulerRotation(Type xAngle, Type yAngle, Type zAngle);
    static Quaternion<Type> getXZYEulerRotation(Type xAngle, Type yAngle, Type zAngle);
    static Quaternion<Type> getYXZEulerRotation(Type xAngle, Type yAngle, Type zAngle);
    static Quaternion<Type> getYZXEulerRotation(Type xAngle, Type yAngle, Type zAngle);
    static Quaternion<Type> getZXYEulerRotation(Type xAngle, Type yAngle, Type zAngle);
    static Quaternion<Type> getZYXEulerRotation(Type xAngle, Type yAngle, Type zAngle);

    Quaternion() {}
    Quaternion(Type x, Type y, Type z, Type w);
    Quaternion(const Matrix<Type> &matrix);

    Quaternion getNormalized() const;
    Quaternion getReflected() const;
    Vector<Type> getRotatedVector(const Vector<Type> &vector) const;

    Quaternion &normalize();
    Quaternion &reflect();
    void rotateVector(Vector<Type> &vector) const;

    Matrix<Type> toMatrix() const;

    Quaternion<Type> &operator *=(const Quaternion<Type> &quaternion);

};

}

}

#include "Matrix.h"

namespace Math
{

namespace Templates
{

    template<typename Type>
    inline Quaternion<Type>::Quaternion(Type x, Type y, Type z, Type w):
        x(x),
        y(y),
        z(z),
        w(w)
    {}

    template<typename Type>
    inline Quaternion<Type>::Quaternion(const Matrix<Type> &m)
    {
        Type tr, s, q[4];
        int i, j, k;

        int nxt[3] = {1, 2, 0};

        tr = m[0][0] + m[1][1] + m[2][2];

        if (tr > 0.0)
        {
            s = sqrt (tr + 1.0);
            w = s / 2.0;
            s = 0.5 / s;
            x = (m[1][2] - m[2][1]) * s;
            y = (m[2][0] - m[0][2]) * s;
            z = (m[0][1] - m[1][0]) * s;
        }
        else
        {
            i = 0;
            if (m[1][1] > m[0][0])
                i = 1;
            if (m[2][2] > m[i][i])
                i = 2;
            j = nxt[i];
            k = nxt[j];

            s = sqrt ((m[i][i] - (m[j][j] + m[k][k])) + 1.0);

            q[i] = s * 0.5;

            if (s != 0.0) s = 0.5 / s;

            q[3] = (m[j][k] - m[k][j]) * s;
            q[j] = (m[i][j] + m[j][i]) * s;
            q[k] = (m[i][k] + m[k][i]) * s;

            x = q[0];
            y = q[1];
            z = q[2];
            w = q[3];
        }
    }

    template<typename Type>
    inline Matrix<Type> Quaternion<Type>::toMatrix() const
    {
        Matrix<Type> mat;

        float xx = x * x;
        float xy = x * y;
        float xz = x * z;
        float xw = x * w;

        float yy = y * y;
        float yz = y * z;
        float yw = y * w;

        float zz = z * z;
        float zw = z * w;

        mat[0][0] = 1 - 2 * ( yy + zz );
        mat[0][1] =     2 * ( xy - zw );
        mat[0][2] =     2 * ( xz + yw );
        mat[0][3] = 0;

        mat[1][0] =     2 * ( xy + zw );
        mat[1][1] = 1 - 2 * ( xx + zz );
        mat[1][2] =     2 * ( yz - xw );
        mat[1][3] = 0;

        mat[2][0] =     2 * ( xz - yw );
        mat[2][1] =     2 * ( yz + xw );
        mat[2][2] = 1 - 2 * ( xx + yy );
        mat[2][3] = 0;

        mat[3][0] = 0;
        mat[3][1] = 0;
        mat[3][2] = 0;
        mat[3][3] = 1;

        mat.transpose();

        return mat;
    }

    template<typename Type>
    inline Quaternion<Type> &Quaternion<Type>::operator *=(const Quaternion<Type> &quaternion)
    {
        *this = *this * quaternion;
        return *this;
    }

    template<typename Type>
    inline Quaternion<Type> operator +(const Quaternion<Type> &lquaternion, const Quaternion<Type> &rquaternion)
    {
        return { lquaternion.x + rquaternion.x, lquaternion.y + rquaternion.y, lquaternion.z + rquaternion.z, lquaternion.w + rquaternion.w };
    }

    template<typename Type>
    inline Quaternion<Type> operator -(const Quaternion<Type> &lquaternion, const Quaternion<Type> &rquaternion)
    {
        return { lquaternion.x - rquaternion.x, lquaternion.y - rquaternion.y, lquaternion.z - rquaternion.z, lquaternion.w - rquaternion.w };
    }

    template<typename Type>
    inline Quaternion<Type> operator *(const Quaternion<Type> &lquaternion, const Quaternion<Type> &rquaternion)
    {
        Type A, B, C, D, E, F, G, H;

        A = (lquaternion.w + lquaternion.x) * (rquaternion.w + rquaternion.x);
        B = (lquaternion.z - lquaternion.y) * (rquaternion.y - rquaternion.z);
        C = (lquaternion.x - lquaternion.w) * (rquaternion.y + rquaternion.z);
        D = (lquaternion.y + lquaternion.z) * (rquaternion.x - rquaternion.w);
        E = (lquaternion.x + lquaternion.z) * (rquaternion.x + rquaternion.y);
        F = (lquaternion.x - lquaternion.z) * (rquaternion.x - rquaternion.y);
        G = (lquaternion.w + lquaternion.y) * (rquaternion.w - rquaternion.z);
        H = (lquaternion.w - lquaternion.y) * (rquaternion.w + rquaternion.z);

        return {
            A - (E + F + G + H) * Type(0.5),
            -C + (E - F + G - H) * Type(0.5),
            -D + (E - F - G + H) * Type(0.5),
            B + (-E - F + G + H) * Type(0.5)
        };
        /*Dim res As TQuat
            res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
            res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y
            res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x
            res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
            quat_mul_quat = res*/

        /*return Quaternion<Type>(
            lquaternion.w * rquaternion.x + lquaternion.x * rquaternion.w + lquaternion.y * rquaternion.z - lquaternion.z * rquaternion.y,
            lquaternion.w * rquaternion.y - lquaternion.x * rquaternion.z + lquaternion.y * rquaternion.w + lquaternion.z * rquaternion.x,
            lquaternion.w * rquaternion.z + lquaternion.x * rquaternion.y - lquaternion.y * rquaternion.x + lquaternion.z * rquaternion.w,
            lquaternion.w * rquaternion.w - lquaternion.x * rquaternion.x - lquaternion.y * rquaternion.y - lquaternion.z * rquaternion.z
        );*/
    }

    template<typename Type>
    inline Quaternion<Type> operator /(const Quaternion<Type> &lquaternion, const Quaternion<Type> &rquaternion)
    {
        return { lquaternion.x / rquaternion.x, lquaternion.y / rquaternion.y, lquaternion.z / rquaternion.z, lquaternion.w / rquaternion.w };
    }

    template<typename Type>
    inline Quaternion<Type> operator *(const Quaternion<Type> &quaternion, Type value)
    {
        return { quaternion.x * value, quaternion.y * value, quaternion.z * value, quaternion.w * value };
    }

    template<typename Type>
    inline Quaternion<Type> operator /(const Quaternion<Type> &quaternion, Type value)
    {
        return { quaternion.x / value, quaternion.y / value, quaternion.z / value, quaternion.w / value };
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getEulerRotation(Type xAngle, Type yAngle, Type zAngle, RotationOrder rotationOrder)
    {
        switch(rotationOrder)
        {
        case RotationOrder::XYZ:
            return getXYZEulerRotation(xAngle, yAngle, zAngle);
        case RotationOrder::XZY:
            return getXZYEulerRotation(xAngle, yAngle, zAngle);
        case RotationOrder::YXZ:
            return getYXZEulerRotation(xAngle, yAngle, zAngle);
        case RotationOrder::YZX:
            return getYZXEulerRotation(xAngle, yAngle, zAngle);
        case RotationOrder::ZXY:
            return getZXYEulerRotation(xAngle, yAngle, zAngle);
        case RotationOrder::ZYX:
            return getZYXEulerRotation(xAngle, yAngle, zAngle);
        }
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getXYZEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getXRotation(xAngle) *
            Quaternion::getYRotation(yAngle) *
            Quaternion::getZRotation(zAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getXZYEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getXRotation(xAngle) *
            Quaternion::getZRotation(zAngle) *
            Quaternion::getYRotation(yAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getYXZEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getYRotation(yAngle) *
            Quaternion::getXRotation(xAngle) *
            Quaternion::getZRotation(zAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getYZXEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getYRotation(yAngle) *
            Quaternion::getZRotation(zAngle) *
            Quaternion::getXRotation(xAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getZXYEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getZRotation(zAngle) *
            Quaternion::getXRotation(xAngle) *
            Quaternion::getYRotation(yAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getZYXEulerRotation(Type xAngle, Type yAngle, Type zAngle)
    {
        return Quaternion::getZRotation(zAngle) *
            Quaternion::getYRotation(yAngle) *
            Quaternion::getXRotation(xAngle);
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getNormalized() const
    {
        return Quaternion(*this).normalize();
    }

    template<typename Type>
    inline Quaternion<Type> Quaternion<Type>::getReflected() const
    {
        return Quaternion(*this).reflect();
    }

    template<typename Type>
    inline Quaternion<Type> &Quaternion<Type>::normalize()
    {
        Type magnitude = sqrtf(x * x + y * y + z * z + w * w);
        w = w / magnitude;
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
        return *this;
    }

    template<typename Type>
    inline Quaternion<Type> &Quaternion<Type>::reflect()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    template<typename Type>
    inline void Quaternion<Type>::rotateVector(Vector<Type> &vector) const
    {
        //TODO: optimize
        vector = vector * toMatrix();
    }

    template<typename Type>
    inline Vector<Type> Quaternion<Type>::getRotatedVector(const Vector<Type> &vector) const
    {
        return vector * toMatrix();
    }

}

using FloatQuaternion = Templates::Quaternion<float>;
using DoubleQuaternion = Templates::Quaternion<double>;
using IntegerQuaternion = Templates::Quaternion<int32_t>;
using Quaternion = Templates::Quaternion<FloatType>;

}

#include <iostream>

template<typename Type>
inline std::ostream& operator<<(std::ostream& stream, const Math::Templates::Quaternion<Type> &quaternion)
{
    return stream << "Quaternion(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
}

