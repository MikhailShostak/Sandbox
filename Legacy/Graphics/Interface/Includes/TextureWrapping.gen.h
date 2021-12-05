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
class TextureWrapping
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        TiledWrapping,
        HorizontalTiledWrapping,
        VerticalTiledWrapping,
        MirroredTiledWrapping,
        HorizontalMirroredTiledWrapping,
        VerticalMirroredTiledWrapping,
        WrapToBorder,
        WrapToEdge,
    };
    Enum value = TiledWrapping;
    TextureWrapping();
    inline TextureWrapping(Enum value):value(value) {}
    inline TextureWrapping(const TextureWrapping &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "TiledWrapping",
        "HorizontalTiledWrapping",
        "VerticalTiledWrapping",
        "MirroredTiledWrapping",
        "HorizontalMirroredTiledWrapping",
        "VerticalMirroredTiledWrapping",
        "WrapToBorder",
        "WrapToEdge",
    };
    inline TextureWrapping(const String &name)
    {
        if (name == "TiledWrapping") { value = TiledWrapping; return; }
        if (name == "HorizontalTiledWrapping") { value = HorizontalTiledWrapping; return; }
        if (name == "VerticalTiledWrapping") { value = VerticalTiledWrapping; return; }
        if (name == "MirroredTiledWrapping") { value = MirroredTiledWrapping; return; }
        if (name == "HorizontalMirroredTiledWrapping") { value = HorizontalMirroredTiledWrapping; return; }
        if (name == "VerticalMirroredTiledWrapping") { value = VerticalMirroredTiledWrapping; return; }
        if (name == "WrapToBorder") { value = WrapToBorder; return; }
        if (name == "WrapToEdge") { value = WrapToEdge; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TextureWrapping::TiledWrapping:
        {
            return Names[0];
        }
        case TextureWrapping::HorizontalTiledWrapping:
        {
            return Names[1];
        }
        case TextureWrapping::VerticalTiledWrapping:
        {
            return Names[2];
        }
        case TextureWrapping::MirroredTiledWrapping:
        {
            return Names[3];
        }
        case TextureWrapping::HorizontalMirroredTiledWrapping:
        {
            return Names[4];
        }
        case TextureWrapping::VerticalMirroredTiledWrapping:
        {
            return Names[5];
        }
        case TextureWrapping::WrapToBorder:
        {
            return Names[6];
        }
        case TextureWrapping::WrapToEdge:
        {
            return Names[7];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
}
inline AJSONValue toJSONValue(const Legacy::Graphics::TextureWrapping &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, Legacy::Graphics::TextureWrapping &output) { output = Legacy::Graphics::TextureWrapping(value.toString()); }
namespace Graphics {
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
