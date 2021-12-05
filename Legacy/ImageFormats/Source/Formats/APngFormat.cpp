#include "APngFormat.h"

#include <Foundation>

#include <png.h>
//#include <pngstruct.h>

struct sMemoryData
{
    const png_byte *pData;
    size_t size;
    sMemoryData() :
        pData(),
        size()
    {}

    explicit sMemoryData(const void* data, size_t size_data) : pData(static_cast<const png_byte*>(data)), size(size_data) {}

    inline void Read(png_bytep data, png_size_t length)
    {
        AAssert(length <= size, "Out of range");
        size -= length;
        memcpy(data, pData, length);
        pData += length;
    }
};


void readMemoryFunc(png_structp png_ptr, png_bytep data, png_size_t length)
{
    sMemoryData *pMemoryData = static_cast<sMemoryData*>(png_get_io_ptr(png_ptr));
    pMemoryData->Read(data, length);
}

bool APngFormat::isValid(const APath &path) const
{
    return true;
}

bool APngFormat::isValid(const Array<uint8_t> &buffer) const
{
    return true;
}

APixmap APngFormat::load(const APath &path) const
{
    AFile file;
    if (file.open(path, AFileOpenMode::ReadBinary))
        return decompress(file.readAll());
    return APixmap();
}

void APngFormat::save(const APath &path, const APixmap &pixmap) const
{

}

Array<uint8_t> APngFormat::compress(const APixmap &pixmap) const
{
    return Array<uint8_t>();
}

APixmap APngFormat::decompress(const Array<uint8_t> &buffer) const
{
    APixmapDataFormat format;
    sMemoryData pngdata(buffer.data(), buffer.size());

    unsigned char header[8];
    pngdata.Read(header, 8);

    if (png_sig_cmp(header, 0, 8) != 0)
        return APixmap();

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    png_set_read_fn(png, &pngdata, readMemoryFunc);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    int bit = 0;
    int f = 0;
    uint32_t width = 0;
    uint32_t height = 0;

    png_get_IHDR(png, info, &width, &height, &bit, &f, nullptr, nullptr, nullptr);

    switch (f)
    {
    case PNG_COLOR_TYPE_GRAY:
        format = APixmapDataFormat::Gray;
        break;
    case PNG_COLOR_TYPE_GA:
        format = APixmapDataFormat::GrayAlpha;
        break;
    case PNG_COLOR_TYPE_RGB:
        format = APixmapDataFormat::RGB;
        break;
    case PNG_COLOR_TYPE_RGBA:
        format = APixmapDataFormat::RGBA;
        break;
    default:
        return APixmap();
    }

    Math::IntegerVector size = Math::IntegerVector{ static_cast<int32_t>(width), static_cast<int32_t>(height) };

    int rowSize = size.x * (int8_t)format;
    uint8_t *b = new uint8_t[rowSize * size.y];

    uint8_t *row = b;
    for (int i = 0; i < size.y; ++i)
    {
        png_read_row(png, row, nullptr);
        row += rowSize;
    }
    png_destroy_read_struct(&png, &info, nullptr);
    if (format != APixmapDataFormat::RGBA)
    {
        APixmap pixmap;
        pixmap.setData(b, size, format);
        delete[] b;
        return pixmap;
    }

    uint64_t s = size.x * size.y * (int8_t)format;
    bool found = false;

    for (uint64_t i = 3; i < s; i += 4)
        if (b[i] < 255)
        {
            b[i] = 255 * (1.0f - sqrtf((255 - b[i]) / 255.0f));
            found = true;
            //break;
        }

    if (found)
    {
        APixmap pixmap;
        pixmap.setData(b, size, format);
        delete[] b;
        return pixmap;
    }

    format = APixmapDataFormat::RGB;
    s = size.x * size.y * (int8_t)format;
    uint8_t *data = new uint8_t[s];
    uint64_t skip = 0;

    for (uint64_t i = 0; i < s; i += 3)
    {
        data[i] = b[i + skip];
        data[i + 1] = b[i + 1 + skip];
        data[i + 2] = b[i + 2 + skip];
        ++skip;
    }

    APixmap pixmap;
    pixmap.setData(data, size, format);

    delete[] data;
    delete[] b;

    return pixmap;
}
