#pragma once

#include <Foundation>

namespace UI
{

class GroupAdapter
{
public:
    virtual ~GroupAdapter() {}
    virtual SizeType getCountGroups(const AObject &sender) const { return 0; }
    virtual SizeType getCountItems(const AObject &sender, SizeType groupIndex) const { return 0; }
    virtual SharedReference<View> provideViewForGroup(const AObject &sender, SizeType groupIndex) { return nullptr; }
    virtual SharedReference<View> provideViewForItem(const AObject &sender, SizeType groupIndex, SizeType itemIndex) { return nullptr; }

    virtual bool shouldAddTouchGestureRecognizerToItem(SizeType groupIndex, SizeType itemIndex) const { return true; }
    virtual bool shouldReceiveInputFromItem(SizeType groupIndex, SizeType itemIndex) const { return true; }
    virtual void onItemSelected(const AObject &sender, TapGestureEvent &event, SizeType groupIndex, SizeType itemIndex) {}
    virtual void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType groupIndex, SizeType itemIndex) {}
};

}
