#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ItemView.gen.h"

//CLASSGEN END REGION
#include "Includes/SplitView.gen.h"
#include "Includes/ItemView.gen.h"//TODO:temp include

#include "UI/GestureRecognizers/UIItemReorderingGestureRecognizer.h"//TODO:temp include

#include "Includes/ViewWindow.gen.h"//TODO:temp include
#include "Includes/FlexBox.gen.h"//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TableView : public UI::ItemView<UI::ItemAdapter>
//CLASSGEN END REGION
{
/*
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TableView This;
    typedef UI::ItemView<UI::ItemAdapter> Super;
    typedef void Interfaces;
public:
    TableView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
*/
public:
    typedef TableView This;
    typedef UI::ItemView<UI::ItemAdapter> Super;
    typedef void Interfaces;
public:
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT

    void onHierarchyCreate();

    ADelegate<SizeInteger()> CountColumns;
    ADelegate<SizeInteger()> CountRows;
    ADelegate<SharedReference<View>(SizeInteger Row, SizeInteger Column)> TableItem;
    ADelegate<void(SizeInteger Row, SizeInteger Column)> OnTableItemSelected;
    ADelegate<void(TapGestureEvent &Event, SizeInteger Row, SizeInteger Column)> OnTableItemTapped;

    TableView()
    {
        CountItems.set(this, &This::temp_count_items);
        Item.set(this, &This::temp_items);
        OnItemSelected.set(this, &This::temp_on_selected);
        OnItemTapped.set(this, &This::temp_on_tapped);
    }

    SizeInteger temp_count_items()
    {
        return CountColumns() * CountRows();
    }

    SharedReference<View> temp_items(SizeInteger index)
    {
        SizeInteger c = CountColumns();
        return TableItem(index / c, index % c);
    }

    void temp_on_selected(SizeInteger index)
    {
        if (OnTableItemSelected)
        {
            SizeInteger c = CountColumns();
            OnTableItemSelected(index / c, index % c);
        }
    }

    void temp_on_tapped(TapGestureEvent &event, SizeInteger index)
    {
        if (OnTableItemTapped)
        {
            SizeInteger c = CountColumns();
            OnTableItemTapped(event, index / c, index % c);
        }
    }

    Math::IntegerVector getContentSize() const override
    {
        return contentView->getContentSize();
    }

    Direction getDirection() const
    {
        return StaticCast<SplitView>(contentView)->getDirection();
    }

    void setDirection(Direction direction) const
    {
        return StaticCast<SplitView>(contentView)->setDirection(direction);
    }

    //TODO:remove
    void onLayout(AUpdateEvent &event)
    {
        auto s = [&](size_t i, View &v) {
            switch (v.getSizePolicyAt(i))
            {
            case SizePolicy::Expanded:
                return getSize()[i];
            case SizePolicy::Fixed:
                return v.getSize()[i];
            }
            return v.getContentSize()[i];
        };
        contentView->setSize(Math::IntegerVector{ s(0, *contentView), s(1, *contentView) });

        Super::onLayout(event);
    }

    void insertViewAtIndex(SizeType index, const SharedReference<View> &view) override
    {
        Super::insertViewAtIndex(index, view);

        auto data = StaticCast<SplitView>(contentView)->getData();
        data.insert(data.begin() + index, {});
        StaticCast<SplitView>(contentView)->setData(data);
        StaticCast<SplitView>(contentView)->setPrimaryAxisLimit(CountColumns());
    }

    void removeViewAtIndex(SizeType index) override
    {
        auto data = StaticCast<SplitView>(contentView)->getData();
        data.erase(data.begin() + index, {});
        StaticCast<SplitView>(contentView)->setData(data);
        StaticCast<SplitView>(contentView)->setPrimaryAxisLimit(CountColumns());

        Super::removeViewAtIndex(index);
    }

    void clearItems() override
    {
        StaticCast<SplitView>(contentView)->setData({});
        contentView->removeAllViews();

        Super::clearItems();
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
