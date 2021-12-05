#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "TextureWrapping.gen.h"
#include "TextureFiltration.gen.h"

//CLASSGEN END REGION
#include "Graphics/HardwareHandle.h"
//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class Texture : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Texture This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    Graphics::TextureWrapping Wrapping;
Graphics::TextureFiltration Filtration;
public:
    Texture();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Graphics::TextureWrapping getWrapping() const;
    void setWrapping(Graphics::TextureWrapping const &Wrapping);
    void setWrapping(Graphics::TextureWrapping &&Wrapping);
    Graphics::TextureFiltration getFiltration() const;
    void setFiltration(Graphics::TextureFiltration const &Filtration);
    void setFiltration(Graphics::TextureFiltration &&Filtration);
//CLASSGEN END REGION
};
*/
class Texture : public AObject, public HardwareHandle<Texture>
{
    TextureWrapping wrapping = TextureWrapping::WrapToEdge;
    TextureFiltration filtration = TextureFiltration::Anisotropic;
    APixmap pixmap;
    Math::IntegerVector size;
    APixmapDataFormat format;
public:

    static ::SharedReference<Texture> getPlaceholder();
    static ::SharedReference<Texture> getWhiteTexture();

    Texture();

    Texture(const APixmap &pixmap);
    ~Texture();

    void onActivate() {}
    void onDeactivate() {}

    void loadAsRenderTarget(const Math::IntegerVector &targetSize, APixmapDataFormat format)
    {
        unload();
        this->pixmap.clear();
        this->format = format;
        this->size = targetSize;
        load();
    }

    TextureFiltration getFiltration() const { return this->filtration; }
    void setFiltration(TextureFiltration filtration) { this->filtration = filtration; }

    TextureWrapping getWrapping() const { return this->wrapping; }
    void setWrapping(TextureWrapping wrapping) { this->wrapping = wrapping; }

    const APixmap &getPixmap() const { return this->pixmap; }
    void setPixmap(const APixmap &pixmap) { this->pixmap = pixmap; size = pixmap.getSize(); format = pixmap.getFormat(); }

    APixmapDataFormat getFormat() const { return format; }
    uint8_t getChannels() const { return uint8_t(format); }

    bool hasAlpha() const { return format == APixmapDataFormat::GrayAlpha || this->format == APixmapDataFormat::RGBA; }

    Math::IntegerVector getSize() const { return size; }
    APixmap::SizeType getBufferSize() const { return this->pixmap.getBufferSize(); }

    const Array<uint8_t> &getBuffer() const { return this->pixmap.getBuffer(); }
    const uint8_t *getData() const { return this->pixmap.getData(); }

    //InplaceStorage<struct TexturePrivateData, 8, 8> Data;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
