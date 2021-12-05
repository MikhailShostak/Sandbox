#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ListView.gen.h"

//CLASSGEN END REGION

#include "Includes/ListView.gen.h"//TODO:temp include
#include "UI/Views/UIGroupProxy.h"//TODO:temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

/*
//CLASSGEN GENERATED REGION: ClassHeader
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GroupView This;
    typedef UI::ListView Super;
    typedef void Interfaces;
public:
    GroupView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};
*/


class GroupView : public ListView
{
    GroupProxy proxy;
public:
    typedef GroupView This;
    typedef UI::ListView Super;
    typedef void Interfaces;

    ADelegate<SizeInteger()> CountGroups;
    ADelegate<SharedReference<UI::View>(SizeInteger groupIndex)> Group;

    ADelegate<SizeInteger(SizeInteger groupIndex)> CountGroupItems;
    ADelegate<SharedReference<UI::View>(SizeInteger groupIndex, SizeInteger index)> GroupItem;

    virtual SizeType getCountGroups(const AObject &sender) const { return 0; }
    virtual SizeType getCountItems(const AObject &sender, SizeType groupIndex) const { return 0; }
    virtual SharedReference<View> provideViewForGroup(const AObject &sender, SizeType groupIndex) { return nullptr; }
    virtual SharedReference<View> provideViewForItem(const AObject &sender, SizeType groupIndex, SizeType itemIndex) { return nullptr; }

    GroupView():proxy(*this, GroupProxy::TempProxyBindings{ CountGroups, Group, CountGroupItems, GroupItem })
    {
        CountItems.set(this, &This::temp_count_items);
        Item.set(this, &This::temp_items);
    }

    SizeInteger temp_count_items()
    {
        return proxy.getCountItems(*this);
    }

    SharedReference<View> temp_items(SizeInteger index)
    {
        return proxy.provideViewForItem(*this, index);
    }

    GroupAdapter *getProxyAdapter() const { return proxy.getAdapter(); }
    void setProxyAdapter(GroupAdapter *adapter)
    {
        proxy.setAdapter(adapter);
        setAdapter(adapter ? &proxy : nullptr);
    }

    size_t getGroupIndexForItemView(const View &view) const
    {
        size_t index = getIndexForItemView(view);
        if (index == InvalidIndex)
        {
            return InvalidIndex;
        }
        return proxy.paths[index].groupIndex;
    }

    size_t getGroupItemIndexForItemView(const View &view) const
    {
        size_t index = getIndexForItemView(view);
        if (index == InvalidIndex)
        {
            return InvalidIndex;
        }
        return proxy.paths[index].itemIndex;
    }

    void notifyUpdateAllItems()
    {
        proxy.reloadCachedPaths();
        ListView::notifyUpdateAllItems();
    }

    void notifyInsertItemsInGroup(SizeType groupIndex, SizeType itemIndex, SizeType size = 1)
    {
        SizeType absoluteIndex = proxy.findAbsoluteIndex(groupIndex, itemIndex);
        for (SizeType i = 0; i < size; ++i)
        {
            proxy.paths.insert(proxy.paths.begin() + absoluteIndex + i, { groupIndex, itemIndex + i });
        }
        for (SizeType i = absoluteIndex + size; i < proxy.paths.size(); ++i)
        {
            if (proxy.paths[i].groupIndex != groupIndex)
            {
                break;
            }

            proxy.paths[i].itemIndex += size;
        }
        proxy.groupSizes[groupIndex] += size;
        notifyInsertItems(absoluteIndex, size);
    }

    void notifyUpdateItemsInGroup(SizeType groupIndex, SizeType itemIndex, SizeType size = 1)
    {
        SizeType absoluteIndex = proxy.findAbsoluteIndex(groupIndex, itemIndex);
        notifyUpdateItems(absoluteIndex, size);
    }

    void notifyRemoveItemsInGroup(SizeType groupIndex, SizeType itemIndex, SizeType size = 1)
    {
        SizeType absoluteIndex = proxy.findAbsoluteIndex(groupIndex, itemIndex);
        for (SizeType i = 0; i < size; ++i)
        {
            proxy.paths.erase(proxy.paths.begin() + absoluteIndex);
        }
        for (SizeType i = absoluteIndex; i < proxy.paths.size(); ++i)
        {
            if (proxy.paths[i].groupIndex != groupIndex)
            {
                break;
            }

            proxy.paths[i].itemIndex -= size;
        }
        proxy.groupSizes[groupIndex] -= size;
        notifyRemoveItems(absoluteIndex, size);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
