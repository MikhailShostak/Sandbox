#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class Alignment
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Start,
        Center,
        End,
    };
    Enum value = Start;
    Alignment();
    inline Alignment(Enum value):value(value) {}
    inline Alignment(const Alignment &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Start",
        "Center",
        "End",
    };
    inline Alignment(const String &name)
    {
        if (name == "Start") { value = Start; return; }
        if (name == "Center") { value = Center; return; }
        if (name == "End") { value = End; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case Alignment::Start:
        {
            return Names[0];
        }
        case Alignment::Center:
        {
            return Names[1];
        }
        case Alignment::End:
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
inline AJSONValue toJSONValue(const Core::Alignment &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Core::Alignment &output) { output = Core::Alignment(value.toString()); }
namespace Core {
//CLASSGEN END REGION

template<typename Type>
Type align(Type contentSize, Type containerSize, Core::Alignment alignment)
{
    switch (alignment)
    {
    case Alignment::Start:
        return Type{};
    case Alignment::Center:
        return (containerSize - contentSize) / 2;
    case Alignment::End:
        return containerSize - contentSize;
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
