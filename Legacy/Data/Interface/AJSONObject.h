#pragma once

#include <Foundation>

#include "AJSONValue.h"
#include "AJSONError.h"

class AJSONSerializedObject;
class AJSONArray;

using AJSONValueMap = Map<String, AJSONValue>;

class AJSONObject
{
    friend std::ostream& operator<<(std::ostream& stream, const AJSONObject &object);
public:
    using Iterator = AJSONValueMap::iterator;
    using ConstIterator = AJSONValueMap::const_iterator;

    using PairType = AJSONValueMap::value_type;
    using ValueType = AJSONValueMap::mapped_type;
    using SizeType = AJSONValueMap::size_type;

    AJSONObject() {}
    AJSONObject(const AInitializerList<PairType> &list): d(list) {}
    AJSONObject(const AJSONObject &object): d(object.d) {}
    AJSONObject(AJSONObject &&object): d(object.d) {}
    AJSONObject(const AJSONSerializedObject *object);

    AJSONObject &operator =(const AJSONObject &object) { d = object.d; return *this; }
    AJSONObject &operator =(AJSONObject &&object) { d = object.d; return *this; }
    AJSONObject &operator =(const AJSONSerializedObject *object);

    void insert(const String &key, const AJSONArray &array, bool removeEmpty = true);
    void insert(const String &key, const AJSONObject &object, bool removeEmpty = true);
    void insert(const String &key, const AJSONValue &value, bool removeEmpty = true);

    void insert(const String &key, AJSONArray &&array, bool removeEmpty = true);
    void insert(const String &key, AJSONObject &&object, bool removeEmpty = true);
    void insert(const String &key, AJSONValue &&value, bool removeEmpty = true);
    void insert(const String &key, const AJSONSerializedObject *object, bool removeEmpty = true);

    void remove(const String &key);

    bool hasKey(const String &key) const
    {
        ConstIterator iterator = d.find(key);
        return iterator != d.end();
    }

    AJSONValue &at(const String &key) { AAssert(hasKey(key), "JSON object has no key"); return d.at(key); }
    const AJSONValue &at(const String &key) const { AAssert(hasKey(key), "JSON object has no key"); return d.at(key); }

    Iterator find(const String &key) { return d.find(key); }
    ConstIterator find(const String &key) const { return d.find(key); }

    SizeType size() const { return d.size(); }
    bool isEmpty() const { return d.empty(); }

    Iterator begin() { return d.begin(); }
    ConstIterator begin() const { return d.begin(); }

    Iterator end() { return d.end(); }
    ConstIterator end() const { return d.end(); }

    bool read(const String &key, bool &value) const;
    bool read(const String &key, char &value) const;
    bool read(const String &key, int8_t &value) const;
    bool read(const String &key, uint8_t &value) const;
    bool read(const String &key, int16_t &value) const;
    bool read(const String &key, uint16_t &value) const;
    bool read(const String &key, int32_t &value) const;
    bool read(const String &key, uint32_t &value) const;
    bool read(const String &key, int64_t &value) const;
    bool read(const String &key, uint64_t &value) const;
    bool read(const String &key, float &value) const;
    bool read(const String &key, double &value) const;
    bool read(const String &key, String &string) const;

    bool read(const String &key, AJSONArray &array) const;
    bool read(const String &key, Array<bool> &array) const;
    bool read(const String &key, List<bool> &list) const;
    bool read(const String &key, Array<int8_t> &array) const;
    bool read(const String &key, List<int8_t> &list) const;
    bool read(const String &key, Array<uint8_t> &array) const;
    bool read(const String &key, List<uint8_t> &list) const;
    bool read(const String &key, Array<int16_t> &array) const;
    bool read(const String &key, List<int16_t> &list) const;
    bool read(const String &key, Array<uint16_t> &array) const;
    bool read(const String &key, List<uint16_t> &list) const;
    bool read(const String &key, Array<int32_t> &array) const;
    bool read(const String &key, List<int32_t> &list) const;
    bool read(const String &key, Array<uint32_t> &array) const;
    bool read(const String &key, List<uint32_t> &list) const;
    bool read(const String &key, Array<int64_t> &array) const;
    bool read(const String &key, List<int64_t> &list) const;
    bool read(const String &key, Array<uint64_t> &array) const;
    bool read(const String &key, List<uint64_t> &list) const;
    bool read(const String &key, Array<float> &array) const;
    bool read(const String &key, List<float> &list) const;
    bool read(const String &key, Array<double> &array) const;
    bool read(const String &key, List<double> &list) const;
    bool read(const String &key, Array<String> &array) const;
    bool read(const String &key, List<String> &list) const;

    bool read(const String &key, AJSONObject &object) const;
    bool read(const String &key, AJSONSerializedObject *object) const;

    bool read(const String &key, AJSONValue &value) const;

    void clear() { d.clear(); }

    explicit operator bool() const { return d.size() > 0; }

    String toString(AJSONWriteOption option, const String &prefix = String()) const;

private:
    AJSONValueMap d;
};

inline String AJSONObject::toString(AJSONWriteOption option, const String &prefix) const
{
    String string;

    AJSONObject::SizeType i = 0;

    string.append("{\n");

    for(const std::pair<String, AJSONValue> pair : d)
    {
        string.append(prefix + '\t' + "\"" + pair.first + "\"");
        string.append(" : ");
        string.append(pair.second.toString(option, prefix + '\t'));
        if(i < (d.size() - 1))
            string.append(",\n");
        ++i;
    }

    string.append("\n" + prefix + "}");
    return string;
}

#include "AJSONObject.inl"
#include "AJSONValue.inl"
