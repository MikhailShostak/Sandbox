#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: EnumerationHeader
class TextureFiltration
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Nearest,
        Bilinear,
        Trilinear,
        Anisotropic,
    };
    Enum value = Nearest;
    TextureFiltration();
    inline TextureFiltration(Enum value):value(value) {}
    inline TextureFiltration(const TextureFiltration &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Nearest",
        "Bilinear",
        "Trilinear",
        "Anisotropic",
    };
    inline TextureFiltration(const String &name)
    {
        if (name == "Nearest") { value = Nearest; return; }
        if (name == "Bilinear") { value = Bilinear; return; }
        if (name == "Trilinear") { value = Trilinear; return; }
        if (name == "Anisotropic") { value = Anisotropic; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TextureFiltration::Nearest:
        {
            return Names[0];
        }
        case TextureFiltration::Bilinear:
        {
            return Names[1];
        }
        case TextureFiltration::Trilinear:
        {
            return Names[2];
        }
        case TextureFiltration::Anisotropic:
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
inline AJSONValue toJSONValue(const Legacy::Graphics::TextureFiltration &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Legacy::Graphics::TextureFiltration &output) { output = Legacy::Graphics::TextureFiltration(value.toString()); }
namespace Graphics {
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
