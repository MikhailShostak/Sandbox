//CLASSGEN GENERATED REGION: Includes
#include "TabView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ListView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "ContentFit.gen.h"
#include "ScrollBarVisibility.gen.h"
#include "Direction.gen.h"
#include "PageView.gen.h"

//CLASSGEN END REGION
#include "DefaultTextItemView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TabView::TabView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_131_0;
    item_131_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_133_1;
    item_133_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_131_0,item_133_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(0.000000);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TabView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Tabs", toJSONValue(Tabs));
}
void TabView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Tabs", value);
    fromJSONValue(value, Tabs);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<Text> TabView::getTabs() const
{
    return this->Tabs;
}
void TabView::setTabs(Array<Text> const &Tabs)
{
    this->Tabs = Tabs;
    UpdateTabs();
}
void TabView::setTabs(Array<Text> &&Tabs)
{
    this->Tabs = std::move(Tabs);
    UpdateTabs();
}
void TabView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TabView");
    tabs = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*tabs).setName("Tabs");
    {
    }
    (*tabs).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*tabs).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*tabs).setDirection(UI::Direction::Horizontal);
    (*this).addView(tabs);
    pages = CreateShared<UI::PageView>([this](UI::PageView *v)
    {
    }
);
    (*pages).setName("Pages");
    {
    }
    (*pages).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*pages).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*pages).setCurrentPage(0.000000);
    (*this).addView(pages);
}
//CLASSGEN END REGION

void TabView::UpdateTabs()
{

}

void TabView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    if (!tabs->getAdapter())
    {
        tabs->setAdapter(this);
    }
    { //DIRTY HACK: page's views should placed directly into pages view. 
        Array<SharedReference<View>> views;
        for (auto &view : getViews())
        {
            if (view.get() == tabs.get() || view.get() == pages.get())
            {
                continue;
            }
            views.push_back(view);
        }
        for (auto &view : views)
        {
            pages->addView(view);
        }
        Array<UI::OverlayData> layoutData;
        layoutData.resize(views.size());
        for (auto &l : layoutData)
        {
            l.HorizontalAlignment = Core::Alignment::Center;
            l.VerticalAlignment = Core::Alignment::Center;
        }
        pages->setData(layoutData);
        if (!views.empty())
        {
            pages->setCurrentPage(pages->getCurrentPage());
        }
    }
}

SizeType TabView::getCountItems(const AObject &sender) const
{
    return Tabs.size();
}

SharedReference<View> TabView::provideViewForItem(const AObject &sender, SizeType index)
{
    auto v = CreateShared<UI::DefaultTextItemView>();
    v->setText(Tabs[index]);
    return v;
}

void TabView::onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index)
{
    pages->setCurrentPage(index);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
