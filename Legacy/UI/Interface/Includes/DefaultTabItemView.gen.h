#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "DefaultTextItemView.gen.h"

#include "Foundation"
#include "Button.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DefaultTabItemView : public UI::DefaultTextItemView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DefaultTabItemView This;
    typedef UI::DefaultTextItemView Super;
    typedef void Interfaces;
public:
    DefaultTabItemView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::Button> closeButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
