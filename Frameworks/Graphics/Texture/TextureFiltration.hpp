#pragma once

namespace Graphics
{

class TextureFiltration
{
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
};

}
