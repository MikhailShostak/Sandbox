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
class CGTypeGroup
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Undefined,
        SimpleValue,
        Object,
        Structure,
        Function,
        Event,
        Asset,
    };
    Enum value = Undefined;
    CGTypeGroup();
    inline CGTypeGroup(Enum value):value(value) {}
    inline CGTypeGroup(const CGTypeGroup &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Undefined",
        "SimpleValue",
        "Object",
        "Structure",
        "Function",
        "Event",
        "Asset",
    };
    inline CGTypeGroup(const String &name)
    {
        if (name == "Undefined") { value = Undefined; return; }
        if (name == "SimpleValue") { value = SimpleValue; return; }
        if (name == "Object") { value = Object; return; }
        if (name == "Structure") { value = Structure; return; }
        if (name == "Function") { value = Function; return; }
        if (name == "Event") { value = Event; return; }
        if (name == "Asset") { value = Asset; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case CGTypeGroup::Undefined:
        {
            return Names[0];
        }
        case CGTypeGroup::SimpleValue:
        {
            return Names[1];
        }
        case CGTypeGroup::Object:
        {
            return Names[2];
        }
        case CGTypeGroup::Structure:
        {
            return Names[3];
        }
        case CGTypeGroup::Function:
        {
            return Names[4];
        }
        case CGTypeGroup::Event:
        {
            return Names[5];
        }
        case CGTypeGroup::Asset:
        {
            return Names[6];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::CGTypeGroup &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::CGTypeGroup &output) { output = LegacyClassGen::CGTypeGroup(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
