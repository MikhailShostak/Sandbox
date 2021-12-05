#pragma once

#include "AJSONObject.h"
#include "AJSONArray.h"
#include "String.h"
#include "AAssert.h"
#include "AJSONSerializedObject.h"

inline AJSONValue::AJSONValue(const char *string): t(AJSONValueType::String) { d.string = Create<String>(string); }
inline AJSONValue::AJSONValue(const String &string): t(AJSONValueType::String) { d.string = Create<String>(string); }
inline AJSONValue::AJSONValue(String &&string): t(AJSONValueType::String) { d.string = Create<String>(string); }
inline AJSONValue::AJSONValue(const AJSONArray &array): t(AJSONValueType::Array) { d.array = Create<AJSONArray>(array); }
inline AJSONValue::AJSONValue(AJSONArray &&array): t(AJSONValueType::Array) { d.array = Create<AJSONArray>(array); }
inline AJSONValue::AJSONValue(const AJSONObject &object): t(AJSONValueType::Object) { d.object = Create<AJSONObject>(object); }
inline AJSONValue::AJSONValue(AJSONObject &&object): t(AJSONValueType::Object) { d.object = Create<AJSONObject>(object); }


inline AJSONValue::AJSONValue(const AJSONSerializedObject *object)
{
    d.object = Create<AJSONObject>();
    if(object->serialize(*d.object))
    {
        t = AJSONValueType::Object;
    }
    else
    {
        delete d.object;
        d.object = nullptr;
    }
}

inline AJSONValue::AJSONValue(const AJSONValue &value): t(value.t) { copy(value); }
inline AJSONValue::AJSONValue(AJSONValue &&value): t(value.t), d(value.d) { value.t = AJSONValueType::Null; }

inline bool AJSONValue::isEmpty() const { return isNull() || (isString() && d.string->empty()) || (isArray() && d.array->empty()) || (isObject() && d.object->isEmpty()); }

inline String AJSONValue::toString() const { return isString() ? *d.string : String(); }
inline AJSONArray AJSONValue::toArray() const { return isArray() ? *d.array : AJSONArray(); }
inline AJSONObject AJSONValue::toObject() const { return isObject() ? *d.object : AJSONObject(); }

inline AJSONValue &AJSONValue::operator =(std::nullptr_t)
{
    clear();
    return *this;
}

inline AJSONValue &AJSONValue::operator =(bool value)
{
    free();
    t = AJSONValueType::Boolean;
    d.boolean = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(int8_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(uint8_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(int16_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(uint16_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(int32_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(uint32_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(int64_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(uint64_t value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(float value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(double value)
{
    free();
    t = AJSONValueType::Number;
    d.number = value;
    return *this;
}

inline AJSONValue &AJSONValue::operator =(const String &string)
{
    free();
    t = AJSONValueType::String;
    d.string = Create<String>(string);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(String &&string)
{
    free();
    t = AJSONValueType::String;
    d.string = Create<String>(string);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(const AJSONArray &array)
{
    free();
    t = AJSONValueType::Array;
    d.array = Create<AJSONArray>(array);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(AJSONArray &&array)
{
    free();
    t = AJSONValueType::Array;
    d.array = Create<AJSONArray>(array);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(const AJSONObject &object)
{
    free();
    t = AJSONValueType::Object;
    d.object = Create<AJSONObject>(object);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(AJSONObject &&object)
{
    free();
    t = AJSONValueType::Object;
    d.object = Create<AJSONObject>(object);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(const AJSONValue &value)
{
    free();
    t = value.t;
    copy(value);
    return *this;
}

inline AJSONValue &AJSONValue::operator =(AJSONValue &&value)
{
    free();
    t = value.t;
    d = value.d;
    value.t = AJSONValueType::Null;
    return *this;
}

inline void AJSONValue::free() {
    switch(t)
    {
    case AJSONValueType::String: delete d.string; break;
    case AJSONValueType::Array: delete d.array; break;
    case AJSONValueType::Object: delete d.object;
    default: break;
    }
}

inline void AJSONValue::copy(const AJSONValue &value) {
    switch(value.t)
    {
    case AJSONValueType::Null: break;
    case AJSONValueType::Boolean: d.boolean = value.d.boolean ; break;
    case AJSONValueType::Number: d.number = value.d.number; break;
    case AJSONValueType::String: d.string = Create<String>(*value.d.string); break;
    case AJSONValueType::Array: d.array = Create<AJSONArray>(*value.d.array); break;
    case AJSONValueType::Object: d.object = Create<AJSONObject>(*value.d.object); break;
    }
}

inline String AJSONValue::toString(AJSONWriteOption option, const String &prefix) const
{
    auto jsonString = [](const String &string)
    {
        String result;
        for(auto symbol : string)
        {
            switch(symbol)
            {
            case '\"': result.append("\\\""); break;
            case '\\': result.append("\\\\"); break;
            case '\b': result.append("\\b"); break;
            case '\f': result.append("\\f"); break;
            case '\r': result.append("\\r"); break;
            case '\n': result.append("\\n"); break;
            case '\t': result.append("\\t"); break;
            default: result.push_back(symbol); break;
            }
        }
        return result;
    };

    switch(t)
    {
    case AJSONValueType::Boolean:
        return d.boolean ? "true" : "false";
    case AJSONValueType::Number:
        return std::to_string(d.number);
    case AJSONValueType::String:
        return "\"" + jsonString(*d.string) + "\"";
    case AJSONValueType::Array:
        return d.array->toString(option, prefix);
    case AJSONValueType::Object:
        return d.object->toString(option, prefix);
    default:
        return "null";
    }
}
