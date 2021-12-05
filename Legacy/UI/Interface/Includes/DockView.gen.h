#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "SplitView.gen.h"
#include "Foundation"
#include "DockViewArea.gen.h"

#include "Foundation"

//CLASSGEN END REGION
#include "TabItem.gen.h"
#include "TabView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DockView : public UI::SplitView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DockView This;
    typedef UI::SplitView Super;
    typedef void Interfaces;
protected:
    Array<UI::DockViewArea> Areas;
public:
    DockView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<UI::DockViewArea> getAreas() const;
    void setAreas(Array<UI::DockViewArea> const &Areas);
    void setAreas(Array<UI::DockViewArea> &&Areas);
    void onHierarchyCreate();
//CLASSGEN END REGION
    void UpdateAreas();
    
    class InternalNode : public Overlay
    {
    public:

        class SharedTab : public TabItem
        {
        public:
            InternalNode *parentNode = nullptr;
        };

        class InternalTabView : public TabView
        {
        public:
            Array<SharedReference<SharedTab>> tabViews;
            SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override { return tabViews[index]; }
        };

        DockView *owner = nullptr;
        SharedReference<InternalTabView> tabView = SharedReference<InternalTabView>(Create<InternalTabView>());
        SharedReference<BorderImageView> area = SharedReference<BorderImageView>(Create<BorderImageView>());

        InternalNode()
        {
            tabView->setSizePolicy(SizePolicy::Expanded);
            addView(tabView);

            area->setImage(Legacy::Graphics::Texture::getWhiteTexture());
            area->setColor(AColor::fromHex(0x22888888));
            area->setSizePolicy(SizePolicy::Expanded);
            area->setVisibility(Visibility::Collapsed);
            addView(area);

            setData({ {}, {} });
        }

        SharedReference<DockView::InternalNode::SharedTab> createSharedTab(const DockViewTab &data);
    };

    ADelegate<SharedReference<InternalNode::SharedTab>(const DockViewTab &tabData)> SharedTabAllocator;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
