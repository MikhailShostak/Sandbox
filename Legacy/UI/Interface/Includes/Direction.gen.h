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
class Direction
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Horizontal,
        Vertical,
        ReverseHorizontal,
        ReverseVertical,
    };
    Enum value = Horizontal;
    Direction();
    inline Direction(Enum value):value(value) {}
    inline Direction(const Direction &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Horizontal",
        "Vertical",
        "ReverseHorizontal",
        "ReverseVertical",
    };
    inline Direction(const String &name)
    {
        if (name == "Horizontal") { value = Horizontal; return; }
        if (name == "Vertical") { value = Vertical; return; }
        if (name == "ReverseHorizontal") { value = ReverseHorizontal; return; }
        if (name == "ReverseVertical") { value = ReverseVertical; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case Direction::Horizontal:
        {
            return Names[0];
        }
        case Direction::Vertical:
        {
            return Names[1];
        }
        case Direction::ReverseHorizontal:
        {
            return Names[2];
        }
        case Direction::ReverseVertical:
        {
            return Names[3];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const UI::Direction &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::Direction &output) { output = UI::Direction(value.toString()); }
namespace UI {
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
