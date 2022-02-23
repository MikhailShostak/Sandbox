#pragma once

#include "Memory/Allocation.hpp"
#include "Memory/Assets.hpp"
#include "Memory/References.hpp"
#include "Serialization/Serialization.hpp"
#include "Text/String.hpp"

namespace Reflection
{

template<typename ClassType>
struct MetaObject : public MetaObject<typename Meta::GetBaseType<ClassType>::Type>
{
    using Super = MetaObject<typename Meta::GetBaseType<ClassType>::Type>;

    MetaObject(const char *name)
    {
        Super::m_Name = name;
        Super::ConstructorFunction = []() -> void* { return CreateAs<ClassType, Meta::RootType<ClassType>>(); };
        Super::DestructorFunction = &::DestroyAs<ClassType>;
        if constexpr (true) //TODO: disable if serialization is not implemented for class
        {
            Super::SerializeFunction = [](const void *object, Serialization::Data &data)
            {
                auto base = reinterpret_cast<const Meta::RootType<ClassType> *>(object);
                auto derived = static_cast<const ClassType *>(base);
                Serialization::Serialize(*derived, data);
            };
            Super::DeserializeFunction = [](const Serialization::Data &data, void *object)
            {
                auto base = reinterpret_cast<Meta::RootType<ClassType> *>(object);
                auto derived = static_cast<ClassType *>(base);
                Serialization::Deserialize(data, *derived);
            };
        }
    }

    UniqueReference<ClassType> Create()
    {
        auto base = reinterpret_cast<Meta::RootType<ClassType> *>(Super::ConstructorFunction());
        return UniqueReference<ClassType>{ static_cast<ClassType *>(base) };
    }
protected:
    MetaObject() {}
};

using MetaObjectRootType = Meta::False;

template<>
struct MetaObject<MetaObjectRootType>
{
public:
    virtual ~MetaObject() {};

    const char *m_Name = nullptr;
    template<typename ClassType>
    void Serialize(const ClassType &value, Serialization::Data &data) const
    {
        auto base = static_cast<const Meta::RootType<ClassType>*>(&value);
        SerializeFunction(base, data);
    }
    template<typename ClassType>
    void Deserialize(const Serialization::Data &data, ClassType &value) const
    {
        auto base = static_cast<Meta::RootType<ClassType>*>(&value);
        DeserializeFunction(data, base);
    }
protected:
    Meta::ConstructorPointer<void> ConstructorFunction;
    Meta::DestructorPointer<void> DestructorFunction;
    Meta::VoidFunctionPointer<const void *, Serialization::Data &> SerializeFunction;
    Meta::VoidFunctionPointer<const Serialization::Data &, void *> DeserializeFunction;
};

}
