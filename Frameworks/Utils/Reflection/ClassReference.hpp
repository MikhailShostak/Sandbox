#pragma once

#include "Reflection/MetaObjectStorage.hpp"

namespace Reflection
{

template<typename Type>
using ClassReference = Reflection::MetaObject<Type>*;

inline ClassReference<MetaObjectRootType> Find(size_t TypeHash)
{
    auto it = GetTypes().find(TypeHash);
    if (it == GetTypes().end())
    {
        return nullptr;
    }

    return it->second.get();
}

template<typename Type>
inline ClassReference<Type> Find()
{
    return static_cast<ClassReference<Type>>(Find(typeid(Type).hash_code()));
}

template<typename Type>
inline ClassReference<Type> Find(const String& name)
{
    auto it = ranges::find_if(GetTypes(), [&name](auto& pair) { return pair.second->m_Name == name; });
    if (it == GetTypes().end())
    {
        return nullptr;
    }

    return dynamic_cast<ClassReference<Type>>(it->second.get());
}

template<typename Type>
inline ClassReference<Type> Find(const Type& Object)
{
    return static_cast<ClassReference<Type>>(Find(typeid(Object).hash_code()));
}

template<typename Type>
inline Array<ClassReference<Type>> FindAll()
{
    return GetTypes()
        | ranges::views::filter([](auto& pair) { return dynamic_cast<ClassReference<Type>>(pair.second.get()); })
        | ranges::views::transform([](auto& pair) { return static_cast<ClassReference<Type>>(pair.second.get()); })
        | ranges::to<Array<ClassReference<Type>>>();
}

template<typename Type>
inline UniqueReference<Type> Create(const String& name)
{
    ClassReference<Type> classReference = Find<Type>(name);
    if (!classReference)
    {
        return nullptr;
    }

    return classReference->Create();
}

}

using Reflection::ClassReference;
