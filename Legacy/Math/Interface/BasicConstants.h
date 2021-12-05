#pragma once

#include <cstdint>
#include <cmath>

namespace Math
{

#if UseDoublePrecision
using FloatType = double;
#else
using FloatType = float;
#endif

namespace Constants
{

constexpr FloatType E = 2.718281828459045235360287471352662497757247093699959574966L;
constexpr FloatType Log2E = 1.442695040888963407359924681001892137426645954152985934135L;
constexpr FloatType Log10E = 0.434294481903251827651128918916605082294397005803666566114L;
constexpr FloatType Ln2 = 0.693147180559945309417232121458176568075500134360255254120L;
constexpr FloatType Ln10 = 2.302585092994045684017991454684364207601101488628772976033L;

constexpr FloatType Pi = 3.141592653589793238462643383279502884197169399375105820974L;
constexpr FloatType PiTwoTimes = Pi * 2;
constexpr FloatType InversePi = 1 / Pi;
constexpr FloatType InversePiTwoTimes = InversePi * 2;

constexpr FloatType SqrtPi = 1.772453850905516027298167483341145182797549456122387128213L;
constexpr FloatType SqrtPiTwoTimes = SqrtPi * 2;
constexpr FloatType InverseSqrtPi = 1 / SqrtPi;
constexpr FloatType InverseSqrtPiTwoTimes = InverseSqrtPi * 2;

constexpr FloatType Sqrt2 = 1.414213562373095048801688724209698078569671875376948073176L;
constexpr FloatType Sqrt2TwoTimes = Sqrt2 * 2;
constexpr FloatType InverseSqrt2 = 1 / Sqrt2;
constexpr FloatType InverseSqrt2TwoTimes = InverseSqrt2 * 2;

constexpr FloatType DegreeToRadianRatio = Pi / 180.0L;
constexpr FloatType RadiansToDegreeRatio = 180.0L / Pi;

}

}
