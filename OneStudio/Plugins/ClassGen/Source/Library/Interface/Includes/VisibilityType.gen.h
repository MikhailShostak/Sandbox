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
class VisibilityType
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Public,
        Protected,
        Private,
    };
    Enum value = Public;
    VisibilityType();
    inline VisibilityType(Enum value):value(value) {}
    inline VisibilityType(const VisibilityType &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Public",
        "Protected",
        "Private",
    };
    inline VisibilityType(const String &name)
    {
        if (name == "Public") { value = Public; return; }
        if (name == "Protected") { value = Protected; return; }
        if (name == "Private") { value = Private; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case VisibilityType::Public:
        {
            return Names[0];
        }
        case VisibilityType::Protected:
        {
            return Names[1];
        }
        case VisibilityType::Private:
        {
            return Names[2];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const LegacyClassGen::VisibilityType &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::VisibilityType &output) { output = LegacyClassGen::VisibilityType(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
