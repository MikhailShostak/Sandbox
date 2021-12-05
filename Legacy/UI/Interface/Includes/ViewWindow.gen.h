#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"
#include "View.gen.h"

//CLASSGEN END REGION
#include <Graphics>

#include "Core/TemplateWindow.h"

#include "UI/UIPerspectiveCamera.h"
#include "UI/UIComponent.h"

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class ViewWindow : public Core::Window
//CLASSGEN END REGION
*/
class ViewWindow : public TemplateWindow<Component, PerspectiveCamera>
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ViewWindow This;
    typedef Core::Window Super;
    typedef void Interfaces;
protected:
    SharedReference<UI::View> View;
public:
    ViewWindow();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::View> getView() const;
    void setView(SharedReference<UI::View> const &View);
    void setView(SharedReference<UI::View> &&View);
//CLASSGEN END REGION
};
using Window = ViewWindow;

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
