#pragma once

#include "AJSONSerializedObject.h"
#include "AJSONArray.h"

inline AJSONObject::AJSONObject(const AJSONSerializedObject *object)
{
    if(object) object->serialize(*this);
}

inline AJSONObject &AJSONObject::operator =(const AJSONSerializedObject *object)
{
    d.clear();
    if(object)
        object->serialize(*this);
    return *this;
}

inline void AJSONObject::insert(const String &key, const AJSONArray &array, bool removeEmpty)
{
    if(removeEmpty && array.empty())
    {
        d.erase(key);
        return;
    }

    d[key] = array;
}

inline void AJSONObject::insert(const String &key, const AJSONObject &object, bool removeEmpty)
{
    if(removeEmpty && !object)
    {
        d.erase(key);
        return;
    }

    d[key] = object;
}

inline void AJSONObject::insert(const String &key, const AJSONValue &value, bool removeEmpty)
{
    if(removeEmpty && !value)
    {
        d.erase(key);
        return;
    }

    d[key] = value;
}

inline void AJSONObject::insert(const String &key, AJSONArray &&array, bool removeEmpty)
{
    if(removeEmpty && array.empty())
    {
        d.erase(key);
        return;
    }

    d[key] = std::move(array);
}

inline void AJSONObject::insert(const String &key, AJSONObject &&object, bool removeEmpty)
{
    if(removeEmpty && !object)
    {
        d.erase(key);
        return;
    }

    d[key] = std::move(object);
}

inline void AJSONObject::insert(const String &key, AJSONValue &&value, bool removeEmpty)
{
    if(removeEmpty && !value)
    {
        d.erase(key);
        return;
    }

    d[key] = std::move(value);
}

inline void AJSONObject::insert(const String &key, const AJSONSerializedObject *object, bool removeEmpty)
{
    if(removeEmpty && !object)
    {
        d.erase(key);
        return;
    }

    AJSONObject value;
    if(object->serialize(value))
        d[key] = std::move(value);
}

inline void AJSONObject::remove(const String &key)
{
    d.erase(key);
}

inline bool AJSONObject::read(const String &key, bool &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isBoolean())
        return false;
    value = it->second.asBoolean();
    return true;
}

inline bool AJSONObject::read(const String &key, char &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isString() && it->second.asString().size() != 1)
        return false;
    value = it->second.asString().at(0);
    return true;
}

inline bool AJSONObject::read(const String &key, int8_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, uint8_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, int16_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, uint16_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, int32_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, uint32_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, int64_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, uint64_t &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, float &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, double &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isNumber())
        return false;
    value = it->second.asNumber();
    return true;
}

inline bool AJSONObject::read(const String &key, String &string) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isString())
        return false;
    string = it->second.asString();
    return true;
}

inline bool AJSONObject::read(const String &key, AJSONArray &array) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isArray())
        return false;
    array = it->second.asArray();
    return true;
}

inline bool AJSONObject::read(const String &key, Array<bool> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isBoolean())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asBoolean());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<bool> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isBoolean())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asBoolean());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<int8_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<int8_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<uint8_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<uint8_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<int16_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<int16_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<uint16_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<uint16_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<int32_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<int32_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<uint32_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<uint32_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<int64_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<int64_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<uint64_t> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<uint64_t> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<float> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<float> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<double> &array) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<double> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isNumber())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asNumber());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, Array<String> &array) const
{
    AJSONArray jsonArray;
    if (!read(key, jsonArray))
        return false;
    for (AJSONValue &value : jsonArray)
    {
        if (!value.isString())
        {
            array.clear();
            return false;
        }
        array.push_back(value.asString());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, List<String> &list) const
{
    AJSONArray jsonArray;
    if(!read(key, jsonArray))
        return false;
    for(AJSONValue &value : jsonArray)
    {
        if(!value.isString())
        {
            list.clear();
            return false;
        }
        list.push_back(value.asString());
    }
    return true;
}

inline bool AJSONObject::read(const String &key, AJSONObject &object) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isObject())
        return false;
    object = it->second.asObject();
    return true;
}

inline bool AJSONObject::read(const String &key, AJSONSerializedObject *object) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    if(!it->second.isObject())
        return false;
    return object->deserialize(it->second.asObject());
}

inline bool AJSONObject::read(const String &key, AJSONValue &value) const
{
    ConstIterator it = find(key);
    if(it == end())
        return false;
    value = it->second;
    return true;
}
