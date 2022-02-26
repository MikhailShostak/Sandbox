#pragma once

namespace Graphics
{
enum class TextureWrapping
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
}

namespace Serialization
{
template<>
struct Serializer<InputValue, Graphics::TextureWrapping>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (data.m_Storage.IsScalar())
        {
            const auto &valueName = data.m_Storage.template as<String>();
            if (valueName == "TiledWrapping") { value = Graphics::TextureWrapping::TiledWrapping; return; }
            if (valueName == "HorizontalTiledWrapping") { value = Graphics::TextureWrapping::HorizontalTiledWrapping; return; }
            if (valueName == "VerticalTiledWrapping") { value = Graphics::TextureWrapping::VerticalTiledWrapping; return; }
            if (valueName == "MirroredTiledWrapping") { value = Graphics::TextureWrapping::MirroredTiledWrapping; return; }
            if (valueName == "HorizontalMirroredTiledWrapping") { value = Graphics::TextureWrapping::HorizontalMirroredTiledWrapping; return; }
            if (valueName == "VerticalMirroredTiledWrapping") { value = Graphics::TextureWrapping::VerticalMirroredTiledWrapping; return; }
            if (valueName == "WrapToBorder") { value = Graphics::TextureWrapping::WrapToBorder; return; }
            if (valueName == "WrapToEdge") { value = Graphics::TextureWrapping::WrapToEdge; return; }
            value = Graphics::TextureWrapping::TiledWrapping;

        }
    }
};

template<>
struct Serializer<OutputValue, Graphics::TextureWrapping>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {

        switch(value)
        {
        case Graphics::TextureWrapping::TiledWrapping: data.m_Storage = "TiledWrapping"; return;
        case Graphics::TextureWrapping::HorizontalTiledWrapping: data.m_Storage = "HorizontalTiledWrapping"; return;
        case Graphics::TextureWrapping::VerticalTiledWrapping: data.m_Storage = "VerticalTiledWrapping"; return;
        case Graphics::TextureWrapping::MirroredTiledWrapping: data.m_Storage = "MirroredTiledWrapping"; return;
        case Graphics::TextureWrapping::HorizontalMirroredTiledWrapping: data.m_Storage = "HorizontalMirroredTiledWrapping"; return;
        case Graphics::TextureWrapping::VerticalMirroredTiledWrapping: data.m_Storage = "VerticalMirroredTiledWrapping"; return;
        case Graphics::TextureWrapping::WrapToBorder: data.m_Storage = "WrapToBorder"; return;
        case Graphics::TextureWrapping::WrapToEdge: data.m_Storage = "WrapToEdge"; return;
        }

    }
};

}
