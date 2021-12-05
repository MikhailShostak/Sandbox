#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <AData>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class SizePolicy
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Fixed,
        Expanded,
        ContentWrapped,
    };
    Enum value = Fixed;
    SizePolicy();
    inline SizePolicy(Enum value):value(value) {}
    inline SizePolicy(const SizePolicy &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Fixed",
        "Expanded",
        "ContentWrapped",
    };
    inline SizePolicy(const String &name)
    {
        if (name == "Fixed") { value = Fixed; return; }
        if (name == "Expanded") { value = Expanded; return; }
        if (name == "ContentWrapped") { value = ContentWrapped; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case SizePolicy::Fixed:
        {
            return Names[0];
        }
        case SizePolicy::Expanded:
        {
            return Names[1];
        }
        case SizePolicy::ContentWrapped:
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
inline AJSONValue toJSONValue(const UI::SizePolicy &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::SizePolicy &output) { output = UI::SizePolicy(value.toString()); }
namespace UI {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
