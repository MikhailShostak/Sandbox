//CLASSGEN GENERATED REGION: Includes
#include "GraphicsComponent.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

#if PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#if PLATFORM_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Core/ACommonEvents.h"
#include "Window2.gen.h"

namespace Core
{
extern std::vector<Window2*> windows;
}

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
GraphicsComponent::GraphicsComponent()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GraphicsComponent::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void GraphicsComponent::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
void GraphicsComponent::onCreate()
{
    
}

void GraphicsComponent::onLoad()
{
    /* Initialize the library */
    if (glfwInit())
    {
        isInitialized = true;
    }
}

void GraphicsComponent::onUnload()
{
    if(isInitialized)
    {
        glfwTerminate();
    }
}

AObject *GraphicsComponent::getFocus() const
{
    return focusedObject;
}

void GraphicsComponent::setFocus(AObject &object)
{
    if (focusedObject == &object)
    {
        return;
    }

    if (focusedObject)
    {
        AFocusOutEvent e(*this);
        focusedObject->sendEvent(e);
    }
    focusedObject = &object;
    AFocusInEvent e(*this);
    focusedObject->sendEvent(e);
}

void GraphicsComponent::removeFocus(AObject &object)
{
    if (focusedObject == &object)
    {
        AFocusOutEvent e(*this);
        focusedObject->sendEvent(e);
        focusedObject = nullptr;
    }
}

void GraphicsComponent::removeFocus()
{
    if (focusedObject != nullptr)
    {
        AFocusOutEvent e(*this);
        focusedObject->sendEvent(e);
        focusedObject = nullptr;
    }
}

ASteadyClock::duration dt;
auto tp = ASteadyClock::now();

void GraphicsComponent::onUpdate()
{
    dt = ASteadyClock::now() - tp;
    tp = ASteadyClock::now();
    this->elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() / 1000.f;
    
    for(const auto &w : Core::windows)
    {
        if(w->IsActive())
        {
            w->OnUpdate();
        }
    }

    glfwPollEvents();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
