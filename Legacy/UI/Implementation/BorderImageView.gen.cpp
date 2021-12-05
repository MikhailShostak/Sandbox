//CLASSGEN GENERATED REGION: Includes
#include "BorderImageView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "Graphics"
#include "UIComponent.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
BorderImageView::BorderImageView()
{
    (*this).setFillCenter(true);
    (*this).setUseOriginalContentSize(true);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void BorderImageView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Image", toJSONValue(Image));
    object.insert("Border", toJSONValue(Border));
    object.insert("FillCenter", toJSONValue(FillCenter));
    object.insert("UseOriginalContentSize", toJSONValue(UseOriginalContentSize));
}
void BorderImageView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Image", value);
    fromJSONValue(value, Image);
    value = AJSONValue();
    object.read("Border", value);
    fromJSONValue(value, Border);
    value = AJSONValue();
    object.read("FillCenter", value);
    fromJSONValue(value, FillCenter);
    value = AJSONValue();
    object.read("UseOriginalContentSize", value);
    fromJSONValue(value, UseOriginalContentSize);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Graphics::Texture BorderImageView::getImage() const
{
    return this->Image;
}
void BorderImageView::setImage(Graphics::Texture const &Image)
{
    this->Image = Image;
}
void BorderImageView::setImage(Graphics::Texture &&Image)
{
    this->Image = std::move(Image);
}
Math::Offsets BorderImageView::getBorder() const
{
    return this->Border;
}
void BorderImageView::setBorder(Math::Offsets const &Border)
{
    this->Border = Border;
}
void BorderImageView::setBorder(Math::Offsets &&Border)
{
    this->Border = std::move(Border);
}
Boolean BorderImageView::getFillCenter() const
{
    return this->FillCenter;
}
void BorderImageView::setFillCenter(Boolean const &FillCenter)
{
    this->FillCenter = FillCenter;
}
void BorderImageView::setFillCenter(Boolean &&FillCenter)
{
    this->FillCenter = std::move(FillCenter);
}
Boolean BorderImageView::getUseOriginalContentSize() const
{
    return this->UseOriginalContentSize;
}
void BorderImageView::setUseOriginalContentSize(Boolean const &UseOriginalContentSize)
{
    this->UseOriginalContentSize = UseOriginalContentSize;
    requestLayoutUpdate();
}
void BorderImageView::setUseOriginalContentSize(Boolean &&UseOriginalContentSize)
{
    this->UseOriginalContentSize = std::move(UseOriginalContentSize);
    requestLayoutUpdate();
}
//CLASSGEN END REGION
*/
AStaticRun(BorderImageViewMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
        MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<BorderImageView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const BorderImageView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<BorderImageView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<BorderImageView, SharedReference<Legacy::Graphics::Texture>>("Image", &BorderImageView::getImage, &BorderImageView::setImage, false);
    object.registerMetaProperty<BorderImageView, AColor>("Color", &BorderImageView::getColor, &BorderImageView::setColor, false);
    object.registerMetaProperty<BorderImageView, UIOffsets>("Border", &BorderImageView::getBorder, &BorderImageView::setBorder, false);
    object.registerMetaProperty<BorderImageView, bool>("FillCenter", &BorderImageView::getFillCenter, &BorderImageView::setFillCenter, false);
    manager.registerMetaObject("UI.BorderImageView", object);
    CLASSGEN_END_REGION
}

CLASSGEN_GENERATED_REGION_OBJECT
void BorderImageView::serialize(AJSONObject &object) const
{
    object.insert("Border", toJSONValue(border));
    object.insert("FillCenter", toJSONValue(fillCenter));

    Super::serialize(object);
}
void BorderImageView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;

    value = AJSONValue();
    object.read("Border", value);
    fromJSONValue(value, border);

    value = AJSONValue();
    object.read("FillCenter", value);
    fromJSONValue(value, fillCenter);
}
UIOffsets const &BorderImageView::getBorder() const
{
    return this->border;
}
void BorderImageView::setBorder(UIOffsets const &border)
{
    this->border = border;
}
bool const &BorderImageView::getFillCenter() const
{
    return this->fillCenter;
}
void BorderImageView::setFillCenter(bool fillCenter)
{
    this->fillCenter = fillCenter;
}
Boolean BorderImageView::getUseOriginalContentSize() const
{
    return this->UseOriginalContentSize;
}
void BorderImageView::setUseOriginalContentSize(Boolean const &UseOriginalContentSize)
{
    this->UseOriginalContentSize = UseOriginalContentSize;
    requestLayoutUpdate();
}
void BorderImageView::setUseOriginalContentSize(Boolean &&UseOriginalContentSize)
{
    this->UseOriginalContentSize = std::move(UseOriginalContentSize);
    requestLayoutUpdate();
}
CLASSGEN_END_REGION

void BorderImageView::onCreate()
{
    topLeft = std::make_shared<DynamicImageMaterial>();
    top = std::make_shared<DynamicImageMaterial>();
    topRight = std::make_shared<DynamicImageMaterial>();
    left = std::make_shared<DynamicImageMaterial>();
    center = std::make_shared<DynamicImageMaterial>();
    right = std::make_shared<DynamicImageMaterial>();
    bottomLeft = std::make_shared<DynamicImageMaterial>();
    bottom = std::make_shared<DynamicImageMaterial>();
    bottomRight = std::make_shared<DynamicImageMaterial>();

    setBorder(UIOffsets{ 0, 0, 0, 0 });
    setImage(Legacy::Graphics::Texture::getPlaceholder());
}

Math::IntegerVector BorderImageView::getContentSize() const
{
    return getUseOriginalContentSize() ? getImage()->getSize() : this->border.getSpace();
}

const SharedReference<Legacy::Graphics::Texture> &BorderImageView::getImage() const
{
    return center->data.Image;
}

void BorderImageView::setImage(const SharedReference<Legacy::Graphics::Texture> &image)
{
    topLeft->data.Image = image;
    top->data.Image = image;
    topRight->data.Image = image;
    left->data.Image = image;
    center->data.Image = image;
    right->data.Image = image;
    bottomLeft->data.Image = image;
    bottom->data.Image = image;
    bottomRight->data.Image = image;
    updateOpaque();
    if (getParent())
    {
        getParent()->requestGraphicsUpdate();
    }
}

const AColor &BorderImageView::getColor() const
{
    return center->data.Color;
}

void BorderImageView::setColor(const AColor &color)
{
    topLeft->data.Color = color;
    top->data.Color = color;
    topRight->data.Color = color;
    left->data.Color = color;
    center->data.Color = color;
    right->data.Color = color;
    bottomLeft->data.Color = color;
    bottom->data.Color = color;
    bottomRight->data.Color = color;
    updateOpaque();
    if (getParent())
    {
        getParent()->requestGraphicsUpdate();
    }
}

void BorderImageView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if (getSize().isEmpty())
    {
        setSize(getContentSize());
    }
    if (!center->isLoaded())
    {
        topLeft->load();
        top->load();
        topRight->load();
        left->load();
        center->load();
        right->load();
        bottomLeft->load();
        bottom->load();
        bottomRight->load();
    }
    AAssert(center->data.Image, "Image is not set for UI::BorderImageView");
    if (!center->data.Image->isLoaded())
    {
        center->data.Image->load();
    }
}

void BorderImageView::onDraw(AUpdateEvent &event)
{
    auto getMatrixForSubSprite = [this](const Math::IntegerVector &offset, const Math::IntegerVector &size) {
        Math::Matrix m = Math::Matrix::getScale2(size.getXY<Math::Vector>()) * Math::Matrix::getTranslation(offset.getXY<Math::Vector>()) * getGlobalMatrix();
        return m;
    };

    Math::IntegerVector size = getSize();
    Math::IntegerVector centerSize{ size.x - border.left - border.right, size.y - border.top - border.bottom };
    Math::Vector centerScale = Math::Vector{ float(getImage()->getSize().x - border.left - border.right) / centerSize.x, float(getImage()->getSize().y - border.top - border.bottom) / centerSize.y };
    Math::IntegerVector rightBottomSegmentsOffset{ size.x - border.right, size.y - border.bottom };

    auto drawSubSprite = [&](const SharedReference<DynamicImageMaterial> &material, const Math::IntegerVector &offset, const Math::IntegerVector &size, const Math::Vector &scale = Math::Vector{ 1, 1 }) {
        material->data.ImageScale = { float(size.x) / getImage()->getSize().x, float(size.y) / getImage()->getSize().y };

        Legacy::Graphics::TextureWrapping wrapping = material->data.Image->getWrapping();
        if (wrapping == Legacy::Graphics::TextureWrapping::WrapToBorder || wrapping == Legacy::Graphics::TextureWrapping::WrapToEdge)
        {
            material->data.ImageScale.x *= scale.x;
            material->data.ImageScale.y *= scale.y;
        }
        else if (material.get() == center.get() && (wrapping == Legacy::Graphics::TextureWrapping::HorizontalTiledWrapping || wrapping == Legacy::Graphics::TextureWrapping::HorizontalMirroredTiledWrapping))
        {
            material->data.ImageScale.y *= scale.y;
        }
        else if (material.get() == center.get() && (wrapping == Legacy::Graphics::TextureWrapping::VerticalTiledWrapping || wrapping == Legacy::Graphics::TextureWrapping::VerticalMirroredTiledWrapping))
        {
            material->data.ImageScale.x *= scale.x;
        }

        material->data.ModelViewProjectionMatrix = getMatrixForSubSprite(offset, size) * ACamera::getCurrentCamera()->getMatrix();
        material->data.ClippingTopLeft = Math::Vector{ 0.0f, 0.0f };
        material->data.ClippingBottomRight = Math::Vector{ 1.0f, 1.0f };
        Legacy::Graphics::GraphicsContext::getCurrent().draw(Component::getSprite(), material);
    };

    center->data.ImageOffset.x = float(border.left) / getImage()->getSize().x;
    center->data.ImageOffset.y = float(border.top) / getImage()->getSize().y;

    top->data.ImageOffset.x = center->data.ImageOffset.x;
    bottom->data.ImageOffset.x = center->data.ImageOffset.x;
    left->data.ImageOffset.y = center->data.ImageOffset.y;
    right->data.ImageOffset.y = center->data.ImageOffset.y;

    bottomRight->data.ImageOffset.x = float(getImage()->getSize().x - border.right) / getImage()->getSize().x;
    bottomRight->data.ImageOffset.y = float(getImage()->getSize().y - border.bottom) / getImage()->getSize().y;

    topRight->data.ImageOffset.x = bottomRight->data.ImageOffset.x;
    bottomLeft->data.ImageOffset.y = bottomRight->data.ImageOffset.y;
    bottom->data.ImageOffset.y = bottomRight->data.ImageOffset.y;
    right->data.ImageOffset.x = bottomRight->data.ImageOffset.x;

    /*drawSubSprite(topLeft, Math::IntegerVector(-halfSize.x + halfBorder.left, halfSize.y - halfBorder.top), Math::IntegerVector(border.left, border.top));
    drawSubSprite(top, Math::IntegerVector(centerOffset.x, halfSize.y - halfBorder.top), Math::IntegerVector(centerSize.x, border.top), Math::IntegerVector(centerScale.x, 1));
    drawSubSprite(topRight, Math::IntegerVector(halfSize.x - halfBorder.right, halfSize.y - halfBorder.top), Math::IntegerVector(border.right, border.top));
    drawSubSprite(left, Math::IntegerVector(-halfSize.x + halfBorder.left, centerOffset.y), Math::IntegerVector(border.left, centerSize.y), Math::IntegerVector(1, centerScale.y));
    drawSubSprite(center, Math::IntegerVector(centerOffset.x, centerOffset.y), centerSize, centerScale);
    drawSubSprite(right, Math::IntegerVector(halfSize.x - halfBorder.right, centerOffset.y), Math::IntegerVector(border.right, centerSize.y), Math::IntegerVector(1, centerScale.y));
    drawSubSprite(bottomLeft, Math::IntegerVector(-halfSize.x + halfBorder.left, -halfSize.y + halfBorder.bottom), Math::IntegerVector(border.left, border.bottom));
    drawSubSprite(bottom, Math::IntegerVector(centerOffset.x, -halfSize.y + halfBorder.bottom), Math::IntegerVector(centerSize.x, border.bottom), Math::IntegerVector(centerScale.x, 1));
    drawSubSprite(bottomRight, Math::IntegerVector(halfSize.x - halfBorder.right, -halfSize.y + halfBorder.bottom), Math::IntegerVector(border.right, border.bottom));*/
    /*auto a = {topLeft, top, topRight, left, center, right, bottomLeft, bottom, bottomRight};
    for (uint8_t i = 0; i < 0; ++i)
    {
        for (uint8_t j = 0; j < 0; ++j)
        {
            drawSubSprite(a[i * j], Math::IntegerVector(0, rightTopSegmentsOffset.y), Math::IntegerVector(border.left, border.top));
        }
    }*/

    if (border.top > 0)
    {
        if (border.left > 0)
        {
            drawSubSprite(topLeft, Math::IntegerVector{ 0, 0 }, Math::IntegerVector{ border.left, border.top });
        }
        drawSubSprite(top, Math::IntegerVector{ border.left, 0 }, Math::IntegerVector{ centerSize.x, border.top }, Math::Vector{ centerScale.x, 1 });
        if (border.right > 0)
        {
            drawSubSprite(topRight, Math::IntegerVector{ rightBottomSegmentsOffset.x, 0 }, Math::IntegerVector{ border.right, border.top });
        }
    }

    if (border.left > 0)
    {
        drawSubSprite(left, Math::IntegerVector{ 0, border.top }, Math::IntegerVector{ border.left, centerSize.y }, Math::Vector{ 1, centerScale.y });
    }
    if (getFillCenter() && centerScale.x != 0 && centerScale.y != 0)
    {
        drawSubSprite(center, Math::IntegerVector{ border.left, border.top }, centerSize, centerScale);
    }
    if (border.right > 0)
    {
        drawSubSprite(right, Math::IntegerVector{ rightBottomSegmentsOffset.x, border.top }, Math::IntegerVector{ border.right, centerSize.y }, Math::Vector{ 1, centerScale.y });
    }
    if (border.bottom > 0)
    {
        if (border.left > 0)
        {
            drawSubSprite(bottomLeft, Math::IntegerVector{ 0, rightBottomSegmentsOffset.y }, Math::IntegerVector{ border.left, border.bottom });
        }
        drawSubSprite(bottom, Math::IntegerVector{ border.left, rightBottomSegmentsOffset.y }, Math::IntegerVector{ centerSize.x, border.bottom }, Math::Vector{ centerScale.x, 1 });
        if (border.right > 0)
        {
            drawSubSprite(bottomRight, Math::IntegerVector{ rightBottomSegmentsOffset.x, rightBottomSegmentsOffset.y }, Math::IntegerVector{ border.right, border.bottom });
        }
    }

    Super::onDraw(event);
}

void BorderImageView::updateOpaque()
{
    if (getImage() && (getImage()->getFormat() == APixmapDataFormat::GrayAlpha || getImage()->getFormat() == APixmapDataFormat::RGBA || getColor().alpha() < 1.0f))
    {
        topLeft->setOpaque(false);
        top->setOpaque(false);
        topRight->setOpaque(false);
        left->setOpaque(false);
        center->setOpaque(false);
        right->setOpaque(false);
        bottomLeft->setOpaque(false);
        bottom->setOpaque(false);
        bottomRight->setOpaque(false);
    }
    else
    {
        topLeft->setOpaque(true);
        top->setOpaque(true);
        topRight->setOpaque(true);
        left->setOpaque(true);
        center->setOpaque(true);
        right->setOpaque(true);
        bottomLeft->setOpaque(true);
        bottom->setOpaque(true);
        bottomRight->setOpaque(true);
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
