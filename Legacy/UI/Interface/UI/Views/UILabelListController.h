#pragma once

#include <Foundation>

#include "Includes/ListView.gen.h"
#include "Includes/TextField.gen.h"
#include "Includes/DefaultTextItemView.gen.h"

namespace UI
{

template<typename Item, typename Base = AObject>
class LabelListController : public ItemController<Item, Base>
{
public:
    using This = LabelListController<Item, Base>;
    using Super = ItemController<Item, Base>;
    using ItemType = Item;
    //using TemplateItemAdapter<Type>::data;

    virtual String getTitle(const AObject &sender, const ItemType &item) const = 0;

    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override
    {
        auto v = Create<DefaultTextItemView>();
        v->setText(getTitle(sender, This::data[index]));
        return SharedReference<View>(v);
    }
};

class StringListController : public LabelListController<String>
{
public:

    String getTitle(const AObject &sender, const ItemType &item) const override
    {
        return item;
    }

    ItemType createNewItem(const AObject &sender) const override
    {
        return "New Item";
    }
};

}
