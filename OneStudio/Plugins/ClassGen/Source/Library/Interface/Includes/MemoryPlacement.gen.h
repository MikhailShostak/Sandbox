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
class MemoryPlacement
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
    MemoryPlacement();
    inline MemoryPlacement(Enum value):value(value) {}
    inline MemoryPlacement(const MemoryPlacement &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Embedded",
        "Shared",
        "Referenced",
    };
    inline MemoryPlacement(const String &name)
    {
        if (name == "Embedded") { value = Embedded; return; }
        if (name == "Shared") { value = Shared; return; }
        if (name == "Referenced") { value = Referenced; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case MemoryPlacement::Embedded:
        {
            return Names[0];
        }
        case MemoryPlacement::Shared:
        {
            return Names[1];
        }
        case MemoryPlacement::Referenced:
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
inline AJSONValue toJSONValue(const LegacyClassGen::MemoryPlacement &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, LegacyClassGen::MemoryPlacement &output) { output = LegacyClassGen::MemoryPlacement(value.toString()); }
namespace LegacyClassGen {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
