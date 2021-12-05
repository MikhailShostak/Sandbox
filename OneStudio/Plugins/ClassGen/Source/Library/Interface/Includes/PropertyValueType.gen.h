#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class PropertyValueType
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Value,
        Array,
        Stack,
        Queue,
        OrederedSet,
        UnorderedSet,
        OrderedDictionary,
        UnorderedDictionary,
    };
    Enum value = Value;
    PropertyValueType();
    inline PropertyValueType(Enum value):value(value) {}
    inline PropertyValueType(const PropertyValueType &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Value",
        "Array",
        "Stack",
        "Queue",
        "OrederedSet",
        "UnorderedSet",
        "OrderedDictionary",
        "UnorderedDictionary",
    };
    inline PropertyValueType(const String &name)
    {
        if (name == "Value") { value = Value; return; }
        if (name == "Array") { value = Array; return; }
        if (name == "Stack") { value = Stack; return; }
        if (name == "Queue") { value = Queue; return; }
        if (name == "OrederedSet") { value = OrederedSet; return; }
        if (name == "UnorderedSet") { value = UnorderedSet; return; }
        if (name == "OrderedDictionary") { value = OrderedDictionary; return; }
        if (name == "UnorderedDictionary") { value = UnorderedDictionary; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case PropertyValueType::Value:
        {
            return Names[0];
        }
        case PropertyValueType::Array:
        {
            return Names[1];
        }
        case PropertyValueType::Stack:
        {
            return Names[2];
        }
        case PropertyValueType::Queue:
        {
            return Names[3];
        }
        case PropertyValueType::OrederedSet:
        {
            return Names[4];
        }
        case PropertyValueType::UnorderedSet:
        {
            return Names[5];
        }
        case PropertyValueType::OrderedDictionary:
        {
            return Names[6];
        }
        case PropertyValueType::UnorderedDictionary:
        {
            return Names[7];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::PropertyValueType &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::PropertyValueType &output) { output = LegacyClassGen::PropertyValueType(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
