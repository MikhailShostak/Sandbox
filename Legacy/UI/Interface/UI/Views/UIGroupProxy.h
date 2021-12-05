#pragma once

#include "Includes/ItemView.gen.h"
#include "UIGroupAdapter.h"

namespace UI
{

class GroupProxy : public ItemAdapter
{
    const AObject &sender;
    GroupAdapter *adapter = nullptr;
    struct ItemPath
    {
        SizeType groupIndex;
        SizeType itemIndex;
    };
public:

    struct TempProxyBindings
    {
        const ADelegate<SizeInteger()> &CountGroups;
        const ADelegate<SharedReference<UI::View>(SizeInteger groupIndex)> &Group;

        const ADelegate<SizeInteger(SizeInteger groupIndex)> &CountGroupItems;
        const ADelegate<SharedReference<UI::View>(SizeInteger groupIndex, SizeInteger index)> &GroupItem;
    } bindings;

    Array<ItemPath> paths;
    Array<SizeType> groupSizes;

    GroupProxy(const AObject &sender, TempProxyBindings bindings):sender(sender), bindings(bindings){}

    SizeType findAbsoluteIndex(SizeType groupIndex, SizeType itemIndex) const
    {
        SizeType absoluteIndex = 0;
        for (SizeType i = 0; i < groupIndex; ++i)
        {
            absoluteIndex += groupSizes[i];
        }
        return absoluteIndex + itemIndex + 1;
    }

    SizeType getCountItems(const AObject &sender) const override { return paths.size(); }
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override
    {
        ItemPath path = paths[index];
        if (bindings.GroupItem)
        {
            return path.itemIndex == InvalidIndex ? bindings.Group(path.groupIndex) : bindings.GroupItem(path.groupIndex, path.itemIndex);
        }

        return path.itemIndex == InvalidIndex ? adapter->provideViewForGroup(sender, path.groupIndex) : adapter->provideViewForItem(sender, path.groupIndex, path.itemIndex);
    }

    bool canAddItem(const AObject &sender) const override { return false; }
    bool requestAddItem(const AObject &sender) override { return false; }

    bool canRemoveItem(const AObject &sender, SizeType index) const override { return false; }
    bool requestRemoveItem(const AObject &sender, SizeType index) override { return false; }

    bool shouldAddTouchGestureRecognizerToItem(SizeType index) const override
    {
        ItemPath path = paths[index];
        return adapter->shouldAddTouchGestureRecognizerToItem(path.groupIndex, path.itemIndex);
    }

    bool shouldReceiveInputFromItem(SizeType index) const override
    {
        ItemPath path = paths[index];
        return adapter->shouldReceiveInputFromItem(path.groupIndex, path.itemIndex);
    }

    void onItemSelected(const AObject &sender, TapGestureEvent &event, SizeType index) override
    {
        ItemPath path = paths[index];
        adapter->onItemSelected(sender, event, path.groupIndex, path.itemIndex);
    }

    void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index) override
    {
        ItemPath path = paths[index];
        adapter->onItemTapped(sender, event, path.groupIndex, path.itemIndex);
    }

    GroupAdapter *getAdapter() const { return this->adapter; }
    void setAdapter(GroupAdapter *adapter)
    {
        this->adapter = adapter;
        reloadCachedPaths();
    }

    void reloadCachedPaths()
    {
        groupSizes.clear();
        paths.clear();
        if (bindings.CountGroups || this->adapter)
        {
            SizeType n = bindings.CountGroups ? bindings.CountGroups() : this->adapter->getCountGroups(sender);
            groupSizes.reserve(n);
            for (SizeType i = 0; i < n; ++i)
            {
                //TODO: reserve paths
                paths.push_back({ i, InvalidIndex });
                SizeType m = bindings.CountGroupItems ? bindings.CountGroupItems(i) : this->adapter->getCountItems(sender, i);
                for (SizeType j = 0; j < m; ++j)
                {
                    paths.push_back({ i, j });
                }
                groupSizes.push_back(m + 1); // items + group header
            }
        }
    }
};

}
