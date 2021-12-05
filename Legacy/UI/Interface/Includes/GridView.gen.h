#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Panel.gen.h"

#include "Foundation"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GridView : public UI::Panel
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GridView This;
    typedef UI::Panel Super;
    typedef void Interfaces;
public:
    GridView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    //SharedReference<ScrollView> contentView;
    //SharedReference<BorderImageView> innerShadow = new BorderImageView();
public:

    bool snapToGrid = true;
    bool gridVisibility = true;
    bool checkVisibility = true;

    void onLoad(ALoadEvent &event);
    void updateGrid();
    void updateScroll();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
