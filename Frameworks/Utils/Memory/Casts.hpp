#pragma once

#include "Meta/TypeModifiers.hpp"

#include "Memory/References.hpp"

template<typename Type>
inline constexpr decltype(auto) ConstCast(const Type &value)
{
    return const_cast<Type &>(value);
}

template<typename Type>
inline constexpr decltype(auto) ConstCast(const Type &&value)
{
    return const_cast<Type &&>(value);
}

template<typename Type>
inline constexpr decltype(auto) ConstCast(const Type *value)
{
    return const_cast<Type *>(value);
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(From &from)
{
    return reinterpret_cast<To &>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(From &&from)
{
    return reinterpret_cast<To &&>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(From *from)
{
    return reinterpret_cast<To *>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(From &&from)
{
    using ResultType = Meta::CopyModifiers<Meta::RemoveExtraPointerReference<decltype(from)>, To>;
    return dynamic_cast<ResultType>(std::forward<From>(from));
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(From &&from)
{
    using ResultType = Meta::CopyModifiers<Meta::RemoveExtraPointerReference<decltype(from)>, To>;
    return static_cast<ResultType>(std::forward<From>(from));
}

template<typename To, typename From>
inline constexpr decltype(auto) ConstCast(const SharedReference<From> &from)
{
    return std::const_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) ConstCast(SharedReference<From> &from)
{
    return std::const_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) ConstCast(SharedReference<From> &&from)
{
    return std::const_pointer_cast<To>(std::move(from));
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(const SharedReference<From> &from)
{
    return boost::reinterpret_pointer_cast<To>(from); //TODO: fix macOS
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(SharedReference<From> &from)
{
    return boost::reinterpret_pointer_cast<To>(from); //TODO: fix macOS
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(SharedReference<From> &&from)
{
    return boost::reinterpret_pointer_cast<To>(std::move(from)); //TODO: fix macOS
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(const SharedReference<From> &from)
{
    return std::dynamic_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(SharedReference<From> &from)
{
    return std::dynamic_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(SharedReference<From> &&from)
{
    return std::dynamic_pointer_cast<To>(std::move(from));
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(const SharedReference<From> &from)
{
    return std::static_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(SharedReference<From> &from)
{
    return std::static_pointer_cast<To>(from);
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(SharedReference<From> &&from)
{
    return std::static_pointer_cast<To>(std::move(from));
}

template<typename To, typename From>
inline constexpr decltype(auto) ConstCast(UniqueReference<From> &from)
{
    return UniqueReference<To>{ ConstCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) ConstCast(UniqueReference<From> &&from)
{
    return UniqueReference<To>{ ConstCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(UniqueReference<From> &from)
{
    return UniqueReference<To>{ ReinterpretCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) ReinterpretCast(UniqueReference<From> &&from)
{
    return UniqueReference<To>{ ReinterpretCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(UniqueReference<From> &from)
{
    return UniqueReference<To>{ DynamicCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) DynamicCast(UniqueReference<From> &&from)
{
    return UniqueReference<To>{ DynamicCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(UniqueReference<From> &from)
{
    return UniqueReference<To>{ StaticCast<To>(from.release()) };
}

template<typename To, typename From>
inline constexpr decltype(auto) StaticCast(UniqueReference<From> &&from)
{
    return UniqueReference<To>{ StaticCast<To>(from.release()) };
}
