//CLASSGEN GENERATED REGION: Includes
#include "WindowFlowState.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "MetaObjectSerializationHelper.h"
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
WindowFlowState::WindowFlowState()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void WindowFlowState::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Window", toJSONValue(Window));
}
void WindowFlowState::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Window", value);
    fromJSONValue(value, Window);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<Core::Window> WindowFlowState::getWindow() const
{
    return this->Window;
}
void WindowFlowState::setWindow(SharedReference<Core::Window> const &Window)
{
    this->Window = Window;
}
void WindowFlowState::setWindow(SharedReference<Core::Window> &&Window)
{
    this->Window = std::move(Window);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
