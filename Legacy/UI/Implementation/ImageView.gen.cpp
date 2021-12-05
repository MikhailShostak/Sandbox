//CLASSGEN GENERATED REGION: Includes
#include "ImageView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Graphics>
#include "MetaObject.h"
#include "UIComponent.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
ImageView::ImageView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ImageView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Image", toJSONValue(Image));
}
void ImageView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Image", value);
    fromJSONValue(value, Image);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Legacy::Graphics::Texture ImageView::getImage() const
{
    return this->Image;
}
void ImageView::setImage(Legacy::Graphics::Texture const &Image)
{
    this->Image = Image;
}
void ImageView::setImage(Legacy::Graphics::Texture &&Image)
{
    this->Image = std::move(Image);
}
//CLASSGEN END REGION
*/

AStaticRun(ImageViewMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
        MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<ImageView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const ImageView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<ImageView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<ImageView, SharedReference<Legacy::Graphics::Texture>>("Image", &ImageView::getImage, &ImageView::setImage, false);
    object.registerMetaProperty<ImageView, AColor>("Color", &ImageView::getColor, &ImageView::setColor, false);
    object.registerMetaProperty<ImageView, Math::IntegerVector>("ContentSize", &ImageView::getContentSize, static_cast<void(ImageView::*)(Math::IntegerVector const &)>(nullptr), false);
    manager.registerMetaObject("UI.ImageView", object);
    CLASSGEN_END_REGION
}
CLASSGEN_GENERATED_REGION_OBJECT
void ImageView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ImageView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
CLASSGEN_END_REGION

void ImageView::onCreate()
{
    setSizePolicy(SizePolicy::ContentWrapped);
    material = std::make_shared<DynamicImageMaterial>();
    material->data.Image = Legacy::Graphics::Texture::getPlaceholder();
    material->data.ImageScale = Math::Vector{ 1.0, 1.0 };
    material->data.ClippingTopLeft = Math::Vector{ 0.0f, 0.0f };
    material->data.ClippingBottomRight = Math::Vector{ 1.0f, 1.0f };
}

const SharedReference<Legacy::Graphics::Texture> &ImageView::getImage() const
{
    return material->data.Image;
}

void ImageView::setImage(const SharedReference<Legacy::Graphics::Texture> &image)
{
    if (image)
    {
        material->data.Image = image;
    }
    else
    {
        material->data.Image = Legacy::Graphics::Texture::getPlaceholder();
    }

    if (getImage() && (getImage()->getFormat() == APixmapDataFormat::GrayAlpha || getImage()->getFormat() == APixmapDataFormat::RGBA || getColor().alpha() < 1.0f))
    {
        material->setOpaque(false);
    }
    else
    {
        material->setOpaque(true);
    }
}

const AColor &ImageView::getColor() const
{
    return material->data.Color;
}

void ImageView::setColor(const AColor &color)
{
    material->data.Color = color;
}

Math::Vector const &ImageView::getImageOffset() const
{
    return material->data.ImageOffset;
}

void ImageView::setImageOffset(Math::Vector const &offset)
{
    material->data.ImageOffset = offset;
}

Math::IntegerVector ImageView::getContentSize() const
{
    return material->data.Image->getSize();
}

void ImageView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if (getSize().isEmpty())
    {
        setSize(getMinimalSize());
    }
    if (!material->isLoaded())
    {
        material->load();
    }
    AAssert(material->data.Image, "Image is not set for UI::ImageView");
    if (!material->data.Image->isLoaded())
    {
        material->data.Image->load();
    }
}

void ImageView::onUnload(AUnloadEvent &event)
{
    //material->unload();
    Super::onUnload(event);
}
void ImageView::onDraw(AUpdateEvent &event)
{
    Super::onDraw(event);
    Legacy::Graphics::TextureWrapping wrapping = material->data.Image->getWrapping();
    if (wrapping == Legacy::Graphics::TextureWrapping::TiledWrapping || wrapping == Legacy::Graphics::TextureWrapping::MirroredTiledWrapping)
    {
        material->data.ImageScale = { Math::FloatType(getSize().x) / material->data.Image->getSize().x, Math::FloatType(getSize().y) / material->data.Image->getSize().y };
    }
    else if (wrapping == Legacy::Graphics::TextureWrapping::HorizontalTiledWrapping || wrapping == Legacy::Graphics::TextureWrapping::HorizontalMirroredTiledWrapping)
    {
        material->data.ImageScale = { Math::FloatType(getSize().x) / material->data.Image->getSize().x, 1.0 };
    }
    else if (wrapping == Legacy::Graphics::TextureWrapping::VerticalTiledWrapping || wrapping == Legacy::Graphics::TextureWrapping::VerticalMirroredTiledWrapping)
    {
        material->data.ImageScale = { 1.0, Math::FloatType(getSize().y) / material->data.Image->getSize().y };
    }
    else
    {
        material->data.ImageScale = { 1.0, 1.0 };
    }
    material->data.ModelViewProjectionMatrix = getGraphicsMatrix() * ACamera::getCurrentCamera()->getMatrix();
    Legacy::Graphics::GraphicsContext::getCurrent().draw(Component::getSprite(), material);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
