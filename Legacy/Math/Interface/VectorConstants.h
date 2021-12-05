#pragma once

#include "BasicConstants.h"
#include "Vector.h"

namespace Math
{

namespace Constants
{

constexpr Vector NullVector = { 0, 0, 0, 0 };
constexpr Vector PositiveVectorSpace = { 1, 1, 1, 1 };
constexpr Vector NegativeVectorSpace = -PositiveVectorSpace;

constexpr Vector XVector = { 1, 0, 0, 0 };
constexpr Vector YVector = { 0, 1, 0, 0 };
constexpr Vector ZVector = { 0, 0, 1, 0 };
constexpr Vector WVector = { 0, 0, 0, 1 };

constexpr Vector NagativeXVector = -XVector;
constexpr Vector NagativeYVector = -YVector;
constexpr Vector NagativeZVector = -ZVector;
constexpr Vector NagativeWVector = -WVector;

}

}
