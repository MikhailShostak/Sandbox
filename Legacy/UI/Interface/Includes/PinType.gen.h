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
class PinType
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Input,
        Output,
    };
    Enum value = Input;
    PinType();
    inline PinType(Enum value):value(value) {}
    inline PinType(const PinType &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Input",
        "Output",
    };
    inline PinType(const String &name)
    {
        if (name == "Input") { value = Input; return; }
        if (name == "Output") { value = Output; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case PinType::Input:
        {
            return Names[0];
        }
        case PinType::Output:
        {
            return Names[1];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const UI::PinType &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::PinType &output) { output = UI::PinType(value.toString()); }
namespace UI {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
