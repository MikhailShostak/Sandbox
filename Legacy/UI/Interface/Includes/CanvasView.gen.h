#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"

//CLASSGEN END REGION
#include "Core/FrameClock.h"
#include "Graphics/Canvas.h"
#include "Materials/UIImageMaterial.g.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class CanvasView : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef CanvasView This;
    typedef UI::View Super;
    typedef void Interfaces;
public:
    CanvasView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

protected:
    SharedReference<DynamicImageMaterial> material = std::make_shared<DynamicImageMaterial>();
    Legacy::Graphics::Canvas canvas;
public:

    const SharedReference<ACamera> &getCamera() const { return canvas.getCamera(); }
    void setCamera(const SharedReference<ACamera> &camera) { canvas.setCamera(camera); }

    void resetFrameBuffer();
    void onLoad(ALoadEvent &event) override;
    void onUnload(AUnloadEvent &event) override;
    void onLayout(AUpdateEvent &event) override;
    void onUpdate(AUpdateEvent &event) override;
    void onDraw(AUpdateEvent &event) override;

    virtual void onDrawContent(AUpdateEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
