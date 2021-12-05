#pragma once

#include <Foundation>

class APixmap;

class APixmapFormat
{
public:

    virtual ~APixmapFormat() {}

    virtual bool isValid(const APath &path) const = 0;
    virtual bool isValid(const Array<uint8_t> &buffer) const = 0;

    virtual APixmap load(const APath &path) const = 0;
    virtual void save(const APath &path, const APixmap &pixmap) const = 0;

    virtual Array<uint8_t> compress(const APixmap &pixmap) const = 0;
    virtual APixmap decompress(const Array<uint8_t> &buffer) const = 0;

};
