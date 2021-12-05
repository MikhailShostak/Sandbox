#pragma once
#include "APixmapFormat.h"

class AJpegFormat : public APixmapFormat
{
public:

    virtual bool isValid(const APath &path) const;
    virtual bool isValid(const Array<uint8_t> &buffer) const;

    virtual void save(const APath &path, const APixmap &pixmap) const;
    virtual APixmap load(const APath &path) const;

    virtual Array<uint8_t> compress(const APixmap &pixmap) const;
    virtual APixmap decompress(const Array<uint8_t> &buffer) const;

};
