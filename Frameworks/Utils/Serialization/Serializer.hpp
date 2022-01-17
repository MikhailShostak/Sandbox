#pragma once

#include "Storage.hpp"
#include "Meta/Inheritance.hpp"

namespace Serialization
{

template<typename Type>
struct ObjectSerializer
{
    template<typename DataType, typename ValueType>
    static void Serialize(DataType &&data, ValueType &&value)
    {
        value.Serialize(std::forward<DataType>(data));
    }
};

namespace Details
{
template<typename MapType, typename Type>
inline void ProcessObject(MapType &&map, Type &&value)
{
    using T = std::decay_t<Type>;
    if constexpr (Meta::HasBaseType<T>::Value)
    {
        using Super = typename T::Super;
        using BaseType = std::conditional_t<std::is_rvalue_reference_v<Type>, Super &&, Super &>;
        ProcessObject(std::forward<MapType>(map), std::forward<BaseType>(value));
    }
    ObjectSerializer<T>::Serialize(std::forward<MapType>(map), std::forward<Type>(value));
}
}

template<typename DataType, typename ValueType>
struct Serializer;

template<typename Type>
struct Serializer<InputValue, Type>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue &&data, ValueType &&value)
    {
        using T = typename std::remove_reference_t<ValueType>;
        if constexpr (std::is_scalar_v<T> || std::is_same_v<T, std::string>)
        {
            if (data.m_Storage.IsScalar())
            {
                value = data.m_Storage.template as<T>();
            }
        }
        else
        {
            InputMap map;
            for (const auto &p : data.m_Storage)
            {
                map[p.first.template as<std::string>()].m_Storage = p.second;
            }
            Details::ProcessObject(map, std::forward<ValueType>(value));
        }
    }
};

template<typename Type>
struct Serializer<OutputValue, Type>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue && data, ValueType &&value)
    {
        using T = typename std::remove_reference_t<ValueType>;
        if constexpr (std::is_scalar_v<T> || std::is_same_v<T, std::string>)
        {
            data.m_Storage = std::forward<ValueType>(value);
        }
        else
        {
            OutputMap map;
            Details::ProcessObject(map, std::forward<ValueType>(value));
            for (const auto &[k, v] : map.m_Data)
            {
                bool empty = v.m_Storage.IsNull() || v.m_Storage.IsScalar() && v.m_Storage.Scalar().empty();
                if (!empty)
                {
                    data.m_Storage[k] = std::move(v.m_Storage);
                }
            }
        }
    }
};

template<typename ValueType>
struct ArrayTag;

template<typename KeyType, typename Type>
struct MapTag;

template<typename Type>
struct Serializer<InputValue, ArrayTag<Type>>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue &&data, ValueType &&value)
    {
        if (!data.m_Storage.IsSequence())
        {
            return;
        }

        value.clear();
        value.reserve(data.m_Storage.size());
        for (const auto &node : data.m_Storage)
        {
            Type v{};
            Serialization::InputValue data{};
            data.m_Storage = node.template as<YAML::Node>();
            data & v;
            value.push_back(std::move(v));
        }
    }
};

template<typename Type>
struct Serializer<OutputValue, ArrayTag<Type>>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue &&data, ValueType &&value)
    {
        for (auto &i : value)
        {
            Serialization::OutputValue v{};
            v & i;
            data.m_Storage.push_back(v.m_Storage);
        }
    }
};


template<typename KeyType, typename Type>
struct Serializer<InputValue, MapTag<KeyType, Type>>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue &&data, ValueType &&value)
    {
        if (!data.m_Storage.IsMap())
        {
            return;
        }

        value.clear();
        for (const auto &p : data.m_Storage)
        {
            Type v{};
            Serialization::InputValue data{};
            data.m_Storage = p.second.template as<YAML::Node>();
            data & v;
            value[p.first.template as<std::string>()] = std::move(v);
        }
    }
};

template<typename KeyType, typename Type>
struct Serializer<OutputValue, MapTag<KeyType, Type>>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue &&data, ValueType &&value)
    {
        for (auto &[k, i] : value)
        {
            Serialization::OutputValue v{};
            v & i;
            data.m_Storage[k] = std::move(v.m_Storage);
        }
    }
};

template<>
struct Serializer<InputValue, std::filesystem::path>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue &&data, ValueType &&value)
    {
        if (data.m_Storage.IsScalar())
        {
            value = data.m_Storage.template as<std::string>();
        }
    }
};

template<>
struct Serializer<OutputValue, std::filesystem::path>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue &&data, ValueType &&value)
    {
        data.m_Storage = value.generic_string();
    }
};

template<typename Type> struct Serializer<InputValue, std::vector<Type>> : public Serializer<InputValue, ArrayTag<Type>> {};
template<typename Type> struct Serializer<OutputValue, std::vector<Type>> : public Serializer<OutputValue, ArrayTag<Type>> {};
template<typename Type> struct Serializer<InputValue, std::list<Type>> : public Serializer<InputValue, ArrayTag<Type>> {};
template<typename Type> struct Serializer<OutputValue, std::list<Type>> : public Serializer<OutputValue, ArrayTag<Type>> {};
template<typename KeyType, typename Type> struct Serializer<InputValue, std::map<KeyType, Type>> : public Serializer<InputValue, MapTag<KeyType, Type>> {};
template<typename KeyType, typename Type> struct Serializer<OutputValue, std::map<KeyType, Type>> : public Serializer<OutputValue, MapTag<KeyType, Type>> {};
template<typename KeyType, typename Type> struct Serializer<InputValue, std::unordered_map<KeyType, Type>> : public Serializer<InputValue, MapTag<KeyType, Type>> {};
template<typename KeyType, typename Type> struct Serializer<OutputValue, std::unordered_map<KeyType, Type>> : public Serializer<OutputValue, MapTag<KeyType, Type>> {};

}
