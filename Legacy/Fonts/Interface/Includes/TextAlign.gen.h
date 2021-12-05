#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <AData>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class TextAlign
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Start,
        Center,
        End,
        Justify,
        Left,
        Right,
    };
    Enum value = Start;
    TextAlign();
    inline TextAlign(Enum value):value(value) {}
    inline TextAlign(const TextAlign &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Start",
        "Center",
        "End",
        "Justify",
        "Left",
        "Right",
    };
    inline TextAlign(const String &name)
    {
        if (name == "Start") { value = Start; return; }
        if (name == "Center") { value = Center; return; }
        if (name == "End") { value = End; return; }
        if (name == "Justify") { value = Justify; return; }
        if (name == "Left") { value = Left; return; }
        if (name == "Right") { value = Right; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TextAlign::Start:
        {
            return Names[0];
        }
        case TextAlign::Center:
        {
            return Names[1];
        }
        case TextAlign::End:
        {
            return Names[2];
        }
        case TextAlign::Justify:
        {
            return Names[3];
        }
        case TextAlign::Left:
        {
            return Names[4];
        }
        case TextAlign::Right:
        {
            return Names[5];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const Core::TextAlign &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Core::TextAlign &output) { output = Core::TextAlign(value.toString()); }
namespace Core {
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
