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
class ContentFit
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Fit,
        HalfPaddings,
        FullPaddings,
        Custom,
    };
    Enum value = Fit;
    ContentFit();
    inline ContentFit(Enum value):value(value) {}
    inline ContentFit(const ContentFit &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Fit",
        "HalfPaddings",
        "FullPaddings",
        "Custom",
    };
    inline ContentFit(const String &name)
    {
        if (name == "Fit") { value = Fit; return; }
        if (name == "HalfPaddings") { value = HalfPaddings; return; }
        if (name == "FullPaddings") { value = FullPaddings; return; }
        if (name == "Custom") { value = Custom; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case ContentFit::Fit:
        {
            return Names[0];
        }
        case ContentFit::HalfPaddings:
        {
            return Names[1];
        }
        case ContentFit::FullPaddings:
        {
            return Names[2];
        }
        case ContentFit::Custom:
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
inline AJSONValue toJSONValue(const UI::ContentFit &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, UI::ContentFit &output) { output = UI::ContentFit(value.toString()); }
namespace UI {
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
