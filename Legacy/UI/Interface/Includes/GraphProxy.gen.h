#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "GraphAdapter.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GraphProxy : public Serializable, public UI::ItemAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GraphProxy This;
    typedef Serializable Super;
    typedef std::tuple<UI::ItemAdapter> Interfaces;
public:
    GraphProxy();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    AObject *sender = nullptr;
    GraphAdapter *adapter = nullptr;
public:

    GraphProxy(AObject &sender):sender(&sender) {}

    SizeType getConnectionIndex(SizeType itemIndex) const
    {
        return itemIndex;
    }

    SizeType getNodeIndex(SizeType itemIndex) const
    {
        return itemIndex - adapter->getCountConnections(*sender);
    }

    SizeType getItemIndexFromConnectionIndex(SizeType connectionIndex) const
    {
        return connectionIndex;
    }

    SizeType getItemIndexFromNodeIndex(SizeType nodeIndex) const
    {
        return nodeIndex + adapter->getCountConnections(*sender);
    }

    SizeType getCountItems(const AObject &sender) const override { return adapter->getCountConnections(sender) + adapter->getCountNodes(sender); }
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override
    {
        size_t connectionsCount = adapter->getCountConnections(sender);
        if (index < connectionsCount)
        {
            return adapter->provideViewForConnection(sender, index);
        }

        return adapter->provideViewForNode(sender, index - connectionsCount);
    }

    bool canAddItem(const AObject &sender) const override { return false; }
    bool requestAddItem(const AObject &sender) override { return false; }

    bool canRemoveItem(const AObject &sender, SizeType index) const override { return false; }
    bool requestRemoveItem(const AObject &sender, SizeType index) override { return false; }

    /*bool shouldAddTouchGestureRecognizerToItem(SizeType index) const override
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
    }*/

    GraphAdapter *getAdapter() const { return this->adapter; }
    void setAdapter(GraphAdapter *adapter)
    {
        this->adapter = adapter;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
