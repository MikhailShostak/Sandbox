#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ListView.gen.h"

//CLASSGEN END REGION
#include "Includes/TextButton.gen.h"//TODO:temp include
#include "Includes/ListView.gen.h"//TODO:temp include
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
    typedef TreeView This;
    typedef UI::ListView Super;
    typedef void Interfaces;
public:
    TreeView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};
*/

template<typename TreeItemType>
class TreeAdapter
{
public:
    virtual SizeType getCountRootItems() const = 0;
    virtual TreeItemType *getRootItem(SizeType index) = 0;
    //virtual bool hasContent(TreeItemType *parentItem) const = 0;
    //virtual void loadContent(TreeItemType *parentItem) {}
    virtual SizeType getCountChildItems(TreeItemType *parentItem) const = 0;
    virtual TreeItemType *getChildItem(TreeItemType *parentItem, SizeType index) = 0;
    virtual SharedReference<View> provideViewForItem(const AObject &sender, SizeType depth, TreeItemType *item) = 0;

    virtual bool shouldAddTouchGestureRecognizerToItem(const TreeItemType *item) { return true; }
    virtual bool shouldReceiveInputFromItem(const TreeItemType *item) { return true; }
    virtual void onItemSelected(const AObject &sender, TapGestureEvent &event, TreeItemType *item) {}
    virtual void onItemTapped(const AObject &sender, TapGestureEvent &event, TreeItemType *item) {}
};

template<typename TreeItemType>
class TreeProxy : public ItemAdapter
{
    const AObject &sender;
    TreeAdapter<TreeItemType> *adapter = nullptr;
public:
    struct TreePath
    {
        SizeType depth;
        TreeItemType *parent = nullptr;
        TreeItemType *item = nullptr;
    };
    Array<TreePath> paths;

    struct TempBinding
    {
        ADelegate<SizeInteger()> &CountRootItems;
        ADelegate<PlainReference<TreeItemType>(SizeInteger index)> &RootItem;
        ADelegate<SizeInteger(PlainReference<TreeItemType> parentItem)> &CountChildItems;
        ADelegate<PlainReference<TreeItemType>(PlainReference<TreeItemType> parentItem, SizeInteger index)> &ChildItem;
        ADelegate<SharedReference<View>(SizeInteger depth, PlainReference<TreeItemType> item)> &TreeItem;
        ADelegate<void(PlainReference<TreeItemType> Item)> &OnItemSelected;
        ADelegate<void(TapGestureEvent &Event, PlainReference<TreeItemType> Item)> &OnItemTapped;
    } binding;

    TreeProxy(const AObject &sender, const TempBinding &binding):sender(sender), binding(binding)
    {

    }

    TreeProxy(const AObject &sender):sender(sender) {}

    TreeAdapter<TreeItemType> *getAdapter() const { return this->adapter; }
    void setAdapter(TreeAdapter<TreeItemType> *adapter)
    {
        this->adapter = adapter;
        reloadPaths();
    }

    void reloadPaths()
    {
        paths.clear();
        if (!binding.CountRootItems && ! adapter)
        {
            return;
        }
        auto size = binding.CountRootItems ? binding.CountRootItems() : adapter->getCountRootItems();
        for (size_t i = 0; i < size; ++i)
        {
            TreeItemType *item = binding.RootItem ? binding.RootItem(i) : adapter->getRootItem(i);
            paths.push_back(TreePath{ 0, nullptr, item });
            addChildren(1, item);
        }
    }

    void addChildren(SizeType depth, TreeItemType *item)
    {
        auto size = binding.CountChildItems ? binding.CountChildItems(item) : adapter->getCountChildItems(item);
        for (SizeType i = 0; i < size; ++i)
        {
            TreeItemType *child = binding.ChildItem ? binding.ChildItem(item, i) : adapter->getChildItem(item, i);
            paths.push_back(TreePath{ depth, item, child });
            addChildren(depth + 1, child);
        }
    }

    size_t insertChildren(SizeType index, SizeType depth, TreeItemType *item)
    {
        auto size = binding.CountChildItems ? binding.CountChildItems(item) : adapter->getCountChildItems(item);
        size_t insertedItems = 0;
        for (SizeType i = 0; i < size; ++i)
        {
            TreeItemType *child = binding.ChildItem ? binding.ChildItem(item, i) : adapter->getChildItem(item, i);
            paths.insert(paths.begin() + index + insertedItems + i, TreePath{ depth, item, child });
            insertedItems += insertChildren(index + i + 1, depth + 1, child);
        }

        return size + insertedItems;
    }


    APair<SizeType, SizeType> removeChildren(TreeItemType *parentItem)
    {
        APair<SizeType, SizeType> result{ InvalidIndex, 0 };

        //Search of parent item
        auto parentIt = ranges::find_if(paths, [&](auto &itemPath) {
            return itemPath.item == parentItem;
        });

        if (parentIt == paths.end())
        {
            //No parent in the view
            return result;
        }

        //Check the next item. If it's child, it should be deeper.
        auto firstChild = parentIt + 1;
        if (firstChild == paths.end() || firstChild->depth <= parentIt->depth)
        {
            //No children in the view
            return result;
        }

        //Find the first element which is not inside parent item
        auto endIt = std::find_if(firstChild, paths.end(), [&](auto &itemPath) {
            return itemPath.depth < firstChild->depth;
        });

        result.first = std::distance(paths.begin(), firstChild);
        result.second = std::distance(firstChild, endIt);
        paths.erase(firstChild, endIt);
        return result;
    }

    APair<SizeType, SizeType> addChildren(TreeItemType *parentItem)
    {
        APair<SizeType, SizeType> result{ InvalidIndex, 0 };
        for (SizeType i = 0; i < paths.size(); ++i)
        {
            if (parentItem == paths[i].item)
            {
                result.first = i + 1;
                result.second = insertChildren(result.first, paths[i].depth + 1, parentItem);
                break;
            }
        }
        return result;
    }

    SizeType getCountItems(const AObject &sender) const override { return paths.size(); }
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) override { return binding.TreeItem ? binding.TreeItem(paths[index].depth, paths[index].item) : adapter->provideViewForItem(sender, paths[index].depth, paths[index].item); }

    bool shouldAddTouchGestureRecognizerToItem(SizeType index) const override { return adapter->shouldAddTouchGestureRecognizerToItem(paths[index].item); }
    bool shouldReceiveInputFromItem(SizeType index) const override { return adapter->shouldReceiveInputFromItem(paths[index].item); }
    void onItemSelected(const AObject &sender, TapGestureEvent &event, SizeType index) override
    {
        if (binding.OnItemSelected)
        {
            binding.OnItemSelected(paths[index].item);
        }
        else if(adapter)
        {
            adapter->onItemSelected(sender, event, paths[index].item);
        }
    }

    void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index) override
    {
        if (binding.OnItemTapped)
        {
            binding.OnItemTapped(event, paths[index].item);
        }
        else if (adapter)
        {
            adapter->onItemTapped(sender, event, paths[index].item);
        }
    }
};

template<typename TreeItemType>
class TreeView : public ListView
{
    TreeProxy<TreeItemType> proxy;
public:
    using This = TreeView<TreeItemType>;
    using Super = ListView;

    ADelegate<SizeInteger()> CountRootItems;
    ADelegate<PlainReference<TreeItemType>(SizeInteger index)> RootItem;
    ADelegate<SizeInteger(PlainReference<TreeItemType> parentItem)> CountChildItems;
    ADelegate<PlainReference<TreeItemType>(PlainReference<TreeItemType> parentItem, SizeInteger index)> ChildItem;
    ADelegate<SharedReference<View>(SizeInteger depth, PlainReference<TreeItemType> item)> TreeItem;
    ADelegate<void(PlainReference<TreeItemType> Item)> OnTreeItemSelected;
    ADelegate<void(TapGestureEvent &Event, PlainReference<TreeItemType> Item)> OnTreeItemTapped;

    TreeView():proxy(*this, { CountRootItems, RootItem, CountChildItems, ChildItem, TreeItem, OnTreeItemSelected, OnTreeItemTapped })
    {
        CountItems.set(this, &This::temp_count_items);
        Item.set(this, &This::temp_items);
        OnItemSelected.set(this, &This::temp_on_selected);
        OnItemTapped.set(this, &This::temp_on_tapped);
    }

    SizeInteger temp_count_items()
    {
        return proxy.getCountItems(*this);
    }

    SharedReference<View> temp_items(SizeInteger index)
    {
        return proxy.provideViewForItem(*this, index);
    }

    void temp_on_selected(SizeInteger index)
    {
        Math::IntegerVector p;
        AWindowTouchEvent e1(*this, ATouchID::Touch0, ATouchModifier::Undefined, p);
        TapGestureEvent e2(*this, e1, *this, p);
        return proxy.onItemSelected(*this, e2, index);
    }

    void temp_on_tapped(TapGestureEvent &event, SizeInteger index)
    {
        return proxy.onItemTapped(*this, event, index);
    }


    TreeAdapter<TreeItemType> *getProxyAdapter() const { return proxy.getAdapter(); }
    void setProxyAdapter(TreeAdapter<TreeItemType> *adapter)
    {
        proxy.setAdapter(adapter);
        setAdapter(adapter ? &proxy : nullptr);
    }

    void notifyUpdateAllItems() override
    {
        proxy.reloadPaths();
        Super::notifyUpdateAllItems();
    }

    void notifyUpdateChildren(TreeItemType *parentItem)
    {
        {
            auto pair = proxy.removeChildren(parentItem);
            if (pair.first != InvalidIndex)
            {
                notifyRemoveItems(pair.first, pair.second);
            }
        }

        {
            auto pair = proxy.addChildren(parentItem);
            notifyInsertItems(pair.first, pair.second);
        }
    }
};

class DefaultTreeItemView : public Overlay
{
    bool expandable = false;
public:

    SharedReference<TextButton> expandButton = SharedReference<TextButton>(Create<TextButton>());
    SharedReference<Label> title = SharedReference<Label>(Create<Label>());

    DefaultTreeItemView(SizeType depth, const String &text, bool expandable)
    {
        setSizePolicy(SizePolicy::Expanded, SizePolicy::Fixed);
        setSize(Math::IntegerVector{ 0, 20 });

        expandButton->setSizePolicy(SizePolicy::Fixed);
        expandButton->setSize(Math::IntegerVector{ 12, 12 });
        expandButton->setText("+");
        Data.push_back(OverlayData{ UIOffsets{ 0, 0, 0, static_cast<int32_t>(depth) * 20 + 4 }, Core::Alignment::Start, Core::Alignment::Center });
        addView(expandButton);
        setExpandable(expandable);

        title->setText(text);
        title->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
        Data.push_back(OverlayData{ UIOffsets{ 0, 0, 0, static_cast<int32_t>(depth) * 20 + 20 }, Core::Alignment::Start, Core::Alignment::Center });
        addView(title);
    }

    bool getExpandable() const
    {
        return expandable;
    }

    void setExpandable(bool expandable)
    {
        this->expandable = expandable;
        expandButton->setVisible(expandable);
    }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
