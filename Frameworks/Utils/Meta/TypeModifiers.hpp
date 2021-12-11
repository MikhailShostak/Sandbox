#pragma once

namespace Meta
{

template<typename From, typename To>
using CopyConst = std::conditional_t<std::is_const_v<std::remove_reference_t<From>>, std::add_const_t<To>, To>;

template<typename From, typename To>
using CopyVolatile = std::conditional_t<std::is_volatile_v<std::remove_reference_t<From>>, std::add_volatile_t<To>, To>;

template<typename From, typename To>
using CopyCV = CopyConst<From, CopyVolatile<From, To>>;

template<typename From, typename To>
using CopyPointer = std::conditional_t<std::is_pointer_v<std::remove_reference_t<From>>, std::add_pointer_t<To>, To>;

template<typename From, typename To>
using CopyLValueReference = std::conditional_t<std::is_lvalue_reference_v<From>, std::add_lvalue_reference_t<To>, To>;

template<typename From, typename To>
using CopyRValueReference = std::conditional_t<std::is_rvalue_reference_v<From>, std::add_rvalue_reference_t<To>, To>;

template<typename From, typename To>
using CopyReference = CopyLValueReference<From, CopyRValueReference<From, To>>;

template<typename From, typename To>
using CopyModifiers = CopyReference<From, CopyCV<From, CopyPointer<From, CopyCV<std::remove_pointer_t<std::remove_reference_t<From>>, To>>>>;

template<typename Type>
using RemoveExtraPointerReference = std::conditional_t<std::is_pointer_v<std::remove_reference_t<Type>>, std::remove_reference_t<Type>, Type>;

}
