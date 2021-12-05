//CLASSGEN GENERATED REGION: Includes
#include "UIComposition.gen.h"
//CLASSGEN END REGION
#include <Graphics>
#include "Raycast.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
UIComposition::UIComposition()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void UIComposition::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Root", toJSONValue(Root));
}
void UIComposition::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Root", value);
    fromJSONValue(value, Root);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<UI::View> UIComposition::getRoot() const
{
    return this->Root;
}
void UIComposition::setRoot(SharedReference<UI::View> const &Root)
{
    this->Root = Root;
}
void UIComposition::setRoot(SharedReference<UI::View> &&Root)
{
    this->Root = std::move(Root);
}
//CLASSGEN END REGION
void UIComposition::onUpdate()
{
    if(!initialized)
    {
        initialized = true;
        
        AObject obj;
        ALoadEvent e(obj);
        Root->sendEvent(e);

        SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
        component->onTouchDown = [this](AWindowTouchDownEvent &event)
        {
            if (!Root)
            {
                return;
            }

            processTouchEvent<AWindowTouchDownEvent>(event, camera, Root, [](AWindowTouchDownEvent &event, UI::GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<UI::View>, Math::IntegerVector>> &views)
            {
                if (recognizer.shouldProcessTouchDown(event))
                {
                    recognizer.onTouchDown(event, point, isInside, views);
                }
            });
        };
        component->onTouchMove = [this](AWindowTouchMoveEvent &event)
        {
            if (!Root)
            {
                return;
            }

            processTouchEvent<AWindowTouchMoveEvent>(event, camera, Root, [](AWindowTouchMoveEvent &event, UI::GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<UI::View>, Math::IntegerVector>> &views)
            {
                recognizer.onTouchMove(event, point, isInside, views);
            });
        };
        component->onTouchUp = [this](AWindowTouchUpEvent &event)
        {
            if (!Root)
            {
                return;
            }

            processTouchEvent<AWindowTouchUpEvent>(event, camera, Root, [](AWindowTouchUpEvent &event, UI::GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<UI::View>, Math::IntegerVector>> &views)
            {
                recognizer.onTouchUp(event, point, isInside, views);
            });
        };
        component->onTouchWheel = [this](AWindowTouchWheelEvent &event)
        {
            if (!Root)
            {
                return;
            }

            processTouchEvent<AWindowTouchWheelEvent>(event, camera, Root, [](AWindowTouchWheelEvent &event, UI::GestureRecognizer &recognizer, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<UI::View>, Math::IntegerVector>> &views) {
                recognizer.onTouchWheel(event, point, isInside, views);
            });
        };
        //component.onKeyPress = ;
        //component.onKeyRelease = ;
        //component.onKeyChar = ;
    }
    
    ACamera::pushCamera(camera);
    Graphics::API::setViewport(Math::IntegerRectangle{ { 0, 0 }, camera.resolution });
    AObject obj;
    AUpdateEvent e(obj);
    Root->sendEvent(e);
    ACamera::popCamera();
}

void UIComposition::onResize(const Math::IntegerVector &size)
{
    Root->setSize(size);
    camera.resolution = size;
}
*/
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
