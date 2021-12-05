#pragma once

#include <Math>

enum class APixmapDataFormat : uint8_t
{
    Undefined,
    Gray,
    GrayAlpha,
    RGB,
    RGBA
};

class APixmap
{
    Array<uint8_t> buffer;
    Math::IntegerVector size;
    APixmapDataFormat format;
public:

    using SizeType = typename Array<uint8_t>::size_type;

    APixmapDataFormat getFormat() const { return format; }
    uint8_t getChannels() const { return uint8_t(format); }

    bool hasAlpha() const { return format == APixmapDataFormat::GrayAlpha || this->format == APixmapDataFormat::RGBA; }

    Math::IntegerVector getSize() const { return size; }
    SizeType getBufferSize() const { return this->buffer.size(); }

    Array<uint8_t> &getBuffer() { return buffer; }
    const Array<uint8_t> &getBuffer() const { return buffer; }
    void setBuffer(const Array<uint8_t> &buffer, Math::IntegerVector pixampSize, APixmapDataFormat pixmapFormat);
    void setBuffer(Array<uint8_t> &&buffer, Math::IntegerVector pixampSize, APixmapDataFormat pixmapFormat);

    uint8_t *getData() { return buffer.data(); }
    const uint8_t *getData() const { return this->buffer.data(); }
    void setData(uint8_t *data, Math::IntegerVector pixampSize, APixmapDataFormat pixmapFormat);

    uint8_t &operator [](SizeType index) { return this->buffer[index]; }
    const uint8_t &operator [](SizeType index) const { return this->buffer[index]; }

    void resize(const Math::IntegerVector &size);

    void clear()
    {
        format = APixmapDataFormat::Undefined;
        size.clear();
        buffer.clear();
    }

};

inline void APixmap::setBuffer(const Array<uint8_t> &buffer, Math::IntegerVector pixmapSize, APixmapDataFormat pixmapFormat)
{
    AAssert(!buffer.empty(), "Buffer is empty");
    AAssert(pixmapSize.x > 0 && pixmapSize.y > 0, "Invalid size");
    AAssert(buffer.size() == Array<uint8_t>::size_type(pixmapSize.getArea2()) * int8_t(pixmapFormat), "Invalid size");

    this->buffer = buffer;
    this->size = pixmapSize;
    this->format = pixmapFormat;
}

inline void APixmap::setBuffer(Array<uint8_t> &&buffer, Math::IntegerVector pixmapSize, APixmapDataFormat pixmapFormat)
{
    AAssert(!buffer.empty(), "Buffer is empty");
    AAssert(pixmapSize.x > 0 && pixmapSize.y > 0, "Invalid size");
    AAssert(buffer.size() == Array<uint8_t>::size_type(pixmapSize.getArea2()) * int8_t(pixmapFormat), "Invalid size");

    this->buffer = buffer;
    this->size = pixmapSize;
    this->format = pixmapFormat;
}

inline void APixmap::setData(uint8_t *data, Math::IntegerVector pixmapSize, APixmapDataFormat pixmapFormat)
{
    AAssert(data, "Data is not set");
    AAssert(pixmapSize.x > 0 && pixmapSize.y > 0, "Invalid size");

    this->buffer = Array<uint8_t>(data, data + Array<uint8_t>::size_type(pixmapSize.getArea2()) * int8_t(pixmapFormat));
    this->size = pixmapSize;
    this->format = pixmapFormat;
}


inline void APixmap::resize(const Math::IntegerVector &size)
{
    if (!this->buffer.empty())
    {
        int w = this->size.x;
        int h = this->size.y;
        Array<uint8_t> buffer = this->buffer;
        this->buffer.resize(size.x * size.y * (int8_t)this->format);
        int A, B, C, D, x, y, index, rgba;
        float x_ratio = ((float)(w-1)) / size.x ;
        float y_ratio = ((float)(h-1)) / size.y ;
        float x_diff, y_diff;
        int offset = 0 ;
        for (int32_t i = 0; i < size.y; ++i) {
            for (int32_t j = 0; j < size.x; ++j) {
                for (int8_t h = 0; h < (int8_t)this->format; ++h)
                {
                    x = (int)(x_ratio * j) ;
                    y = (int)(y_ratio * i) ;
                    x_diff = (x_ratio * j) - x ;
                    y_diff = (y_ratio * i) - y ;
                    index = y*w*h + x*h + h ;

                    // range is 0 to 255 thus bitwise AND with 0xff
                    A = buffer[index] & 0xff;
                    B = buffer[index+1] & 0xff;
                    C = buffer[index+w] & 0xff;
                    D = buffer[index+w+1] & 0xff;

                    // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
                    rgba = (int)(
                            A * (1-x_diff) * (1-y_diff) + B * (x_diff) * (1-y_diff) +
                            C * (y_diff) * (1-x_diff) + D * (x_diff * y_diff)
                            ) ;

                    this->buffer[offset++] = rgba;
                }
            }
        }
        this->size = size;
    }
}
