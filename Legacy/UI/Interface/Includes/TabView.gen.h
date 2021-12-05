#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "FlexBox.gen.h"
#include "Foundation"

#include "Foundation"
#include "ListView.gen.h"
#include "PageView.gen.h"

//CLASSGEN END REGION
#include "Includes/ListView.gen.h"//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TabView : public UI::FlexBox, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TabView This;
    typedef UI::FlexBox Super;
    typedef std::tuple<UI::ItemAdapter> Interfaces;
protected:
    Array<Text> Tabs;
public:
    TabView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<Text> getTabs() const;
    void setTabs(Array<Text> const &Tabs);
    void setTabs(Array<Text> &&Tabs);
    SharedReference<UI::ListView> tabs;
    SharedReference<UI::PageView> pages;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void UpdateTabs();
    void onLoad(ALoadEvent &event);
    SizeType getCountItems(const AObject &sender) const override;
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override;
    void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
