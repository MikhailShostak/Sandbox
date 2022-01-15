#pragma once

#define DECLARE_FLAG_OPERATORS(Type) \
inline Type operator~ (Type v) { return (Type)~(std::int64_t)v; } \
inline Type operator| (Type l, Type r) { return (Type)((std::int64_t)l | (std::int64_t)r); } \
inline Type operator& (Type l, Type r) { return (Type)((std::int64_t)l & (std::int64_t)r); } \
inline Type operator^ (Type l, Type r) { return (Type)((std::int64_t)l ^ (std::int64_t)r); } \
inline Type& operator|= (Type& l, Type r) { return (Type&)((std::int64_t&)l |= (std::int64_t)r); } \
inline Type& operator&= (Type& l, Type r) { return (Type&)((std::int64_t&)l &= (std::int64_t)r); } \
inline Type& operator^= (Type& l, Type r) { return (Type&)((std::int64_t&)l ^= (std::int64_t)r); } \
