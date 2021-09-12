#pragma once

#include "Substitution.hpp"

DECLARE_NESTED_TYPE_SUBSTITUTION(BaseType, Super);

namespace Meta
{

namespace Details
{

template<typename Type>
constexpr inline auto WalkToRootType()
{
    if constexpr (HasBaseType<Type>::Value)
    {
        return WalkToRootType<typename GetBaseType<Type>::Type>();
    }
    else
    {
        return Type{};
    }
}

}

template<typename Type>
using RootType = decltype(Details::WalkToRootType<Type>());

}
