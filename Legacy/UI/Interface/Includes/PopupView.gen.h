#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"

#include "Foundation"
#include "BorderImageView.gen.h"
#include "View.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class PopupView : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PopupView This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
public:
    PopupView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::BorderImageView> background;
    SharedReference<UI::View> header;
    SharedReference<UI::View> content;
    SharedReference<UI::View> footer;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
