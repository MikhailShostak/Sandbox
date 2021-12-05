#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class ScrollBarVisibility
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Dynamic,
        Always,
        Never,
    };
    Enum value = Dynamic;
    ScrollBarVisibility();
    inline ScrollBarVisibility(Enum value):value(value) {}
    inline ScrollBarVisibility(const ScrollBarVisibility &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Dynamic",
        "Always",
        "Never",
    };
    inline ScrollBarVisibility(const String &name)
    {
        if (name == "Dynamic") { value = Dynamic; return; }
        if (name == "Always") { value = Always; return; }
        if (name == "Never") { value = Never; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case ScrollBarVisibility::Dynamic:
        {
            return Names[0];
        }
        case ScrollBarVisibility::Always:
        {
            return Names[1];
        }
        case ScrollBarVisibility::Never:
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
inline AJSONValue toJSONValue(const UI::ScrollBarVisibility &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::ScrollBarVisibility &output) { output = UI::ScrollBarVisibility(value.toString()); }
namespace UI {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
