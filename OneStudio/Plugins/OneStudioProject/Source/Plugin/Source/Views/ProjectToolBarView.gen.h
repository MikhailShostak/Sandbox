#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ProjectToolBarView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ProjectToolBarView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    ProjectToolBarView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::DropDownList> projectList;
    SharedReference<UI::DropDownList> targetList;
    SharedReference<UI::DropDownList> configurationList;
    void onHierarchyCreate();
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
