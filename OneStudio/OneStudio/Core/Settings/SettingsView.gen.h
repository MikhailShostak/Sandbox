#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class SettingsView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef SettingsView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    SettingsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
protected:
    void onLoad(ALoadEvent &event);
    UI::SizeType getCountItems(const AObject &sender) const override;
    SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType index) override;
    void onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
