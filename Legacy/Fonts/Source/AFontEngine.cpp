#include "AFontEngine.h"
#include "AFont.h"

#include <Foundation>
//#include <unistd.h>

namespace Core
{

FontEngine::Library FontEngine::_library = nullptr;

FontEngine::FontEngine():
_fonts()
{
	if(!_library && FT_Init_FreeType(&_library))
	{
		ALogMessage("Font engine", "Couldn't initialize freetype library");
		return;
	}
#if APlatformApple
    Array<String> fonts;
	AFile file("/System/Library/Fonts/fonts.list", File::Read);
	while(!file.isEnd())
		fonts.push_back(String(file.readLine()));
	file.open("/Library/Fonts/fonts.list", File::Read);
	while(!file.isEnd())
		fonts.push_back(String(file.readLine()));
	file.open("~/Library/Fonts/fonts.list", File::Read);
	while(!file.isEnd())
		fonts.push_back(String(file.readLine()));
	for(const String &font : fonts)
		if(!font.isEmpty())
			load(font);
#elif APlatformAndroid

#elif APlatformWindowsDesktop

#elif APlatformUnix
	Array<ADirectory*> directories;
	directories.push_back(new ADirectory("/System/Library/Fonts"));
	directories.push_back(new ADirectory("/Library/Fonts"));
	char username[256];
	getlogin_r(username, 256);
	directories.push_back(new ADirectory("/users/" + String(username) + "/library/fonts"));
	Array<String> filters;
	filters.push_back("dfont");
	filters.push_back("ttf");
	filters.push_back("ttc");
	filters.push_back("otf");
	for(ADirectory *directory : directories)
	{
        Array<String> fonts = directory->items(filters);
		for(const String &name : fonts)
		{
			load(directory->path() + "/" + name);
		}
	}
	for(ADirectory *directory : directories)
		delete directory;
#else
    AAssert(false, "Default font's not implemented for this platform");
#endif
}

FontEngine::~FontEngine()
{
	for(auto maps : _fonts)
		for(auto data : maps.second)
			delete data.second;
}

void FontEngine::load(const String &filename)
{
	//FT_Face face;
	//FT_New_Face(_library, ().toUtf8().data(), 0, &face);
	//_fonts[face->family_name][face->style_name] = face;
	FontData *font = new FontData(filename);
	//ALogMessage("Font engine", "%s[%s:%s]", filename.toUtf8().data(), font->family().toUtf8().data(), font->style().toUtf8().data());
    if (!font->isValid())
    {
        delete font;
        return;
    }

    add(font);
	//ALogMessage("Font", "%s[%s][%s]", font.toUtf8().data(), face->family_name, face->style_name);
}

void FontEngine::load(const Array<uint8_t> &array)
{
    FontData *font = new FontData(array.data(), array.size());
    if (!font->isValid())
    {
        delete font;
        return;
    }

    add(font);
}

void FontEngine::load(const uint8_t *data, size_t size)
{
    FontData *font = new FontData(data, size);
    if (!font->isValid())
    {
        delete font;
        return;
    }

    add(font);
}

void FontEngine::add(FontData *data)
{
	FontMap::iterator familily = _fonts.find(data->family());
    if (familily == _fonts.end())
    {
        _fonts[data->family()][data->style()] = data;
    }
	else
	{
		DataMap::iterator style = familily->second.find(data->style());
		if(style == familily->second.end())
		{
			_fonts[data->family()][data->style()] = data;
		}
	}
}

FontEngine::GlyphData *FontEngine::FontChache::glyph(char16_t symbol) const
{
	if(_data && _data->isValid())
	{
		GlyphMap::const_iterator iterator = _glyphs.find(symbol);
		if(iterator == _glyphs.end())
		{
			Face face = _data->_face;
			if(FT_Set_Char_Size(face, 0, _size << 6, 72, 72))
			{
				ALogMessage("Font chache", "Couldn't set char size font: %s(%s)", face->family_name, face->style_name);
				return nullptr;
			}
			uint32_t index = FT_Get_Char_Index(face, symbol);
			if(FT_Load_Glyph(face, index, FT_LOAD_DEFAULT))
			{
				ALogMessage("Font chache", "Couldn't load char from font: %s(%s)", face->family_name, face->style_name);
				return nullptr;
			}
			if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
			{
				ALogMessage("Font chache", "Couldn't renderer char");
				return nullptr;
			}
			FT_Bitmap &bitmap = face->glyph->bitmap;

			GlyphData *data = new GlyphData();
			data->index = index;
			data->metrics.height = face->glyph->metrics.height >> 6;
			data->metrics.width = face->glyph->metrics.width >> 6;
			data->metrics.horiAdvance = face->glyph->metrics.horiAdvance >> 6;
			data->metrics.vertAdvance = face->glyph->metrics.vertAdvance >> 6;
			data->metrics.horiBearingX = face->glyph->metrics.horiBearingX >> 6;
			data->metrics.horiBearingY = face->glyph->metrics.horiBearingY >> 6;
			data->metrics.vertBearingX = face->glyph->metrics.vertBearingX >> 6;
			data->metrics.vertBearingY = face->glyph->metrics.vertBearingY >> 6;
            if (bitmap.buffer)
            {
                data->pixmap.setData(bitmap.buffer, Math::IntegerVector{ static_cast<int32_t>(bitmap.width), static_cast<int32_t>(bitmap.rows) }, APixmapDataFormat::Gray);
            }
			_glyphs[symbol] = data;
			return data;
		}
        else
        {
            return iterator->second;
        }
	}
	ALogMessage("Font chache", "Invalid font data");
	return nullptr;
}

FontEngine::FontData::FontData(const String &filename):
_face(nullptr),
_chache()
{
	if(FT_New_Face(FontEngine::_library, filename.data(), 0, &_face))
		ALogMessage("Font data", "Couldn't load font from: \"%s\"", filename.data());
}

FontEngine::FontData::FontData(const uint8_t *data, uint64_t size):
_face(nullptr),
_chache()
{
	if(FT_New_Memory_Face(FontEngine::_library, data, size, 0, &_face))
		ALogMessage("Font data", "Couldn't load font");
}

FontEngine::FontChache *FontEngine::FontData::chache(pt size) const
{
	ChacheMap::iterator iterator = _chache.find(size);
	if(iterator == _chache.end())
	{
		if(FT_Set_Char_Size(_face, 0, size << 6, 72, 72))
		{
			ALogMessage("Font chache", "Couldn't set char size font: %s(%s)", _face->family_name, _face->style_name);
			return nullptr;
		}
		uint32_t height = _face->size->metrics.height >> 6;
		if(height % 2 > 0)
			++height;
		FontChache *chache = new FontChache(const_cast<FontData*>(this), size, height, _face->size->metrics.ascender >> 6, _face->size->metrics.descender >> 6);
		_chache[size] = chache;
		return chache;
	}
	return iterator->second;
}

enum InsertBlending
{
    Replace,
    Add,
    Subtract,
    Multiply
};

enum InsertClipping
{
    Repeat,
    Clip
};

template<typename Type>
Type addWithoutOverflow(Type x, Type y)
{
    Type res = x + y;
    res |= -(res < x);

    return res;
}

template<typename Type>
Type subtractWithoutOverflow(Type x, Type y)
{
    Type res = x - y;
    res &= -(res <= x);

    return res;
}

void drawPixmap(APixmap &sourcePixmap, const APixmap &pixmap, const Math::IntegerVector &position, InsertBlending blending = Replace, InsertClipping clipping = Clip)
{
    if (sourcePixmap.getBufferSize() > 0 && pixmap.getBufferSize() > 0 && pixmap.getSize().x <= sourcePixmap.getSize().x && pixmap.getSize().y <= sourcePixmap.getSize().y)
    {
        if (sourcePixmap.getFormat() != pixmap.getFormat())
        {
            //ALogError("Pixmap", "Invalid format %s != %s", sourcePixmap.formatName().toUtf8().data(), pixmap.formatName().toUtf8().data());
            return;
        }

        switch (clipping)
        {
        case Clip:
        {
            auto iteratePixmaps = [&](uint8_t(*delegate)(uint8_t source, uint8_t value))
            {
                const Math::IntegerVector size = pixmap.getSize();
                const Math::IntegerVector sourceSize = sourcePixmap.getSize();
                const uint8_t channels = pixmap.getChannels();
                const size_t maxWidth = subtractWithoutOverflow<size_t>(size.x, subtractWithoutOverflow<size_t>(position.x + size.x, sourceSize.x));
                const size_t maxHeight = subtractWithoutOverflow<size_t>(size.y, subtractWithoutOverflow<size_t>(position.y + size.y, sourceSize.y));
                for (size_t i = 0; i < maxHeight; ++i)
                {
                    for (size_t j = 0; j < maxWidth; ++j)
                    {
                        for (size_t k = 0; k < channels; ++k)
                        {
                            const size_t sourcePosition = ((position.y + i) * sourceSize.x + (position.x + j)) * channels + k;
                            const size_t valuePosition = (i * size.x + j) * channels + k;
                            sourcePixmap[sourcePosition] = delegate(sourcePixmap[sourcePosition], pixmap[valuePosition]);
                        }
                    }
                }
            };

            switch (blending)
            {
            case Replace:
                iteratePixmaps([](uint8_t source, uint8_t value) { return value; });
                break;
            case Add:
                iteratePixmaps([](uint8_t source, uint8_t value) { return addWithoutOverflow(source, value); });
                break;
            case Subtract:
                iteratePixmaps([](uint8_t source, uint8_t value) { return subtractWithoutOverflow(source, value); });
                break;
            case Multiply:
                iteratePixmaps([](uint8_t source, uint8_t value) { return std::min<uint8_t>(uint16_t(source) * uint16_t(value), 255); });
                break;
            }
            break;
        }
        case Repeat:
        {

            auto iteratePixmaps = [&](uint8_t(*delegate)(uint8_t source, uint8_t value))
            {
                const Math::IntegerVector size = pixmap.getSize();
                const Math::IntegerVector sourceSize = sourcePixmap.getSize();
                const uint8_t channels = pixmap.getChannels();

                for (size_t i = 0; i < size.y; ++i)
                {
                    for (size_t j = 0; j < size.x; ++j)
                    {
                        const size_t sourcePosition = ((position.y + i) % sourceSize.y) * sourceSize.x + (((position.x + j) % sourceSize.x));
                        const size_t valuePosition = i * size.x + j;
                        sourcePixmap[sourcePosition] = delegate(sourcePixmap[sourcePosition], pixmap[valuePosition]);
                    }
                }
            };

            switch (blending)
            {
            case Replace:
                iteratePixmaps([](uint8_t source, uint8_t value) { return value; });
                break;
            case Add:
                iteratePixmaps([](uint8_t source, uint8_t value) { return addWithoutOverflow(source, value); });
                break;
            case Subtract:
                iteratePixmaps([](uint8_t source, uint8_t value) { return subtractWithoutOverflow(source, value); });
                break;
            case Multiply:
                iteratePixmaps([](uint8_t source, uint8_t value) { return std::min<uint8_t>(uint16_t(source) * uint16_t(value), 255); });
                break;
            }
            break;
        }
        }
    }
}

Array<FontEngine::LineInfo> FontEngine::parseLines(const String &string, const FontEngine::FontChache *fontCache, TextWrapping wrapping, int32_t maxWidth) const
{
    AAssert(fontCache, "");

    Array<LineInfo> lines;

    if (string.empty() || maxWidth == 0)
    {
        return lines;
    }

    const FontEngine::GlyphData *space = fontCache->glyph(' ');
    const int32_t spaceWidth = space->metrics.horiAdvance;
    const int32_t tabWidth = spaceWidth * 4;
    const int32_t lineHeight = fontCache->height();

    auto createLine = [&](int32_t offset) {
        lines.push_back({ 0, offset, 0 });
        return &lines.back();
    };

    LineInfo *line = createLine(0);
    int32_t width = 0;
    Array<GlyphInfo> block;
    size_t i = 0;

    auto pushBlock = [&]()
    {
        /*if (align == CenterAlign && lines.size() > 0)
        {
        ALogMessage("", "Line width: %d", lines.last().x);
        }*/
        if ((line->width + width) > maxWidth)
        {
            line->lenght -= block.size();
            line = createLine(line->offset + lineHeight);
            line->lenght = block.size();
        }
        line->width += width;
        ArrayUtils::Add(line->glyphs, block);
        block.clear();
    };
    for (; i < string.size(); ++i)
    {
        switch (string[i])
        {
        case ' ':
        {
            pushBlock();
            if (!line->glyphs.empty())
            {
                //TODO: Fix spaces at start
                line->glyphs.back().width += spaceWidth;
            }
            line->width += spaceWidth;
            ++line->lenght;
            width = 0;
            break;
        }
        case '\t':
        {
            pushBlock();
            if (!line->glyphs.empty())
            {
                //TODO: Fix spaces at start
                line->glyphs.back().width += tabWidth;
            }
            line->width += tabWidth;
            ++line->lenght;
            width = 0;
            break;
        }
        case '\n':
        {
            ++line->lenght;

            line->width += width;
            ArrayUtils::Add(line->glyphs, block);
            block.clear();

            line = createLine(line->offset + lineHeight);
            width = 0;
            break;
        }
        default:
        {
            if (width > maxWidth)
            {
                pushBlock();
            }
            const FontEngine::GlyphData *glyph = fontCache->glyph(string[i]);
            block.push_back({ static_cast<uint32_t>(glyph->metrics.horiAdvance), glyph });
            width += glyph->metrics.horiAdvance;
            ++line->lenght;
            break;
        }
        }
    }

    pushBlock();

    return lines;
}

Math::IntegerVector FontEngine::getTextSizeFromLines(const Array<LineInfo> &lines, int32_t lineHeight) const
{
    Math::IntegerVector size{};

    if (lines.empty())
    {
        return size;
    }

    for (const LineInfo &line : lines)
    {
        size.x = std::max<int32_t>(size.x, line.width);
    }
    size.y = lines.back().offset + lineHeight;

    return size;
}

Math::IntegerVector FontEngine::getTextSize(const String &string, const Font &font, TextWrapping wrapping, int32_t maxWidth) const
{
    const FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return Math::IntegerVector{};
    }
    return getTextSizeFromLines(parseLines(string, fontCache, wrapping, maxWidth), fontCache->height());
}

int32_t FontEngine::getLineHeight(const Font &font) const
{
    const FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return 0;
    }

    return fontCache->height();
}

size_t FontEngine::findIndexAt(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth, const Math::IntegerVector &position)
{
    size_t result = 0;

    const FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return result;
    }

    if (string.empty())
    {
        return result;
    }

    size_t lastSymbolPosition = std::min<int32_t>(std::max<int32_t>(position.x, 0), maxWidth);
    if (lastSymbolPosition == 0)
    {
        return result;
    }

    const size_t lineIndex = std::max<int32_t>(position.y, 0) / fontCache->height(); // positive offset / line height
    /*
    const String &substr = strings[lineIndex];
    Array<LineInfo> lines = parseLines(substr, fontCache, wrapping, lastSymbolPosition);
    result = lines.first().lenght + lineIndex; //lenght of selected line + count of \n symbols. //TODO: this just doesn't work well*/
    Array<LineInfo> lines = parseLines(string, fontCache, wrapping, maxWidth);
    if (lineIndex > lines.size())
    {
        result = string.size();
        return result;
    }

    for (size_t i = 0; i < lineIndex; ++i)
    {
        result += lines[i].lenght;
    }

    if (result < string.size())
    {
        const FontEngine::GlyphData *space = fontCache->glyph(' ');
        const int32_t spaceWidth = space->metrics.horiAdvance;
        const int32_t tabWidth = spaceWidth * 4;
        const int32_t lineHeight = fontCache->height();

        const LineInfo &l = lines[lineIndex];

        size_t w = 0;
        for (size_t i = 0, j = 0; i < l.lenght && j < l.glyphs.size(); ++i, ++result)
        {
            switch(string[i])
            {
            case ' ':
                w += spaceWidth;
                break;
            case '\t':
                w += tabWidth;
                break;
            case '\r':
            case '\n':
                return result;
            default:
                w += l.glyphs[j].glyph->metrics.horiAdvance;
                ++j;
                break;
            }

            if (w > lastSymbolPosition)
            {
                break;
            }
        }
    }

    return result;
}



Math::IntegerVector FontEngine::findTextPosition(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth, size_t index)
{
    Math::IntegerVector result{};

    const FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return result;
    }

    if(string.empty())
    {
        return result;
    }

    if (index == 0)
    {
        return result;
    }

    const FontEngine::GlyphData *space = fontCache->glyph(' ');
    const int32_t spaceWidth = space->metrics.horiAdvance;
    const int32_t tabWidth = spaceWidth * 4;
    const int32_t lineHeight = fontCache->height();

    Array<LineInfo> lines = parseLines(string, fontCache, wrapping, maxWidth);
    size_t i = 0;
    for (LineInfo &l : lines)
    {
        auto endLineIndex = i + l.lenght;
        if (endLineIndex < index)
        {
            i = endLineIndex;
            result.y += fontCache->height();
            continue;
        }

        for (size_t j = 0; i < index; ++i)
        {
            if (string[i] == ' ')
            {
                result.x += spaceWidth;
            }
            else if (string[i] == '\t')
            {
                result.x += tabWidth;
            }
            else if (string[i] == '\r' || string[i] == '\n')
            {
                break;
            }
            else
            {
                result.x += l.glyphs[j].glyph->metrics.horiAdvance;
                ++j;
            }
        }
        break;
    }

    return result;
}

APixmap FontEngine::createAtlas(const Font &font) const
{
    APixmap pixmap;

    return pixmap;
}

APixmap FontEngine::renderText(const String &string, const Font &font, TextAlign align, TextWrapping wrapping, int32_t maxWidth) const
{
    APixmap pixmap;

    const FontChache *fontCache = font._chache;
    if (!fontCache)
    {
        return pixmap;
    }

    Array<LineInfo> lines = parseLines(string, fontCache, wrapping, maxWidth);
    Math::IntegerVector pixmapSize = getTextSizeFromLines(lines, fontCache->height());
    if (pixmapSize.x == 0 || pixmapSize.y == 0)
    {
        return pixmap;
    }

    //TODO: implement resize method for Pixmap
    Array<uint8_t> array;
    array.resize(pixmapSize.getArea2(), 0);
    pixmap.setBuffer(array, pixmapSize, APixmapDataFormat::Gray);

    auto getAbsoluteAlign = [](TextAlign align) -> TextAlign {
        bool isLeftHandedText = true;
        if (align == TextAlign::Start)
        {
            return isLeftHandedText ? TextAlign::Left : TextAlign::Right;
        }
        else if(align == TextAlign::End)
        {
            return isLeftHandedText ? TextAlign::Right : TextAlign::Left;
        }

        return align;
    };

    for (const LineInfo &line : lines)
    {
        Math::IntegerVector position;
        switch (getAbsoluteAlign(align))
        {
        case TextAlign::Left:
            position = Math::IntegerVector{ 0, line.offset };
            break;
        case TextAlign::Center:
            position = Math::IntegerVector{ (pixmapSize.x / 2) - (line.width / 2), line.offset };
            break;
        case TextAlign::Start:
            position = Math::IntegerVector{ pixmapSize.x - line.width, line.offset };
            break;
        }
        /*const FontEngine::GlyphData *previousGlyph = nullptr;
        const FontEngine::GlyphData *currentGlyph = nullptr;*/
        /*const size_t end = line.index + line.lenght;
        for (size_t i = line.index; i < end; ++i)
        {
            currentGlyph = font._chache->glyph(string.at(i));
            Math::IntegerVector kerning;
            if (previousGlyph)
            {
                kerning = font._chache->kerning(previousGlyph, currentGlyph);
            }
            previousGlyph = currentGlyph;
            drawPixmap(pixmap, currentGlyph->pixmap, position + Math::IntegerVector(currentGlyph->metrics.horiBearingX, font._chache->ascent() - currentGlyph->metrics.horiBearingY));
            position.x += currentGlyph->metrics.horiAdvance + kerning.x;
        }*/
        for (const GlyphInfo &glyphInfo : line.glyphs)
        {
            const FontEngine::GlyphData *glyph = glyphInfo.glyph;
            drawPixmap(pixmap, glyph->pixmap, position + Math::IntegerVector{ static_cast<int32_t>(glyph->metrics.horiBearingX), static_cast<int32_t>(fontCache->ascent() - glyph->metrics.horiBearingY) });
            position.x += glyphInfo.width;
        }
    }
    return pixmap;
}

}
