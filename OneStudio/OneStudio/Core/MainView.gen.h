#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class MainView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef MainView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    MainView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::FlexBox> toolbar;
    SharedReference<UI::DockView> contentView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
