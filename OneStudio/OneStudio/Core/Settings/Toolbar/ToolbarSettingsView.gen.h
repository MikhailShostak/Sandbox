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
class ToolbarSettingsView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ToolbarSettingsView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    ToolbarSettingsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::ListView> currentItems;
    SharedReference<UI::TextButton> addButton;
    SharedReference<UI::ListView> availableItems;
    SharedReference<UI::TextButton> saveButton;
    SharedReference<UI::TextButton> cancelButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
void onLoad(ALoadEvent &event) override;
UI::SizeType getCountItems(const AObject &sender) const override;
SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
