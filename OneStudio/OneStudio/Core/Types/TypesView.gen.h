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
class TypesView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TypesView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    TypesView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::ListView> typesList;
    SharedReference<UI::ListView> editorsList;
    void onHierarchyCreate();
//CLASSGEN END REGION
void onLoad(ALoadEvent &event) override;
UI::SizeType getCountItems(const AObject &sender) const override;
SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
