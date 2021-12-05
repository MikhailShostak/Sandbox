//CLASSGEN GENERATED REGION: Includes
#include "CanvasView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "UIComponent.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
CanvasView::CanvasView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void CanvasView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void CanvasView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

void CanvasView::resetFrameBuffer()
{
    canvas.unload();

    if (getSize().x > 0 && getSize().y > 0)
    {
        material->data.Image->loadAsRenderTarget(getSize(), APixmapDataFormat::RGBA);

        canvas.setSize(getSize());
        canvas.attachments[0] = material->data.Image;
        canvas.load();
    }
}

void CanvasView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    material->data.Image = std::make_shared<Legacy::Graphics::Texture>();
    material->data.ImageScale = Math::Vector{ 1.0, 1.0 };
    material->data.ClippingTopLeft = Math::Vector{ 0.0f, 0.0f };
    material->data.ClippingBottomRight = Math::Vector{ 1.0f, 1.0f };

    material->load();
}

void CanvasView::onUnload(AUnloadEvent &event)
{
    //material->unload();
    Super::onUnload(event);
}

void CanvasView::onLayout(AUpdateEvent &event)
{
    Super::onLayout(event);
    if (getSize().x != material->data.Image->getSize().x || getSize().y != material->data.Image->getSize().y)
    {
        resetFrameBuffer();
    }
    requestGraphicsUpdate();
}

void CanvasView::onUpdate(AUpdateEvent &event)
{
    if (!(isVisible() && isExpanded()))
    {
        return;
    }

    if (isNeededLayoutUpdate())
    {
        onLayout(event);
    }
    onDraw(event);
}

void CanvasView::onDraw(AUpdateEvent &event)
{
    if (canvas.isLoaded() /*&& isNeededGraphicsUpdate()*/)
    {
        Legacy::Graphics::GraphicsContext::pushContext(canvas);
        auto c = canvas.getCamera();
        if (SharedReference<Legacy::Graphics::CanvasCamera> camera = DynamicCast<Legacy::Graphics::CanvasCamera>(c))
        {
            camera->inverseParentMatrix = getGlobalMatrix().getInversed();
        }
        onDrawContent(event);
        Legacy::Graphics::GraphicsContext::popContext();
    }

    material->data.ModelViewProjectionMatrix = getGraphicsMatrix() * ACamera::getCurrentCamera()->getMatrix();
    material->setOpaque(false);
    Legacy::Graphics::GraphicsContext::getCurrent().draw(Component::getSprite(), material);
    Super::onDraw(event);
}

void CanvasView::onDrawContent(AUpdateEvent &event)
{
    updateViews(event);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
