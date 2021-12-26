#pragma once

#include "Meta/Inheritance.hpp"

namespace Memory
{

template<typename Type>
inline constexpr Type *Null = reinterpret_cast<Type*>(0);

template<typename Type>
[[nodiscard]] inline Type *Allocate()
{
    return new Type;
}

template<typename Type, typename ReturnType>
[[nodiscard]] inline ReturnType *AllocateAs()
{
    return Allocate<Type>();
}

template<typename Type, typename ...Arguments>
[[nodiscard]] inline Type *Create(Arguments &&...arguments)
{
    return new Type(std::forward<Arguments>(arguments)...);
}

template<typename Type, typename ReturnType, typename ...Arguments>
[[nodiscard]] inline ReturnType *CreateAs(Arguments &&...arguments)
{
    return Create<Type>(std::forward<Arguments>(arguments)...);
}

template<typename Type, typename ...Arguments>
[[nodiscard]] inline void *CreateAsVoid(Arguments &&...arguments)
{
    return Create<Type>(std::forward<Arguments>(arguments)...);
}

template<typename Type>
inline void Destroy(Type *object)
{
    delete object;
}

template<typename Type>
inline void DestroyAs(void *object)
{
    delete static_cast<Type *>(object);
}

template<typename DerivedType, typename BaseType = DerivedType>
struct Constructor
{
    template<typename ...Arguments>
    [[nodiscard]] inline static DerivedType *Create(Arguments &&...arguments)
    {
        return Constructor<DerivedType, typename Meta::GetBaseType<BaseType>::Type>::Create(std::forward<Arguments>(arguments)...);
    }
};

template<typename Type>
struct Constructor<Type, Meta::False>
{
    template<typename ...Arguments>
    [[nodiscard]] inline static Type *Create(Arguments &&...arguments)
    {
        return Memory::Create<Type>(std::forward<Arguments>(arguments)...);
    }
};

}

template<typename Type, typename ...Arguments>
[[nodiscard]] inline Type *Create(Arguments &&...arguments)
{
    return Memory::Constructor<Type>::Create(std::forward<Arguments>(arguments)...);
}

template<typename Type, typename ...Arguments>
[[nodiscard, deprecated("Use Create instead")]] inline SharedReference<Type> CreateShared(Arguments &&...arguments)
{
    return SharedReference<Type>(Create<Type>(std::forward<Arguments>(arguments)...));
}

template<typename Type, typename ReturnType, typename ...Arguments>
[[nodiscard]] inline ReturnType *CreateAs(Arguments &&...arguments)
{
    return Create<Type>(std::forward<Arguments>(arguments)...);
}

template<typename Type>
inline void Destroy(Type *object)
{
    Memory::Destroy(object);
}

template<typename Type>
inline void DestroyAs(void *object)
{
    Memory::DestroyAs<Type>(object);
}
