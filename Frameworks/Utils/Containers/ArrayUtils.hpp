#pragma once

#include "Containers/Array.hpp"

namespace ArrayUtils
{

inline constexpr size_t InvalidIndex = std::numeric_limits<size_t>::max();

template<typename ValueType>
inline size_t FindFirst(const Array<ValueType> &container, const ValueType &value)
{
    auto it = ranges::find(container, value);
    if (it == container.end())
    {
        return InvalidIndex;
    }
    return std::distance(container.begin(), it);
}

template<typename ValueType>
inline bool Contains(const Array<ValueType> &container, const ValueType &value)
{
    return ranges::find(container, value) != container.end();
}

template<typename ValueType, typename OtherValueType = ValueType>
inline bool Contains(const Array<ValueType> &container, const Array<OtherValueType> &values)
{
    for (const auto &v : values)
    {
        if (!Contains(container, v))
        {
            return false;
        }
    }
    return true;
}

template<typename ValueType, typename OtherValueType = ValueType>
inline size_t ContainsAny(const Array<ValueType> &container, const Array<OtherValueType> &values)
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (Contains(container, values[i]))
        {
            return i;
        }
    }
    return InvalidIndex;
}

template<typename ValueType>
inline void Add(Array<ValueType> &container, const ValueType &value)
{
    container.push_back(value);
}

template<typename ValueType>
inline void Add(Array<ValueType> &container, ValueType &&value)
{
    container.push_back(std::move(value));
}

template<typename ValueType, typename OtherValueType = ValueType>
inline void Add(Array<ValueType> &container, const Array<OtherValueType> &values)
{
    container.reserve(values.size());
    for (const auto &v : values)
    {
        container.push_back(v);
    }
}

template<typename ValueType, typename OtherValueType = ValueType>
inline void Add(Array<ValueType> &container, Array<OtherValueType> &&values)
{
    container.reserve(values.size());
    for (auto &v : values)
    {
        container.push_back(std::move(v));
    }
}

template<typename ValueType>
inline void AddUnique(Array<ValueType> &container, const ValueType &value)
{
    if (!Contains(container, value))
    {
        container.push_back(value);
    }
}

template<typename ValueType>
inline void AddUnique(Array<ValueType> &container, ValueType &&value)
{
    if (!Contains(container, value))
    {
        container.push_back(std::move(value));
    }
}


template<typename ValueType, typename OtherValueType = ValueType>
inline void AddUnique(Array<ValueType> &container, const Array<OtherValueType> &&values)
{
    container.reserve(values.size());
    for (auto &v : values)
    {
        AddUnique(container, v);
    }
}


template<typename ValueType, typename OtherValueType = ValueType>
inline void AddUnique(Array<ValueType> &container, Array<OtherValueType> &&values)
{
    container.reserve(values.size());
    for (auto &v : values)
    {
        AddUnique(container, std::move(v));
    }
}

template<typename ValueType, typename OtherValueType = ValueType>
inline auto Insert(Array<ValueType> &container, typename Array<ValueType>::const_iterator iterator, OtherValueType &&value)
{
    if (iterator >= container.end())
    {
        container.push_back(std::forward<OtherValueType>(value));
        return container.end() - 1;
    }

    return container.insert(iterator, std::forward<OtherValueType>(value));
}

template<typename ValueType, typename OtherValueType = ValueType>
inline auto Insert(Array<ValueType> &container, size_t index, OtherValueType &&value)
{
    return Insert(container, container.begin() + index, std::forward<OtherValueType>(value));
}

template<typename ValueType>
inline void Remove(Array<ValueType> &container, size_t index)
{
    size_t lastIndex = container.size() - 1;
    if (index != lastIndex)
    {
        container[index] = std::move(container[lastIndex]);
    }
    container.resize(container.size() - 1);
}

template<typename ValueType>
inline void Remove(Array<ValueType> &container, const ValueType &value)
{
    auto it = ranges::find(container, value);
    if (it != container.end())
    {
        Remove(container, std::distance(container.begin(), it));
    }
}

template<typename ValueType, typename OtherValueType = ValueType>
inline void Remove(Array<ValueType> &container, const Array<OtherValueType> &values)
{
    for (auto &v : values)
    {
        Remove(container, v);
    }
}

template<typename ValueType>
inline ValueType Pop(Array<ValueType> &container, size_t index)
{
    ValueType element = std::move(container[index]);
    Remove(container, index);
    return std::move(element);
}

}
