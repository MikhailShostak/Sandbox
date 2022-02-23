#pragma once

#include "Reflection/ClassReference.hpp"

namespace Reflection
{

template<typename Type>
inline void Serialize(const Type& value, Serialization::Data& data)
{
    const size_t hash = typeid(value).hash_code();
    auto it = GetTypes().find(hash);
    if (it == GetTypes().end())
    {
        return;
    }

    it->second->Serialize(value, data);
}

template<typename Type>
inline Serialization::Data Serialize(const Type& value)
{
    Serialization::Data data;
    Reflection::Serialize(value, data);
    return data;
}

template<typename Type>
inline void Deserialize(const Serialization::Data& data, Type& value)
{
    const size_t hash = typeid(value).hash_code();
    auto it = GetTypes().find(hash);
    if (it == GetTypes().end())
    {
        return;
    }

    it->second->Deserialize(data, value);
}

template<typename Type>
inline Type Deserialize(const Serialization::Data& data)
{
    Type value;
    Reflection::Deserialize(data, value);
    return value;
}

template<typename Type>
struct MetaObjectTag {};

}

namespace Serialization
{

template<typename Type>
struct Serializer<InputValue, Reflection::MetaObjectTag<Type>>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (data.m_Storage.IsScalar())
        {
            value = Reflection::Find<Type>(data.m_Storage.template as<std::string>());
        }
    }
};

template<typename Type>
struct Serializer<OutputValue, Reflection::MetaObjectTag<Type>>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {
        if (value)
        {
            data.m_Storage = value->m_Name;
        }
    }
};

template<typename Type> struct Serializer<InputValue, Reflection::MetaObject<Type>*> : public Serializer<InputValue, Reflection::MetaObjectTag<Type>> {};
template<typename Type> struct Serializer<OutputValue, Reflection::MetaObject<Type>*> : public Serializer<OutputValue, Reflection::MetaObjectTag<Type>> {};


template<typename Type>
struct Serializer<InputValue, UniqueReference<Type>>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (!data.m_Storage.IsMap())
        {
            return;
        }

        ClassReference<Type> type;
        Serialization::InputValue typeData{};
        typeData.m_Storage = data.m_Storage["Type"].template as<YAML::Node>();
        typeData& type;

        if (!type)
        {
            return;
        }

        value = type->Create();

        Serialization::Data valuesData{};
        valuesData.m_Storage = data.m_Storage["Values"].template as<YAML::Node>();
        Reflection::Deserialize(valuesData, *value);
    }
};

template<typename Type>
struct Serializer<OutputValue, UniqueReference<Type>>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {
        if (!value)
        {
            return;
        }

        ClassReference<Type> type = Reflection::Find(*value.get());
        if (!type)
        {
            return;
        }

        data.m_Storage["Type"] = type->m_Name;

        Serialization::Data valuesData{};
        Reflection::Serialize(*value, valuesData);
        data.m_Storage["Values"] = std::move(valuesData.m_Storage);
    }
};


template<typename Type>
struct Serializer<InputValue, SharedReference<Type>>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (!data.m_Storage.IsMap())
        {
            return;
        }

        const auto& typeNode = data.m_Storage["Type"];
        if (typeNode.IsScalar())
        {
            //TODO: how to serialize it to OutputValue?
            value = AssetStorage::Load<Type>(typeNode.template as<std::string>());
            if (value)
            {
                return;
            }
        }

        ClassReference<Type> type;
        Serialization::InputValue typeData{};
        typeData.m_Storage = typeNode.template as<YAML::Node>();
        typeData& type;

        if (!type)
        {
            return;
        }

        value = SharedReference<Type>(type->Create().release());

        Serialization::Data valuesData{};
        valuesData.m_Storage = data.m_Storage["Values"].template as<YAML::Node>();
        Reflection::Deserialize(valuesData, *value);
    }
};

template<typename Type>
struct Serializer<OutputValue, SharedReference<Type>>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {
        if (!value)
        {
            return;
        }

        ClassReference<Type> type = Reflection::Find(*value.get());
        if (!type)
        {
            return;
        }

        data.m_Storage["Type"] = type->m_Name;

        Serialization::Data valuesData{};
        Reflection::Serialize(*value, valuesData);
        data.m_Storage["Values"] = std::move(valuesData.m_Storage);
    }
};

}
