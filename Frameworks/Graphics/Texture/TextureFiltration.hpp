#pragma once

namespace Graphics
{
enum class TextureFiltration
{
    Nearest,
    Bilinear,
    Trilinear,
    Anisotropic,
};
}

namespace Serialization
{
template<>
struct Serializer<InputValue, Graphics::TextureFiltration>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue&& data, ValueType&& value)
    {
        if (data.m_Storage.IsScalar())
        {
            const auto &valueName = data.m_Storage.template as<String>();
            if (valueName == "Nearest") { value = Graphics::TextureFiltration::Nearest; return; }
            if (valueName == "Bilinear") { value = Graphics::TextureFiltration::Bilinear; return; }
            if (valueName == "Trilinear") { value = Graphics::TextureFiltration::Trilinear; return; }
            if (valueName == "Anisotropic") { value = Graphics::TextureFiltration::Anisotropic; return; }
            value = Graphics::TextureFiltration::Nearest;

        }
    }
};

template<>
struct Serializer<OutputValue, Graphics::TextureFiltration>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue&& data, ValueType&& value)
    {

        switch(value)
        {
        case Graphics::TextureFiltration::Nearest: data.m_Storage = "Nearest"; return;
        case Graphics::TextureFiltration::Bilinear: data.m_Storage = "Bilinear"; return;
        case Graphics::TextureFiltration::Trilinear: data.m_Storage = "Trilinear"; return;
        case Graphics::TextureFiltration::Anisotropic: data.m_Storage = "Anisotropic"; return;
        }

    }
};

}
