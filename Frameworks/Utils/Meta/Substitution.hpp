#pragma once

#include "Aliases.hpp"

#define DECLARE_NESTED_TYPE_SUBSTITUTION(Name, Alias)\
namespace Meta::Details\
{\
    constexpr static False Check ## Name(...);\
    template<typename Type>\
    constexpr static typename Type::Alias Check ## Name(Type);\
}\
namespace Meta\
{\
template<typename ClassType>\
struct Get ## Name\
{\
    using Type = decltype(Details::Check ## Name(ClassType{}));\
};\
template<typename ClassType>\
struct Has ## Name\
{\
    constexpr static bool Value = !std::is_same_v<typename Get ## Name<ClassType>::Type, False>;\
};\
}
