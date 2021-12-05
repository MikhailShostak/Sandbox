#pragma once

#include <Foundation>

#include "AJSONError.h"

class AJSONValue;

class AJSONSerializedObject;

class AJSONArray : public Array<AJSONValue>
{
public:
    AJSONArray();

    AJSONArray(const Array<bool> &array);
    AJSONArray(const List<bool> &list);

    AJSONArray(const Array<int8_t> &array);
    AJSONArray(const List<int8_t> &list);
    AJSONArray(AInitializerList<int8_t> list);

    AJSONArray(const Array<uint8_t> &array);
    AJSONArray(const List<uint8_t> &list);
    AJSONArray(AInitializerList<uint8_t> list);

    AJSONArray(const Array<int16_t> &array);
    AJSONArray(const List<int16_t> &list);
    AJSONArray(AInitializerList<int16_t> list);

    AJSONArray(const Array<uint16_t> &array);
    AJSONArray(const List<uint16_t> &list);
    AJSONArray(AInitializerList<uint16_t> list);

    AJSONArray(const Array<int32_t> &array);
    AJSONArray(const List<int32_t> &list);
    AJSONArray(AInitializerList<int32_t> list);

    AJSONArray(const Array<uint32_t> &array);
    AJSONArray(const List<uint32_t> &list);
    AJSONArray(AInitializerList<uint32_t> list);

    AJSONArray(const Array<int64_t> &array);
    AJSONArray(const List<int64_t> &list);
    AJSONArray(AInitializerList<int64_t> list);

    AJSONArray(const Array<uint64_t> &array);
    AJSONArray(const List<uint64_t> &list);
    AJSONArray(AInitializerList<uint64_t> list);

    AJSONArray(const Array<float> &array);
    AJSONArray(const List<float> &list);
    AJSONArray(AInitializerList<float> list);

    AJSONArray(const Array<double> &array);
    AJSONArray(const List<double> &list);
    AJSONArray(AInitializerList<double> list);

    AJSONArray(const Array<String> &array);
    AJSONArray(const List<String> &list);
    AJSONArray(AInitializerList<String> list);

    AJSONArray(const Array<AJSONSerializedObject*> object);

    AJSONArray(const List<AJSONValue> &list);
    AJSONArray(AInitializerList<AJSONValue> list);

    String toString(AJSONWriteOption option, const String &prefix = String()) const;
};

#include "AJSONValue.h"

inline AJSONArray::AJSONArray():Array<AJSONValue>() {}

inline AJSONArray::AJSONArray(const Array<bool> &array):Array<AJSONValue>()
{ for(bool boolean : array) push_back(boolean); }

inline AJSONArray::AJSONArray(const List<bool> &list):Array<AJSONValue>()
{ for(bool boolean : list) push_back(boolean); }

inline AJSONArray::AJSONArray(const Array<int8_t> &array):Array<AJSONValue>()
{ for(int8_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<int8_t> &list):Array<AJSONValue>()
{ for(int8_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<int8_t> list):Array<AJSONValue>()
{ for(int8_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<uint8_t> &array):Array<AJSONValue>()
{ for(uint8_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<uint8_t> &list):Array<AJSONValue>()
{ for(uint8_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<uint8_t> list):Array<AJSONValue>()
{ for(uint8_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<int16_t> &array):Array<AJSONValue>()
{ for(int16_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<int16_t> &list):Array<AJSONValue>()
{ for(int16_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<int16_t> list):Array<AJSONValue>()
{ for(int16_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<uint16_t> &array):Array<AJSONValue>()
{ for(uint16_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<uint16_t> &list):Array<AJSONValue>()
{ for(uint16_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<uint16_t> list):Array<AJSONValue>()
{ for(uint16_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<int32_t> &array):Array<AJSONValue>()
{ for(int32_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<int32_t> &list):Array<AJSONValue>()
{ for(int32_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<int32_t> list):Array<AJSONValue>()
{ for(int32_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<uint32_t> &array):Array<AJSONValue>()
{ for(uint32_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<uint32_t> &list):Array<AJSONValue>()
{ for(uint32_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<uint32_t> list):Array<AJSONValue>()
{ for(uint32_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<int64_t> &array):Array<AJSONValue>()
{ for(int64_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<int64_t> &list):Array<AJSONValue>()
{ for(int64_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<int64_t> list):Array<AJSONValue>()
{ for(int64_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<uint64_t> &array):Array<AJSONValue>()
{ for(uint64_t number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<uint64_t> &list):Array<AJSONValue>()
{ for(uint64_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<uint64_t> list):Array<AJSONValue>()
{ for(uint64_t number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<float> &array):Array<AJSONValue>()
{ for(float number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<float> &list):Array<AJSONValue>()
{ for(float number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<float> list):Array<AJSONValue>()
{ for(float number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<double> &array):Array<AJSONValue>()
{ for(double number : array) push_back(number); }

inline AJSONArray::AJSONArray(const List<double> &list):Array<AJSONValue>()
{ for(double number : list) push_back(number); }

inline AJSONArray::AJSONArray(AInitializerList<double> list):Array<AJSONValue>()
{ for(double number : list) push_back(number); }

inline AJSONArray::AJSONArray(const Array<String> &array):Array<AJSONValue>()
{ for(const String &string : array) push_back(string); }

inline AJSONArray::AJSONArray(const List<String> &list):Array<AJSONValue>()
{ for(const String &string : list) push_back(string); }

inline AJSONArray::AJSONArray(AInitializerList<String> list):Array<AJSONValue>()
{ for(const String &string : list) push_back(string); }

//inline AJSONArray::AJSONArray(const Array<AJSONSerializedObject*> object);

inline AJSONArray::AJSONArray(const List<AJSONValue> &list):Array<AJSONValue>()
{ for(const AJSONValue &value : list) push_back(value); }

inline AJSONArray::AJSONArray(AInitializerList<AJSONValue> list):Array<AJSONValue>()
{ for(const AJSONValue &value : list) push_back(value); }


inline String AJSONArray::toString(AJSONWriteOption option, const String &prefix) const
{
    String string;

    AJSONArray::size_type i = 0;

    string.append("[");

    for(const AJSONValue &value : *this)
    {
        string.append(value.toString(option, prefix));
        if(i < (size() - 1))
            string.append(", ");
        ++i;
    }
    string.push_back(']');
    return string;
}
