//CLASSGEN GENERATED REGION: Includes
#include "ViewWindow.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
ViewWindow::ViewWindow()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ViewWindow::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("View", toJSONValue(View));
}
void ViewWindow::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("View", value);
    fromJSONValue(value, View);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<UI::View> ViewWindow::getView() const
{
    return this->View;
}
void ViewWindow::setView(SharedReference<UI::View> const &View)
{
    this->View = View;
}
void ViewWindow::setView(SharedReference<UI::View> &&View)
{
    this->View = std::move(View);
}
//CLASSGEN END REGION
*/
ViewWindow::ViewWindow()
{
    rootRenderer.debugName = "UI";
    //rootCamera.resolution = getGeometry().size;
    rootCamera.fieldOfView = 45.0f;
    rootCamera.farClipping = 100;
    rootCamera.nearClipping = 0.1;
}

void ViewWindow::serialize(AJSONObject &object) const
{
    TemplateWindow<Component, PerspectiveCamera>::serialize(object);
}
void ViewWindow::deserialize(const AJSONObject &object)
{
    TemplateWindow<Component, PerspectiveCamera>::deserialize(object);
}

SharedReference<UI::View> ViewWindow::getView() const
{
    return rootComponent->getView();
}

void ViewWindow::setView(const SharedReference<UI::View>& view)
{
    rootComponent->setView(view);
}

void ViewWindow::setView(SharedReference<UI::View>&& view)
{
    rootComponent->setView(std::move(view));
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
