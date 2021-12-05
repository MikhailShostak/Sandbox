#pragma once

#define ADeclareFlagsOperators(Type)\
inline Type operator +(Type left, Type right) { return Type(uint64_t(left) | uint64_t(right)); }\
inline Type &operator +=(Type &left, Type right) { return left = left + right; }\
inline Type operator -(Type left, Type right) { return Type(uint64_t(left) & ~uint64_t(right)); }\
inline Type &operator -=(Type &left, Type right) { return left = left - right; }\
inline bool operator &(Type left, Type right) { return uint64_t(left) & uint64_t(right); }