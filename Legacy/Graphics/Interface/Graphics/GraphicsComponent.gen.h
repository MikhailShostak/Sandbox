#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <Foundation>

//CLASSGEN END REGION
#include "Core/ApplicationComponent2.gen.h"
#include "Core/AWindowEvents.h"
//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class GraphicsComponent : public Core::ApplicationComponent2
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GraphicsComponent This;
    typedef Core::ApplicationComponent2 Super;
    typedef void Interfaces;
public:
    GraphicsComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onLoad();
    void onUnload();
    void onUpdate();
//CLASSGEN END REGION
    void onCreate();

    AObject *focusedObject = nullptr;

    AObject *getFocus() const;
    void setFocus(AObject &object);
    void removeFocus(AObject &object);
    void removeFocus();

    AEventChannel inputEventChannel;

    std::function<void(AWindowTouchDownEvent &event)> onTouchDown;
    std::function<void(AWindowTouchMoveEvent &event)> onTouchMove;
    std::function<void(AWindowTouchUpEvent &event)> onTouchUp;
    std::function<void(AWindowTouchWheelEvent &event)> onTouchWheel;

    std::function<void(AWindowKeyPressEvent &event)> onKeyPress;
    std::function<void(AWindowKeyReleaseEvent &event)> onKeyRelease;
    std::function<void(AWindowKeyCharEvent &event)> onKeyChar;

    float elapsedTime = 0.0f;
    bool isInitialized = false;
    explicit operator bool() const { return isInitialized; };
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
