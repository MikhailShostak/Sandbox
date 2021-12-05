#pragma once

#include <Foundation>

#include "AJSONParser.h"
#include "AJSONValue.h"
#include "AJSONSerializedObject.h"

namespace AJSON
{

    template<typename PathType>
    inline bool saveToFile(AJSONSerializedObject *object, PathType &&path)
    {
        AAssert(object, "Bad access, object is null");

        AJSONObject jsonObject;

        if(!object->serialize(jsonObject))
        {
            return false;
        }

        AFile file;
        if(file.open(std::forward<PathType>(path), AFileOpenMode::Write))
        {
            file << jsonObject.toString(AJSONWriteOption::Formated);
            file.close();
            return true;
        }
        return false;
    }

    template<typename PathType>
    inline bool saveToFile(const AJSONValue &value, PathType &&path)
    {
        AFile file;
        if(file.open(std::forward<PathType>(path), AFileOpenMode::Write))
        {
            file << value.toString(AJSONWriteOption::Formated);
            file.close();
            return true;
        }
        return false;
    }

    template<typename PathType>
    inline bool saveToFile(const AJSONObject &object, PathType &&path)
    {
        AFile file;
        if(file.open(std::forward<PathType>(path), AFileOpenMode::Write))
        {
            file << object.toString(AJSONWriteOption::Formated);
            file.close();
            return true;
        }
        return false;
    }

    template<typename PathType>
    inline bool saveToFile(const AJSONArray &array, PathType &&path)
    {
        AFile file;
        if(file.open(std::forward<PathType>(path), AFileOpenMode::Write))
        {
            file << array.toString(AJSONWriteOption::Formated);
            file.close();
            return true;
        }
        return false;
    }

    template<typename PathType>
    inline AJSONValue valueFromFile(PathType &&path, const ADelegate<void(const AJSONError &error)> &completion = ADelegate<void(const AJSONError &error)>())
    {
        AJSONValue value;
        AJSONFileParser parser(std::forward<PathType>(path));
        value = parser.parse();
        if(completion.isValid())
            completion(AJSONError(parser.error(), parser.errorLine(), parser.errorOffset()));
        return value;
    }

    inline AJSONValue valueFromString(const String &string, const ADelegate<void(const AJSONError &error)> &completion = ADelegate<void(const AJSONError &error)>())
    {
        AJSONValue value;
        AJSONStringParser parser(string);
        value = parser.parse();
        if(completion.isValid())
            completion(AJSONError(parser.error(), parser.errorLine(), parser.errorOffset()));
        return value;
    }

    template<typename Type>
    inline bool deserialize(const AJSONObject &object, const AFactoryMap<String, Type> &factory, const String &key, const ADelegate<void(const SharedReference<Type> &object)> &delegate)
    {
        static_assert(std::is_base_of<AJSONSerializedObject, Type>::value, "Type is not a json serialized object");

        AAssert(!object.isEmpty(), "Object is empty");
        AAssert(!factory.isEmpty(), "Factory is empty");
        AAssert(bool(key), "Key is empty");
        AAssert(delegate, "Delegate is null");

        String type;
        object.read(key, type);

        if(!factory.hasKey(type))
            return false;

        SharedReference<Type> instance = factory.allocateShared(type);
        instance->deserialize(object);
        delegate(instance);
        return true;
    }

    inline bool serialize(AJSONSerializedObject *object, AJSONValue &data)
    {
        if(!object)
        {
            data = nullptr;
            return true;
        }
        if(data.isObject())
            return object->serialize(data.asObject());
        return false;
    }

    inline bool deserialize(const AJSONValue &data, AJSONSerializedObject *object)
    {
        if(!object)
            return data.isNull();
        if(data.isObject())
            return object->deserialize(data.asObject());
        return false;
    }

    inline bool serialize(bool value, AJSONValue &data)
    { data = value; return true; }

    inline bool deserialize(const AJSONValue &data, bool &value)
    { if(data.isBoolean()) { value = data.asBoolean(); return true; } return false; }

    inline bool serialize(char value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, char &value)
    { if(data.isString() && data.asString().size() == 1) { value = data.asString().front(); return true; } return false; }

    inline bool serialize(int8_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, int8_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(uint8_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, uint8_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(int16_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, int16_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(uint16_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, uint16_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(int32_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, int32_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(uint32_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, uint32_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(int64_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, int64_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(uint64_t value, AJSONValue &data)
    { data = (double)value; return true; }

    inline bool deserialize(const AJSONValue &data, uint64_t &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(float value, AJSONValue &data)
    { data = value; return true; }

    inline bool deserialize(const AJSONValue &data, float &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(double value, AJSONValue &data)
    { data = value; return true; }

    inline bool deserialize(const AJSONValue &data, double &value)
    { if(data.isNumber()) { value = data.asNumber(); return true; } return false; }

    inline bool serialize(const String &value, AJSONValue &data)
    { data = value; return true; }

    inline bool deserialize(const AJSONValue &data, String &value)
    { if(data.isString()) { value = data.asString(); return true; } return false; }

}
