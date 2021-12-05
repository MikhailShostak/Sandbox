#pragma once

#include <Foundation>

#include "Includes/TextAlign.gen.h"
#include "Includes/TextWrapping.gen.h"

#include "APixmap.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H

typedef int pt;

namespace Core
{

class Font;

class FontEngine final : public ASingleton<FontEngine>
{
    friend class Font;
    friend class FontData;
    friend class FontMetrics;
public:

    FontEngine();
    ~FontEngine();
    void load(const String &filename);
    void load(const Array<uint8_t> &array);
    void load(const uint8_t *data, size_t size);

    APixmap createAtlas(const Font &font) const;

    Math::IntegerVector getTextSize(const String &string, const Font &font, TextWrapping wrapping, int32_t maxWidth = std::numeric_limits<int32_t>::max()) const;

    int32_t getLineHeight(const Font &font) const;
    size_t findIndexAt(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth, const Math::IntegerVector &position);
    Math::IntegerVector findTextPosition(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth, size_t index);
    APixmap renderText(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth = std::numeric_limits<int32_t>::max()) const;
public:
    class FontData;
    class FontChache;
    class GlyphData;

    typedef FT_Library Library;
    typedef FT_Face Face;
    typedef FT_GlyphSlot Glyph;
    typedef FT_Glyph_Metrics GlyphMetrics;
    typedef Map<char16_t, GlyphData*> GlyphMap; //sort by char value
    typedef Map<pt, FontChache*> ChacheMap; //sort by size
    typedef Map<String, FontData*> DataMap; //sort by style
    typedef Map<String, DataMap> FontMap; //sort by family

    class GlyphData
    {
    public:
        uint32_t index = 0;
        GlyphMetrics metrics;
        APixmap pixmap;
    };

    class FontChache final
    {
    public:
        FontChache(FontData *data, pt size, uint32_t height, uint32_t ascent, uint32_t descent);
        ~FontChache();
        pt size() const;
        uint32_t height() const;
        uint32_t ascent() const;
        uint32_t descent() const;
        GlyphData *glyph(char16_t symbol) const;
        Math::IntegerVector kerning(const GlyphData *first, const GlyphData *second) const;
        bool isValid() const;
    private:
        FontData * _data = nullptr;
        pt _size = 0;
        uint32_t _height = 0;
        uint32_t _ascent = 0;
        uint32_t _descent = 0;
        mutable GlyphMap _glyphs;
    };

    class FontData final
    {
        friend class FontChache;
    public:
        FontData(const String &filename);
        FontData(const uint8_t *data, uint64_t size);
        ~FontData();
        String family() const;
        String style() const;
        FontChache *chache(pt size) const;
        bool isValid() const;
    private:
        FontData(const FontData &) = delete;
        Face _face;
        mutable ChacheMap _chache;
    };

    struct GlyphInfo
    {
        uint32_t width = 0;
        const FontEngine::GlyphData* glyph = nullptr;
    };

    struct LineInfo
    {
        size_t lenght = 0;
        int32_t offset = 0;
        int32_t width = 0;
        Array<GlyphInfo> glyphs;
    };

    Array<LineInfo> parseLines(const String &string, const FontEngine::FontChache *fontCache, TextWrapping wrapping, int32_t maxWidth) const;
    Math::IntegerVector getTextSizeFromLines(const Array<LineInfo> &lines, int32_t lineHeight) const;

    static Library _library;

    FontMap _fonts;
    void add(FontData *data);
};

inline FontEngine::FontChache::FontChache(FontData *data, pt size, uint32_t height, uint32_t ascent, uint32_t descent):
    _data(data),
    _size(size),
    _height(height),
    _ascent(ascent),
    _descent(descent)
{
}

inline FontEngine::FontChache::~FontChache()
{
    for (auto pair : _glyphs)
        delete pair.second;
}

inline pt FontEngine::FontChache::size() const
{
    return _size;
}

inline uint32_t FontEngine::FontChache::height() const
{
    return _height;
}

inline uint32_t FontEngine::FontChache::ascent() const
{
    return _ascent;
}

inline uint32_t FontEngine::FontChache::descent() const
{
    return _descent;
}

inline Math::IntegerVector FontEngine::FontChache::kerning(const GlyphData *first, const GlyphData *second) const
{
    FT_Vector offset;
    FT_Get_Kerning(_data->_face, first->index, second->index, FT_KERNING_DEFAULT, &offset);
    return Math::IntegerVector{ offset.x >> 6, offset.y >> 6 };
}

inline bool FontEngine::FontChache::isValid() const
{
    return _data && _data->isValid();
}

inline FontEngine::FontData::~FontData()
{
    if (_face)
        FT_Done_Face(_face);
    for (auto pair : _chache)
        delete pair.second;
}

inline String FontEngine::FontData::family() const
{
    if (_face)
        return _face->family_name;
    return String();
}

inline String FontEngine::FontData::style() const
{
    if (_face)
        return _face->style_name;
    return String();
}

inline bool FontEngine::FontData::isValid() const
{
    return _face;
}

}
