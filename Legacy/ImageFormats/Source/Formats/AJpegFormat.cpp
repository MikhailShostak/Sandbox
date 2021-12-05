#include "AJpegFormat.h"

#include <jpeglib.h>

/*struct JPEGError
{
    struct jpeg_error_mgr data;
    jmp_buf jumpBuffer;
};

METHODDEF(void) jpegErrorExit(j_common_ptr info)
{
    JPEGError *jpegError = (JPEGError *) info->err;
    (*info->err->output_message)(info);
    longjmp(jpegError->jumpBuffer, 1);
}

static void jpegErrorHandle(j_common_ptr info){
    char buffer[JMSG_LENGTH_MAX];
    (*info->err->format_message)(info, buffer);
}*/

bool AJpegFormat::isValid(const APath &path) const
{
    return true;
}

bool AJpegFormat::isValid(const Array<uint8_t> &buffer) const
{
    return true;
}

void AJpegFormat::save(const APath &path, const APixmap &pixmap) const
{

}

APixmap AJpegFormat::load(const APath &path) const
{
    return APixmap();
}

Array<uint8_t> AJpegFormat::compress(const APixmap &pixmap) const
{
    return Array<uint8_t>();
}

APixmap AJpegFormat::decompress(const Array<uint8_t> &buffer) const
{
    return APixmap();
    /*struct jpeg_decompress_struct info;
    struct jpeg_error_mgr err;

    info.err = jpeg_std_error(&err);
    err.error_exit = jpegErrorHandle;

    jpeg_create_decompress(&info);

    uint8_t *img = new uint8_t[size];
    memcpy(img, data, size);
    jpeg_mem_src(&info, img, size);
    if(jpeg_read_header(&info, TRUE) != JPEG_HEADER_OK)
    {
            jpeg_destroy_decompress(&info);
            delete[] img;
            return APixmap();
    }
    jpeg_start_decompress(&info);

    Math::IntegerVector size;
    uint8_t bit;
    uint8_t channels;
    APixmapDataFormat format;

    size.set(info.output_width, info.output_height);
    bit = info.datAPrecision;
    channels = info.output_components;
    format = APixmapDataFormat::RGB;

    int rowSize = size.x() * channels;

    data = new uint8_t[rowSize * size.y()];

    uint8_t *currentRow = data;
    while (info.output_scanline < size.y())
    {
        jpeg_read_scanlines(&info, &currentRow, 1);
        currentRow += rowSize;
    }

    jpeg_finish_decompress(&info);
    jpeg_destroy_decompress(&info);
    APixmap pixmap(data, size, format);
    delete[] img;
    return pixmap;*/
}
