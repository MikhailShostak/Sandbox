#pragma once

#include "Aliases.hpp"

#define DECLARE_NESTED_TYPE_SUBSTITUTION(Name, Alias)\
namespace Meta::Details\
{\
    template<typename Type>\
    constexpr static typename Type::Alias &Check ## Name(Type*);\
    constexpr static False Check ## Name(...);\
}\
namespace Meta\
{\
template<typename ClassType>\
struct Get ## Name\
{\
    using Type = std::remove_reference_t<decltype(Details::Check ## Name(static_cast<ClassType *>(nullptr)))>;\
};\
template<typename ClassType>\
struct Has ## Name\
{\
    constexpr static bool Value = !std::is_same_v<typename Get ## Name<ClassType>::Type, False>;\
};\
}
