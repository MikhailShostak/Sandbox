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
class TextWrapping
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Inline,
        WordWrap,
        Wrap,
    };
    Enum value = Inline;
    TextWrapping();
    inline TextWrapping(Enum value):value(value) {}
    inline TextWrapping(const TextWrapping &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Inline",
        "WordWrap",
        "Wrap",
    };
    inline TextWrapping(const String &name)
    {
        if (name == "Inline") { value = Inline; return; }
        if (name == "WordWrap") { value = WordWrap; return; }
        if (name == "Wrap") { value = Wrap; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TextWrapping::Inline:
        {
            return Names[0];
        }
        case TextWrapping::WordWrap:
        {
            return Names[1];
        }
        case TextWrapping::Wrap:
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
inline AJSONValue toJSONValue(const Core::TextWrapping &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Core::TextWrapping &output) { output = Core::TextWrapping(value.toString()); }
namespace Core {
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
