//CLASSGEN GENERATED REGION: Includes
#include "Texture.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "MetaObject.h"
//#include "Implementation.h"
//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
Texture::Texture()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Texture::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Wrapping", toJSONValue(Wrapping));
    object.insert("Filtration", toJSONValue(Filtration));
}
void Texture::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Wrapping", value);
    fromJSONValue(value, Wrapping);
    value = AJSONValue();
    object.read("Filtration", value);
    fromJSONValue(value, Filtration);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Legacy::Graphics::TextureWrapping Texture::getWrapping() const
{
    return this->Wrapping;
}
void Texture::setWrapping(Legacy::Graphics::TextureWrapping const &Wrapping)
{
    this->Wrapping = Wrapping;
}
void Texture::setWrapping(Legacy::Graphics::TextureWrapping &&Wrapping)
{
    this->Wrapping = std::move(Wrapping);
}
Legacy::Graphics::TextureFiltration Texture::getFiltration() const
{
    return this->Filtration;
}
void Texture::setFiltration(Legacy::Graphics::TextureFiltration const &Filtration)
{
    this->Filtration = Filtration;
}
void Texture::setFiltration(Legacy::Graphics::TextureFiltration &&Filtration)
{
    this->Filtration = std::move(Filtration);
}
//CLASSGEN END REGION
*/

AStaticRun(Texture)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<Texture>();
    object.baseObject = &manager.getMetaObject<AObject>();
    object.registerMetaProperty<Texture, APixmap>("Pixmap", &Texture::getPixmap, &Texture::setPixmap);
    object.registerMetaProperty<Texture, TextureFiltration>("Filtration", &Texture::getFiltration, &Texture::setFiltration);
    object.registerMetaProperty<Texture, TextureWrapping>("Wrapping", &Texture::getWrapping, &Texture::setWrapping);
}

Texture::Texture()
{
    LinkStaticRun(Texture);
}

Texture::Texture(const APixmap &pixmap):
    pixmap(pixmap),
    size(pixmap.getSize()),
    format(pixmap.getFormat())
{

}

Texture::~Texture()
{
    
}

::SharedReference<Legacy::Graphics::Texture> Texture::getPlaceholder()
{
    static ::SharedReference<Legacy::Graphics::Texture> texture;
    if (!texture)
    {
        Math::IntegerVector size{ 200, 200, 3 };
        Array<uint8_t> data;
        data.resize(size.getArea3());

        APixmap pixmap;
        pixmap.setBuffer(data, size, APixmapDataFormat::RGB);

        drawCheck(pixmap, 10, 0, AColor::MagentaColor() * 0.5, AColor::MagentaColor() * 0.4);
        drawCheck(pixmap, 100, 0, AColor(0.9f, 1.0f), Blending::Multiply);
        drawGrid(pixmap, 10, 0, AColor(0.9f, 1.0f), Blending::Multiply);
        drawGrid(pixmap, 100, 0, AColor(0.8f, 1.0f), Blending::Multiply);

        texture = std::make_shared<Legacy::Graphics::Texture>();
        texture->setPixmap(pixmap);
        texture->setWrapping(Legacy::Graphics::TextureWrapping::TiledWrapping);
        texture->load();
    }

    return texture;
}

::SharedReference<Legacy::Graphics::Texture> Texture::getWhiteTexture()
{
    static ::SharedReference<Legacy::Graphics::Texture> texture;
    if (!texture)
    {
        APixmap pixmap;
        pixmap.setBuffer(Array<uint8_t>{ 255, 255, 255, 255 }, Math::IntegerVector{ 1, 1 }, APixmapDataFormat::RGBA);

        texture = std::make_shared<Legacy::Graphics::Texture>();
        texture->setPixmap(pixmap);
        texture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        texture->load();
    }
    return texture;
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
