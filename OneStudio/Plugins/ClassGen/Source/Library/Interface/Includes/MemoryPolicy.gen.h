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
class MemoryPolicy
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Embedded,
        Shared,
        Referenced,
    };
    Enum value = Embedded;
    MemoryPolicy();
    inline MemoryPolicy(Enum value):value(value) {}
    inline MemoryPolicy(const MemoryPolicy &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Embedded",
        "Shared",
        "Referenced",
    };
    inline MemoryPolicy(const String &name)
    {
        if (name == "Embedded") { value = Embedded; return; }
        if (name == "Shared") { value = Shared; return; }
        if (name == "Referenced") { value = Referenced; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case MemoryPolicy::Embedded:
        {
            return Names[0];
        }
        case MemoryPolicy::Shared:
        {
            return Names[1];
        }
        case MemoryPolicy::Referenced:
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
inline AJSONValue toJSONValue(const LegacyClassGen::MemoryPolicy &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::MemoryPolicy &output) { output = LegacyClassGen::MemoryPolicy(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
