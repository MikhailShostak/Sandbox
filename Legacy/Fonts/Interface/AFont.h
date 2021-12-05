#pragma once

#include <Foundation>

#include "AFontEngine.h"

#define DEFAULT_FONT_FAMILY "Arial"
#define DEFAULT_FONT_STYLE "Regular"

namespace Core
{

class Font final
{
    friend class FontEngine;
    friend class FontMetrics;
public:
    Font();
    Font(const Font &) = default;
    Font(Font &&) = default;
    Font(const String &family, const String &style, pt size = 12);
	Font(const String &family, const String &style, FontEngine *engine, pt size = 12);
	Font &operator =(const Font &) = default;
	Font &operator =(Font &&) = default;
    String family() const;
    void setFamily(const String &family);
    String style() const;
    void setStyle(const String &style);
    pt size() const;
    void setSize(pt size);
    bool isValid() const;
    void reload();
public:
    FontEngine::FontChache *_chache = nullptr;
    String _family;
    String _style;
    pt _size;
};

inline Font::Font() :
    _chache(nullptr),
    _family(DEFAULT_FONT_FAMILY),
    _style(DEFAULT_FONT_STYLE),
    _size(12)
{
    reload();
}

inline Font::Font(const String &family, const String &style, pt size) :
    _chache(nullptr),
    _family(family),
    _style(style),
    _size(size)
{
    reload();
}

inline String Font::family() const
{
    return _family;
}

inline void Font::setFamily(const String &family)
{
    _family = family;
    reload();
}

inline String Font::style() const
{
    return _style;
}

inline void Font::setStyle(const String &style)
{
    _style = style;
    reload();
}

inline pt Font::size() const
{
    return _size;
}

inline void Font::setSize(pt size)
{
    _size = size;
    reload();
}

inline bool Font::isValid() const
{
    return _chache && _chache->isValid();
}

/*bool Font::hasChar(char16_t symbol) const
{
if(_face)
return FT_Get_Char_Index(_face, symbol);
else
return false;
}*/

/*Pixmap Font::glyph(char16_t symbol) const
{
if(FT_Set_Char_Size(_face, 0, _size << 6, 72, 72))
{
debug("Font", "Couldn't set char size");
return Pixmap();
}
if(FT_Load_Char(_face, symbol, FT_LOAD_DEFAULT))//FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LCD))
{
debug("Font", "Couldn't load glyph");
return Pixmap();
}
//debug();
FT_Glyph_Metrics metrics = _face->glyph->metrics;
debug("Glyph", "Metrics size(%d, %d)", metrics.x >> 6, metrics.y >> 6);
//FT_Library_SetLcdFilter(FontEngine::_currentEngine->_library, FT_LCD_FILTER_LIGHT);
if(FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL))
{
debug("Font", "Couldn't render glyph");
return Pixmap();
}
const FT_Bitmap &bitmap = _face->glyph->bitmap;
Pixmap glyph;
glyph.setData(bitmap.buffer, Math::IntegerVector(bitmap.x, bitmap.rows), Pixmap::Luminance);
debug("Font", "Pixmap size(%d, %d) pitch %d, font pt%d", bitmap.x, bitmap.rows, bitmap.pitch, _size);
return glyph;
}*/

class FontMetrics
{
public:
    FontMetrics(const Font &font);
    uint32_t lineHeight() const;
    Math::IntegerVector offset(char16_t symbol) const;
    Math::IntegerVector size(char16_t symbol) const;
    uint32_t width(const String &string) const;
    uint32_t height(const String &string) const;
    Math::IntegerVector size(const String &string) const;
private:
    const Font &_font;
};

inline FontMetrics::FontMetrics(const Font &font) :
    _font(font)
{}

inline uint32_t FontMetrics::lineHeight() const
{
    return _font._chache->height();
}

inline Math::IntegerVector FontMetrics::offset(char16_t symbol) const
{
    if (_font.isValid())
    {
        FontEngine::GlyphData *glyph = _font._chache->glyph(symbol);
        return { glyph->metrics.horiBearingX, glyph->metrics.horiBearingY };
    }
    return {};
}

inline Math::IntegerVector FontMetrics::size(char16_t symbol) const
{
    if (_font.isValid())
    {
        FontEngine::GlyphData *glyph = _font._chache->glyph(symbol);
        return { glyph->metrics.width, glyph->metrics.height };
    }
    return {};
}

inline uint32_t FontMetrics::width(const String &string) const
{
    if (_font.isValid())
    {
        uint32_t width = 0;
        FontEngine::GlyphData *previous = nullptr;
        FontEngine::GlyphData *glyph = nullptr;
        for (char16_t symbol : string)
        {
            glyph = _font._chache->glyph(symbol);
            Math::IntegerVector kerning;
            if (previous)
                kerning = _font._chache->kerning(previous, glyph);
            width += glyph->metrics.horiAdvance + kerning.x;
            previous = glyph;
        }
        if (glyph)
            width += glyph->metrics.horiBearingX + glyph->metrics.width - glyph->metrics.horiAdvance;
        return width;
    }
    return 0;
}

inline uint32_t FontMetrics::height(const String &string) const
{
    if (_font.isValid())
    {
        uint32_t height = 0;
        for (char16_t symbol : string)
        {
            FontEngine::GlyphData *glyph = _font._chache->glyph(symbol);
            height += glyph->metrics.vertAdvance;
        }
        return height;
    }
    return 0;
}

inline Math::IntegerVector FontMetrics::size(const String &string) const
{
    if (_font._chache)
    {
        Math::IntegerVector size;
        FontEngine::GlyphData *glyph;
        for (char16_t symbol : string)
        {
            glyph = _font._chache->glyph(symbol);
            size += Math::IntegerVector{ glyph->metrics.horiAdvance, glyph->metrics.vertAdvance };
        }
        if (glyph)
            size += Math::IntegerVector{ glyph->metrics.horiBearingX + glyph->metrics.width - glyph->metrics.horiAdvance, glyph->metrics.vertBearingY + glyph->metrics.height - glyph->metrics.vertAdvance };
        return size;
    }
    return {};
}

}
