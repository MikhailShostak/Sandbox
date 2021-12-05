#pragma once

#include "AAssert.h"

enum class AColorName : uint32_t {
    AliceBlue            = 0xFFF0F8FF,
    AntiqueWhite         = 0xFFFAEBD7,
    Aqua                 = 0xFF00FFFF,
    Aquamarine           = 0xFF7FFFD4,
    Azure                = 0xFFF0FFFF,
    Beige                = 0xFFF5F5DC,
    Bisque               = 0xFFFFE4C4,
    Black                = 0xFF000000,
    BlanchedAlmond       = 0xFFFFEBCD,
    Blue                 = 0xFF0000FF,
    BlueViolet           = 0xFF8A2BE2,
    Brown                = 0xFFA52A2A,
    BurlyWood            = 0xFFDEB887,
    CadetBlue            = 0xFF5F9EA0,
    Chartreuse           = 0xFF7FFF00,
    Chocolate            = 0xFFD2691E,
    Coral                = 0xFFFF7F50,
    CornflowerBlue       = 0xFF6495ED,
    Cornsilk             = 0xFFFFF8DC,
    Crimson              = 0xFFDC143C,
    Cyan                 = 0xFF00FFFF,
    DarkBlue             = 0xFF00008B,
    DarkCyan             = 0xFF008B8B,
    DarkGoldenRod        = 0xFFB8860B,
    DarkGray             = 0xFFA9A9A9,
    DarkGreen            = 0xFF006400,
    DarkKhaki            = 0xFFBDB76B,
    DarkMagenta          = 0xFF8B008B,
    DarkOliveGreen       = 0xFF556B2F,
    DarkOrange           = 0xFFFF8C00,
    DarkOrchid           = 0xFF9932CC,
    DarkRed              = 0xFF8B0000,
    DarkSalmon           = 0xFFE9967A,
    DarkSeaGreen         = 0xFF8FBC8F,
    DarkSlateBlue        = 0xFF483D8B,
    DarkSlateGray        = 0xFF2F4F4F,
    DarkTurquoise        = 0xFF00CED1,
    DarkViolet           = 0xFF9400D3,
    DeepPink             = 0xFFFF1493,
    DeepSkyBlue          = 0xFF00BFFF,
    DimGray              = 0xFF696969,
    DodgerBlue           = 0xFF1E90FF,
    FireBrick            = 0xFFB22222,
    FloralWhite          = 0xFFFFFAF0,
    ForestGreen          = 0xFF228B22,
    Fuchsia              = 0xFFFF00FF,
    Gainsboro            = 0xFFDCDCDC,
    GhostWhite           = 0xFFF8F8FF,
    Gold                 = 0xFFFFD700,
    GoldenRod            = 0xFFDAA520,
    Gray                 = 0xFF808080,
    Green                = 0xFF00FF00,
    GreenYellow          = 0xFFADFF2F,
    HoneyDew             = 0xFFF0FFF0,
    HotPink              = 0xFFFF69B4,
    IndianRed            = 0xFFCD5C5C,
    Indigo               = 0xFF4B0082,
    Ivory                = 0xFFFFFFF0,
    Khaki                = 0xFFF0E68C,
    Lavender             = 0xFFE6E6FA,
    LavenderBlush        = 0xFFFFF0F5,
    LawnGreen            = 0xFF7CFC00,
    LemonChiffon         = 0xFFFFFACD,
    LightBlue            = 0xFFADD8E6,
    LightCoral           = 0xFFF08080,
    LightCyan            = 0xFFE0FFFF,
    LightGoldenRodYellow = 0xFFFAFAD2,
    LightGray            = 0xFFD3D3D3,
    LightGreen           = 0xFF90EE90,
    LightPink            = 0xFFFFB6C1,
    LightSalmon          = 0xFFFFA07A,
    LightSeaGreen        = 0xFF20B2AA,
    LightSkyBlue         = 0xFF87CEFA,
    LightSlateGray       = 0xFF778899,
    LightSteelBlue       = 0xFFB0C4DE,
    LightYellow          = 0xFFFFFFE0,
    Lime                 = 0xFF00FF00,
    LimeGreen            = 0xFF32CD32,
    Linen                = 0xFFFAF0E6,
    Magenta              = 0xFFFF00FF,
    Maroon               = 0xFF800000,
    MediumAquaMarine     = 0xFF66CDAA,
    MediumBlue           = 0xFF0000CD,
    MediumOrchid         = 0xFFBA55D3,
    MediumPurple         = 0xFF9370DB,
    MediumSeaGreen       = 0xFF3CB371,
    MediumSlateBlue      = 0xFF7B68EE,
    MediumSpringGreen    = 0xFF00FA9A,
    MediumTurquoise      = 0xFF48D1CC,
    MediumVioletRed      = 0xFFC71585,
    MidnightBlue         = 0xFF191970,
    MintCream            = 0xFFF5FFFA,
    MistyRose            = 0xFFFFE4E1,
    Moccasin             = 0xFFFFE4B5,
    NavajoWhite          = 0xFFFFDEAD,
    Navy                 = 0xFF000080,
    OldLace              = 0xFFFDF5E6,
    Olive                = 0xFF808000,
    OliveDrab            = 0xFF6B8E23,
    Orange               = 0xFFFFA500,
    OrangeRed            = 0xFFFF4500,
    Orchid               = 0xFFDA70D6,
    PaleGoldenRod        = 0xFFEEE8AA,
    PaleGreen            = 0xFF98FB98,
    PaleTurquoise        = 0xFFAFEEEE,
    PaleVioletRed        = 0xFFDB7093,
    PapayaWhip           = 0xFFFFEFD5,
    PeachPuff            = 0xFFFFDAB9,
    Peru                 = 0xFFCD853F,
    Pink                 = 0xFFFFC0CB,
    Plum                 = 0xFFDDA0DD,
    PowderBlue           = 0xFFB0E0E6,
    Purple               = 0xFF800080,
    Red                  = 0xFFFF0000,
    RosyBrown            = 0xFFBC8F8F,
    RoyalBlue            = 0xFF4169E1,
    SaddleBrown          = 0xFF8B4513,
    Salmon               = 0xFFFA8072,
    SandyBrown           = 0xFFF4A460,
    SeaGreen             = 0xFF2E8B57,
    SeaShell             = 0xFFFFF5EE,
    Sienna               = 0xFFA0522D,
    Silver               = 0xFFC0C0C0,
    SkyBlue              = 0xFF87CEEB,
    SlateBlue            = 0xFF6A5ACD,
    SlateGray            = 0xFF708090,
    Snow                 = 0xFFFFFAFA,
    SpringGreen          = 0xFF00FF7F,
    SteelBlue            = 0xFF4682B4,
    Tan                  = 0xFFD2B48C,
    Teal                 = 0xFF008080,
    Thistle              = 0xFFD8BFD8,
    Tomato               = 0xFFFF6347,
    Transparent          = 0x00FFFFFF,
    Turquoise            = 0xFF40E0D0,
    Violet               = 0xFFEE82EE,
    Wheat                = 0xFFF5DEB3,
    White                = 0xFFFFFFFF,
    WhiteSmoke           = 0xFFF5F5F5,
    Yellow               = 0xFFFFFF00,
    YellowGreen          = 0xFF9ACD32
};

class AColor final
{

    friend AColor operator +(const AColor &lcolor, const AColor &rcolor);
    friend AColor operator -(const AColor &lcolor, const AColor &rcolor);
    friend AColor operator *(const AColor &lcolor, const AColor &rcolor);
    friend AColor operator /(const AColor &lcolor, const AColor &rcolor);
    friend AColor operator *(const AColor &color, float factor);
    friend AColor operator *(float factor, const AColor &color);
    friend AColor operator /(const AColor &color, float divisor);

    enum Mask
    {
        BlueMask  = 0x000000FF,
        GreenMask = 0x0000FF00,
        RedMask   = 0x00FF0000,
        AlphaMask = 0xFF000000
    };

public:

    float Red = 1.0f;
    float Green = 1.0f;
    float Blue = 1.0f;
    float Alpha = 1.0f;

    static const AColor &BlackColor()
    {
        static AColor color(0.0f, 0.0f, 0.0f, 1.0f);
        return color;
    }

    static const AColor &GrayColor()
    {
        static AColor color(0.5f, 0.5f, 0.5f, 1.0f);
        return color;
    }

    static const AColor &WhiteColor()
    {
        static AColor color(1.0f, 1.0f, 1.0f, 1.0f);
        return color;
    }

    static const AColor &RedColor()
    {
        static AColor color(1.0f, 0.0f, 0.0f, 1.0f);
        return color;
    }

    static const AColor &GreenColor()
    {
        static AColor color(0.0f, 1.0f, 0.0f, 1.0f);
        return color;
    }

    static const AColor &BlueColor()
    {
        static AColor color(0.0f, 0.0f, 1.0f, 1.0f);
        return color;
    }

    static const AColor &YellowColor()
    {
        static AColor color(1.0f, 1.0f, 0.0f, 1.0f);
        return color;
    }

    static const AColor &CyanColor()
    {
        static AColor color(0.0f, 1.0f, 1.0f, 1.0f);
        return color;
    }

    static const AColor &MagentaColor()
    {
        static AColor color(1.0f, 0.0f, 1.0f, 1.0f);
        return color;
    }

    static float blueFromHex(uint32_t hex) { return (hex & BlueMask) / 255.0f; }
    static float greenFromHex(uint32_t hex) { return ((hex & GreenMask) >> 8) / 255.0f; }
    static float redFromHex(uint32_t hex) { return ((hex & RedMask) >> 16) / 255.0f; }
    static float alphaFromHex(uint32_t hex) { return ((hex & AlphaMask) >> 24) / 255.0f; }

    static AColor fromHex(uint32_t hex)
    { return AColor(redFromHex(hex), greenFromHex(hex), blueFromHex(hex), alphaFromHex(hex)); }

    static AColor fromBytes(uint8_t gray, uint8_t alpha = 255)
    { return AColor(gray / 255.0f, alpha / 255.0f); }

    static AColor fromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
    { return AColor(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f); }

    AColor() {}
    AColor(float gray, float alpha = 1.0f) { Red = Green = Blue = gray; Alpha = alpha; }
    AColor(float red, float green, float blue, float alpha = 1.0f) { Red = red; Green = green; Blue = blue; Alpha = alpha; }
    AColor(AColorName name) { Red = redFromHex((uint32_t)name); Green = greenFromHex((uint32_t)name); Blue = blueFromHex((uint32_t)name); Alpha = alphaFromHex((uint32_t)name); }

    float red() const { return Red; }
    void setRed(float red) { Red = red; }
    float green() const { return Green; }
    void setGreen(float green) { Green = green; }
    float blue() const { return Blue; }
    void setBlue(float blue) { Blue = blue; }
    float alpha() const { return Alpha; }
    void setAlpha(float alpha) { Alpha = alpha; }

    void setGray(uint8_t gray);
    void setGray(float gray);
    void setGray(uint8_t gray, uint8_t alpha);
    void setGray(float gray, float alpha);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void setColor(float red, float green, float blue);
    void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void setColor(float red, float green, float blue, float alpha);
    void setColor(uint32_t hex);

    float *data() { return &Red; }
    const float *data() const { return &Red; }

    float &operator [](size_t index)
    {
        AAssert(index < 4, "Index %du out of range, color size is %d", (unsigned int)index, 4);
        return *((&Red) + index);
    }

    const float &operator [](size_t index) const
    {
        AAssert(index < 4, "Index %du out of range, color size is %d", (unsigned int)index, 4);
        return *((&Red) + index);
    }

    void inverse();

    AColor operator -() const;
    AColor &operator +=(const AColor &color);
    AColor &operator -=(const AColor &color);
    AColor &operator *=(const AColor &color);
    AColor &operator /=(const AColor &color);
    AColor &operator *=(float factor);
    AColor &operator /=(float divisor);

};

inline void AColor::setGray(uint8_t gray)
{
    Blue = Green = gray / 255.0f;
}

inline void AColor::setGray(float gray)
{
    Blue = Green = Red = gray;
}

inline void AColor::setGray(uint8_t gray, uint8_t alpha)
{
    Blue = Green = Red = gray / 255.0f;
    Alpha = alpha / 255.0f;
}

inline void AColor::setGray(float gray, float alpha)
{
    Blue = Green = Red = gray;
    Alpha = alpha;
}

inline void AColor::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    Red = red / 255.0f;
    Green = green / 255.0f;
    Blue = blue / 255.0f;
}

inline void AColor::setColor(float red, float green, float blue)
{
    Red = red;
    Green = green;
    Blue = blue;
}

inline void AColor::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    Red = red / 255.0f;
    Green = green / 255.0f;
    Blue = blue / 255.0f;
    Alpha = alpha / 255.0f;
}

inline void AColor::setColor(float red, float green, float blue, float alpha)
{
    Red = red;
    Green = green;
    Blue = blue;
    Alpha = alpha;
}

inline void AColor::inverse()
{
    Red = 1.0f - Red;
    Green = 1.0f - Green;
    Blue = 1.0f - Blue;
    Alpha = 1.0f - Alpha;
}

inline AColor AColor::operator -() const
{
    return AColor(-Red, -Green, -Blue, -Alpha);
}

inline AColor &AColor::operator +=(const AColor &color)
{
    Red += color.Red;
    Green += color.Green;
    Blue += color.Blue;
    Alpha += color.Alpha;
    return *this;
}

inline AColor &AColor::operator -=(const AColor &color)
{
    Red -= color.Red;
    Green -= color.Green;
    Blue -= color.Blue;
    Alpha -= color.Alpha;
    return *this;
}

inline AColor &AColor::operator *=(const AColor &color)
{
    Red *= color.Red;
    Green *= color.Green;
    Blue *= color.Blue;
    Alpha *= color.Alpha;
    return *this;
}

inline AColor &AColor::operator /=(const AColor &color)
{
    Red /= color.Red;
    Green /= color.Green;
    Blue /= color.Blue;
    Alpha /= color.Alpha;
    return *this;
}

inline AColor &AColor::operator *=(float factor)
{
    Red *= factor;
    Green *= factor;
    Blue *= factor;
    Alpha *= factor;
    return *this;
}

inline AColor &AColor::operator /=(float divisor)
{
    Red /= divisor;
    Green /= divisor;
    Blue /= divisor;
    Alpha /= divisor;
    return *this;
}


inline AColor operator +(const AColor &lcolor, const AColor &rcolor)
{
    return AColor(
        lcolor.Red + rcolor.Red,
        lcolor.Green + rcolor.Green,
        lcolor.Blue + rcolor.Blue,
        lcolor.Alpha + rcolor.Alpha
    );
}

inline AColor operator -(const AColor &lcolor, const AColor &rcolor)
{
    return AColor(
        lcolor.Red - rcolor.Red,
        lcolor.Green - rcolor.Green,
        lcolor.Blue - rcolor.Blue,
        lcolor.Alpha - rcolor.Alpha
    );
}

inline AColor operator *(const AColor &lcolor, const AColor &rcolor)
{
    return AColor(
        lcolor.Red * rcolor.Red,
        lcolor.Green * rcolor.Green,
        lcolor.Blue * rcolor.Blue,
        lcolor.Alpha * rcolor.Alpha
    );
}

inline AColor operator /(const AColor &lcolor, const AColor &rcolor)
{
    return AColor(
        lcolor.Red / rcolor.Red,
        lcolor.Green / rcolor.Green,
        lcolor.Blue / rcolor.Blue,
        lcolor.Alpha / rcolor.Alpha
    );
}

inline AColor operator *(const AColor &color, float factor)
{
    return AColor(
        color.Red * factor,
        color.Green * factor,
        color.Blue * factor,
        color.Alpha * factor
    );
}

inline AColor operator *(float factor, const AColor &color)
{
    return AColor(
        factor * color.Red,
        factor * color.Green,
        factor * color.Blue,
        factor * color.Alpha
    );
}

inline AColor operator /(const AColor &color, float divisor)
{
    return AColor(
        color.Red / divisor,
        color.Green / divisor,
        color.Blue / divisor,
        color.Alpha / divisor
    );
}

namespace UI
{

using Color = AColor;

}
