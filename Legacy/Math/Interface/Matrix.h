#pragma once

#include "BasicConstants.h"
#include "Vector.h"

#include <array>
#include <initializer_list>

namespace Math
{

namespace Templates
{

template<typename Type>
struct Quaternion;

template<typename Type>
struct Matrix
{
    static Matrix getTranslation(const Vector<Type> &vector);
    static Matrix getXRotation(float angle);
    static Matrix getYRotation(float angle);
    static Matrix getZRotation(float angle);
    static Matrix getScale2(const Vector<Type> &vector);
    static Matrix getScale3(const Vector<Type> &vector);

    static Matrix getPerspective(Type aspect, Type fov, Type near, Type far);

    static Matrix getIdentity()
    {
        static Matrix m{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        };
        return m;
    }

    std::array<Vector<Type>, 4> data;

    Matrix();

    Matrix(
        Type v1, Type v2, Type v3, Type v4,
        Type v5, Type v6, Type v7, Type v8,
        Type v9, Type v10, Type v11, Type v12,
        Type v13, Type v14, Type v15, Type v16):
        data{ { { v1, v2, v3, v4 }, { v5, v6, v7, v8 }, { v9, v10, v11, v12 }, { v13, v14, v15, v16 } } }
    {

    }

    explicit Matrix(const std::array<Vector<Type>, 4> &data);

    Type *getData() { return &data[0][0]; }
    const Type *getData() const { return &data[0][0]; }

    Matrix getTransposed() const
    {
        Matrix m;
        for (auto i = 0; i < 4; ++i)
        {
            for (auto j = 0; j < 4; ++j)
            {
                m[i][j] = data[j][i];
            }
        }
        return m;
    }

    void transpose()
    {
        Type temp;
        for (auto i = 0; i < 4; ++i)
        {
            for (auto j = 0; j < 4; ++j)
            {
                temp = data[i][j];
                data[i][j] = data[j][i];
                data[j][i] = temp;
            }
        }
    }

    Matrix getInversed() const
    {
        Matrix<Type> m = *this;

        Type subFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        Type subFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        Type subFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        Type subFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        Type subFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        Type subFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        Type subFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        Type subFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        Type subFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        Type subFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        Type subFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        Type subFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        Type subFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        Type subFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
        Type subFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
        Type subFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
        Type subFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
        Type subFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
        Type subFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        Matrix<Type> inverseMatrix;
        inverseMatrix[0][0] = +(m[1][1] * subFactor00 - m[1][2] * subFactor01 + m[1][3] * subFactor02);
        inverseMatrix[0][1] = -(m[1][0] * subFactor00 - m[1][2] * subFactor03 + m[1][3] * subFactor04);
        inverseMatrix[0][2] = +(m[1][0] * subFactor01 - m[1][1] * subFactor03 + m[1][3] * subFactor05);
        inverseMatrix[0][3] = -(m[1][0] * subFactor02 - m[1][1] * subFactor04 + m[1][2] * subFactor05);

        inverseMatrix[1][0] = -(m[0][1] * subFactor00 - m[0][2] * subFactor01 + m[0][3] * subFactor02);
        inverseMatrix[1][1] = +(m[0][0] * subFactor00 - m[0][2] * subFactor03 + m[0][3] * subFactor04);
        inverseMatrix[1][2] = -(m[0][0] * subFactor01 - m[0][1] * subFactor03 + m[0][3] * subFactor05);
        inverseMatrix[1][3] = +(m[0][0] * subFactor02 - m[0][1] * subFactor04 + m[0][2] * subFactor05);

        inverseMatrix[2][0] = +(m[0][1] * subFactor06 - m[0][2] * subFactor07 + m[0][3] * subFactor08);
        inverseMatrix[2][1] = -(m[0][0] * subFactor06 - m[0][2] * subFactor09 + m[0][3] * subFactor10);
        inverseMatrix[2][2] = +(m[0][0] * subFactor11 - m[0][1] * subFactor09 + m[0][3] * subFactor12);
        inverseMatrix[2][3] = -(m[0][0] * subFactor08 - m[0][1] * subFactor10 + m[0][2] * subFactor12);

        inverseMatrix[3][0] = -(m[0][1] * subFactor13 - m[0][2] * subFactor14 + m[0][3] * subFactor15);
        inverseMatrix[3][1] = +(m[0][0] * subFactor13 - m[0][2] * subFactor16 + m[0][3] * subFactor17);
        inverseMatrix[3][2] = -(m[0][0] * subFactor14 - m[0][1] * subFactor16 + m[0][3] * subFactor18);
        inverseMatrix[3][3] = +(m[0][0] * subFactor15 - m[0][1] * subFactor17 + m[0][2] * subFactor18);

        Type determinant =
            +m[0][0] * inverseMatrix[0][0]
            + m[0][1] * inverseMatrix[0][1]
            + m[0][2] * inverseMatrix[0][2]
            + m[0][3] * inverseMatrix[0][3];

        for (size_t i = 0; i < 16; ++i)
        {
            inverseMatrix[0][i] /= determinant;
        }

        return inverseMatrix.getTransposed();
    }

    void inverse()
    {
        //TODO: improve code
        *this = getInversed();
    }

    Matrix getTranslated(const Vector<Type> &point) const;
    Matrix getScaled2(const Vector<Type> &size) const;
    Matrix getScaled3(const Vector<Type> &size) const;
    Matrix getRotated(const Quaternion<Type> &quaternion) const;

    void translate(const Vector<Type> &point);
    void scale2(const Vector<Type> &size);
    void scale3(const Vector<Type> &size);
    void rotate(const Quaternion<Type> &quaternion);

    Vector<Type> &operator[](size_t index) { return data[index]; }
    const Vector<Type> &operator[](size_t index) const { return data[index]; }

    /*Matrix &operator +=(const Type &value)
    {
        //TODO: WTF?
        data[0][0] += value;
        data[0][1] += value;
        data[0][2] += value;
        data[0][3] += value;
        data[1][0] += value;
        data[1][1] += value;
        data[1][2] += value;
        data[1][3] += value;
        data[2][0] += value;
        data[2][1] += value;
        data[2][2] += value;
        data[2][3] += value;
        data[3][0] += value;
        data[3][1] += value;
        data[3][2] += value;
        data[3][3] += value;

        return *this;
    }

    Matrix &operator -=(const Type &value)
    {
        //TODO: WTF?
        data[0][0] -= value;
        data[0][1] -= value;
        data[0][2] -= value;
        data[0][3] -= value;
        data[1][0] -= value;
        data[1][1] -= value;
        data[1][2] -= value;
        data[1][3] -= value;
        data[2][0] -= value;
        data[2][1] -= value;
        data[2][2] -= value;
        data[2][3] -= value;
        data[3][0] -= value;
        data[3][1] -= value;
        data[3][2] -= value;
        data[3][3] -= value;

        return *this;
    }

    Matrix &operator *=(const Type &value)
    {
        //TODO: WTF?
        data[0][0] *= value;
        data[0][1] *= value;
        data[0][2] *= value;
        data[0][3] *= value;
        data[1][0] *= value;
        data[1][1] *= value;
        data[1][2] *= value;
        data[1][3] *= value;
        data[2][0] *= value;
        data[2][1] *= value;
        data[2][2] *= value;
        data[2][3] *= value;
        data[3][0] *= value;
        data[3][1] *= value;
        data[3][2] *= value;
        data[3][3] *= value;

        return *this;
    }

    Matrix &operator /=(const Type &value)
    {
        //TODO: WTF?
        data[0][0] /= value;
        data[0][1] /= value;
        data[0][2] /= value;
        data[0][3] /= value;
        data[1][0] /= value;
        data[1][1] /= value;
        data[1][2] /= value;
        data[1][3] /= value;
        data[2][0] /= value;
        data[2][1] /= value;
        data[2][2] /= value;
        data[2][3] /= value;
        data[3][0] /= value;
        data[3][1] /= value;
        data[3][2] /= value;
        data[3][3] /= value;

        return *this;
    }*/

};

}

}

#include "Quaternion.h"
#include "Vector.h"

namespace Math
{

namespace Templates
{

template<typename Type>
inline Matrix<Type> Matrix<Type>::getTranslation(const Vector<Type> &vector)
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        vector.x, vector.y, vector.z, 1,
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getXRotation(float angle)
{
    angle *= Constants::DegreeToRadianRatio;
    return {
        1, 0, 0, 0,
        0, cos(angle), sin(angle), 0,
        0, -sin(angle), cos(angle), 0,
        0, 0, 0, 1
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getYRotation(float angle)
{
    angle *= Constants::DegreeToRadianRatio;
    return {
        cos(angle), 0, -sin(angle), 0,
        0, 1, 0, 0,
        sin(angle), 0, cos(angle), 0,
        0, 0, 0, 1
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getZRotation(float angle)
{
    angle *= Constants::DegreeToRadianRatio;
    return {
        cos(angle), sin(angle), 0, 0,
        -sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getScale2(const Vector<Type> &vector)
{
    return {
        vector.x, 0, 0, 0,
        0, vector.y, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getScale3(const Vector<Type> &vector)
{
    return {
        vector.x, 0, 0, 0,
        0, vector.y, 0, 0,
        0, 0, vector.z, 0,
        0, 0, 0, 1,
    };
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getPerspective(Type aspect, Type fieldOfView, Type nearValue, Type farValue)
{

    /*assert(aspect != static_cast<T>(0));
    assert(zFar != zNear);

#ifdef GLM_FORCE_RADIANS
    T const rad = fovy;
#else
#		pragma message("GLM: perspective function taking degrees as a parameter is deprecated. #define GLM_FORCE_RADIANS before including GLM headers to remove this message.")
    T const rad = glm::radians(fovy);
#endif

    T tanHalfFovy = tan(rad / static_cast<T>(2));

    detail::tmat4x4<T, defaultp> Result(static_cast<T>(0));
    Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
    Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
    Result[2][2] = - (zFar + zNear) / (zFar - zNear);
    Result[2][3] = - static_cast<T>(1);
    Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
    return Result;*/

    Type rad = fieldOfView * Constants::DegreeToRadianRatio;
    Type tanHalfFovy = tan(rad / static_cast<Type>(2));

    Matrix<Type> result;
    result[0][0] = static_cast<Type>(1) / (aspect * tanHalfFovy);
    result[1][1] = static_cast<Type>(1) / (tanHalfFovy);
    result[2][2] = -(farValue + nearValue) / (farValue - nearValue);
    result[2][3] = -static_cast<Type>(1);
    result[3][2] = -(static_cast<Type>(2) * farValue * nearValue) / (farValue - nearValue);
    return result;
}

template<typename Type>
inline Matrix<Type>::Matrix():
    data{ { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } }
{
}

template<typename Type>
inline Matrix<Type>::Matrix(const std::array<Vector<Type>, 4> &data):
    data(data)
{
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getTranslated(const Vector<Type> &point) const
{
    //TODO: improve code
    return Matrix(*this) * Matrix::getTranslation(point);
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getRotated(const Quaternion<Type> &quaternion) const
{
    //TODO: improve code
    return Matrix(this) * quaternion.toMatrix();
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::getScaled2(const Vector<Type> &size) const
{
    //TODO: improve code
    return Matrix(*this) * Matrix::getScale2(size);
}


template<typename Type>
inline Matrix<Type> Matrix<Type>::getScaled3(const Vector<Type> &size) const
{
    //TODO: improve code
    return Matrix(*this) * Matrix::getScale3(size);
}

template<typename Type>
inline void Matrix<Type>::translate(const Vector<Type> &point)
{
    *this = getTranslated(point);
}

template<typename Type>
inline void Matrix<Type>::rotate(const Quaternion<Type> &quaternion)
{
    //TODO: improve code
    *this = getRotated(quaternion);
}

template<typename Type>
inline void Matrix<Type>::scale2(const Vector<Type> &size)
{
    //TODO: improve code
    *this = getScaled2(size);
}

template<typename Type>
inline void Matrix<Type>::scale3(const Vector<Type> &size)
{
    //TODO: improve code
    *this = getScaled3(size);
}

template<typename Type>
inline Matrix<Type> operator *(const Matrix<Type> &m1, const Matrix<Type> &m2)
{
    Matrix<Type> m{};
    for (uint8_t i = 0; i < 4; ++i)
    {
        for (uint8_t j = 0; j < 4; ++j)
        {
            for (uint8_t k = 0; k < 4; ++k)
            {
                m[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return m;
}

template<typename Type>
inline Vector<Type> operator *(const Vector<Type> &v, const Matrix<Type> &m)
{
    Type t[4] = { v.x, v.y, v.z, Type(1) };
    Type r[4] = {};
    for (uint8_t i = 0; i < 4; ++i)
    {
        for (uint8_t j = 0; j < 4; ++j)
        {
            r[i] += m[j][i] * t[j];
        }
    }
    return Vector<Type>{ r[0], r[1], r[2] } / r[3];
}

}

using FloatMatrix = Templates::Matrix<float>;
using DoubleMatrix = Templates::Matrix<double>;
using IntegerMatrix = Templates::Matrix<int32_t>;
using Matrix = Templates::Matrix<FloatType>;

}

#include <iostream>

template<typename Type>
inline std::ostream& operator<<(std::ostream& stream, const Math::Templates::Matrix<Type> &matrix)
{
    return stream << "Matrix():\n"
    " {" << matrix[0][0] << ", " << matrix[0][1] << ", " << matrix[0][2] << ", " << matrix[0][3] << "}\n"
    " {" << matrix[1][0] << ", " << matrix[1][1] << ", " << matrix[1][2] << ", " << matrix[1][3] << "}\n"
    " {" << matrix[2][0] << ", " << matrix[2][1] << ", " << matrix[2][2] << ", " << matrix[2][3] << "}\n"
    " {" << matrix[3][0] << ", " << matrix[3][1] << ", " << matrix[3][2] << ", " << matrix[3][3] << "}";
}
