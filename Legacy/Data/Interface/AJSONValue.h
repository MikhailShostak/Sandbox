#pragma once

#include <Foundation>

#include "AJSONError.h"

class AJSONArray;
class AJSONObject;
class AJSONValue;
class AJSONSerializedObject;

enum class AJSONValueType
{
    Null,
    Boolean,
    Number,
    String,
    Array,
    Object
};

class AJSONValue
{
    friend std::ostream& operator<<(std::ostream& stream, const AJSONValue &value);
public:
    AJSONValue() {}
    AJSONValue(std::nullptr_t) {}
    AJSONValue(bool boolean): t(AJSONValueType::Boolean) { d.boolean = boolean; }
    AJSONValue(int8_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(uint8_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(int16_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(uint16_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(int32_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(uint32_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(int64_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(uint64_t number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(float number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(double number): t(AJSONValueType::Number) { d.number = number; }
    AJSONValue(const char *string);
    AJSONValue(const String &string);
    AJSONValue(String &&string);
    AJSONValue(const AJSONArray &array);
    AJSONValue(AJSONArray &&array);
    AJSONValue(const AJSONObject &object);
    AJSONValue(AJSONObject &&object);
    AJSONValue(const AJSONSerializedObject *object);
    AJSONValue(const AJSONValue &value);
    AJSONValue(AJSONValue &&value);
    ~AJSONValue() { free(); }

    AJSONValueType type() const { return t; }
    bool isNull() const { return t == AJSONValueType::Null; }
    bool isEmpty() const;
    bool isValid() const { return t != AJSONValueType::Null; }
    bool isBoolean() const { return t == AJSONValueType::Boolean; }
    bool isNumber() const { return t == AJSONValueType::Number; }
    bool isString() const { return t == AJSONValueType::String; }
    bool isArray() const { return t == AJSONValueType::Array; }
    bool isObject() const { return t == AJSONValueType::Object; }

    bool toBoolean() const { return isBoolean() ? d.boolean : false; }
    double toNumber() const { return isNumber() ? d.number : 0.0; }
    String toString() const;
    AJSONArray toArray() const;
    AJSONObject toObject() const;

    bool &asBoolean() { AAssert(isBoolean(),"JSON value is not a boolean"); return d.boolean; }
    const bool &asBoolean() const { AAssert(isBoolean(),"JSON value is not a boolean"); return d.boolean; }
    double &asNumber() { AAssert(isNumber(),"JSON value is not a number"); return d.number; }
    const double &asNumber() const { AAssert(isNumber(),"JSON value is not a number"); return d.number; }
    String &asString() { AAssert(isString(),"JSON value is not a string"); return *d.string; }
    const String &asString() const { AAssert(isString(),"JSON value is not a string"); return *d.string; }
    AJSONArray &asArray() { AAssert(isArray(),"JSON value is not a array"); return *d.array; }
    const AJSONArray &asArray() const { AAssert(isArray(),"JSON value is not a array"); return *d.array; }
    AJSONObject &asObject() { AAssert(isObject(),"JSON value is not a object"); return *d.object; }
    const AJSONObject &asObject() const { AAssert(isObject(),"JSON value is not a object"); return *d.object; }

    void clear() { free(); t = AJSONValueType::Null; }

    AJSONValue &operator =(std::nullptr_t);
    AJSONValue &operator =(bool value);
    AJSONValue &operator =(int8_t value);
    AJSONValue &operator =(uint8_t value);
    AJSONValue &operator =(int16_t value);
    AJSONValue &operator =(uint16_t value);
    AJSONValue &operator =(int32_t value);
    AJSONValue &operator =(uint32_t value);
    AJSONValue &operator =(int64_t value);
    AJSONValue &operator =(uint64_t value);
    AJSONValue &operator =(float value);
    AJSONValue &operator =(double value);
    AJSONValue &operator =(const String &string);
    AJSONValue &operator =(String &&array);
    AJSONValue &operator =(const AJSONArray &array);
    AJSONValue &operator =(AJSONArray &&array);
    AJSONValue &operator =(const AJSONObject &object);
    AJSONValue &operator =(AJSONObject &&object);
    AJSONValue &operator =(const AJSONValue &value);
    AJSONValue &operator =(AJSONValue &&value);

    String toString(AJSONWriteOption option, const String &prefix = String()) const;

    explicit operator bool() const { return !isEmpty(); }

private:
    AJSONValueType t = AJSONValueType::Null;
    union Data
    {
        bool boolean;
        double number;
        String *string;
        AJSONArray *array;
        AJSONObject *object;
    } d;

    void free();

    void copy(const AJSONValue &value);
};

#include "AJSONObject.h"
