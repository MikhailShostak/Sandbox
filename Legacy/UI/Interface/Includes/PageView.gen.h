#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class PageView : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PageView This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
protected:
    SizeInteger CurrentPage;
public:
    PageView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SizeInteger getCurrentPage() const;
    void setCurrentPage(SizeInteger const &CurrentPage);
    void setCurrentPage(SizeInteger &&CurrentPage);
//CLASSGEN END REGION
public:
    void setCurrentView(const UI::View &view);
    void onLoad(ALoadEvent &event) override;
    void UpdateContent();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
