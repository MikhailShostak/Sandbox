#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ScrollView.gen.h"

//CLASSGEN END REGION
#include "UI/Views/UIDataView.h"//TODO:temp include
#include "Includes/ScrollView.gen.h"//TODO:temp include
#include "UI/GestureRecognizers/UINewGestureRecognizers.h"//TODO:temp include
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
    typedef ItemView This;
    typedef UI::ScrollView Super;
    typedef void Interfaces;
public:
    ItemView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};
*/

using SizeType = Array<SharedReference<View>>::size_type;
constexpr static SizeType InvalidIndex = SizeType(-1);

class ItemAdapter
{
public:
    virtual SizeType getCountItems(const AObject &sender) const { return 0; }
    virtual SharedReference<View> provideViewForItem(const AObject &sender, SizeType index) { return nullptr; }

    virtual bool canAddItem(const AObject &sender) const { return false; }
    virtual bool requestAddItem(const AObject &sender) { return false; }

    virtual bool canRemoveItem(const AObject &sender, SizeType index) const { return false; }
    virtual bool requestRemoveItem(const AObject &sender, SizeType index) { return false; }

    virtual bool shouldAddTouchGestureRecognizerToItem(SizeType index) const { return true; }
    virtual bool shouldReceiveInputFromItem(SizeType index) const { return true; }
    virtual void onItemSelected(const AObject &sender, TapGestureEvent &event, SizeType index) {}
    virtual void onItemTapped(const AObject &sender, TapGestureEvent &event, SizeType index) {}

    virtual bool canBeReoredered() const { return false; }
    virtual void onItemReoredered(SizeType oldIndex, SizeType newIndex) {}
};

class ItemDataObserver
{
public:
    virtual void notifyUpdateAllItems() = 0;

    virtual void notifyInsertItems(size_t index, size_t size = 1) = 0;
    virtual void notifyUpdateItems(size_t index, size_t size = 1) = 0;
    virtual void notifyRemoveItems(size_t index, size_t size = 1) = 0;
};

template<typename AdapterType>
class ItemView : public DataView<AdapterType, ScrollView>, public ItemDataObserver
{
public:
    using This = ItemView<AdapterType>;
    using Super = DataView<AdapterType, ScrollView>;
protected:

    Array<SharedReference<View>> items;
    SharedReference<ImageView> highlightingView = std::make_shared<ImageView>();
    SharedReference<ImageView> selectionView = std::make_shared<ImageView>();
    //SharedReference<ButtonGroup> buttons = new ButtonGroup();
    void *highlightedView = nullptr;
    bool highlighting = false;
    size_t currentIndex = -1;
    SharedReference<SignleSelection> selectionRecognizer;
    SharedReference<Highlighting> highlightingRecognizer;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        if (!highlightingView->getParent())
        {
            highlightingView->setName("highlightingView");
            highlightingView->setSizePolicy(SizePolicy::Fixed);
            highlightingView->affectsParentLayout = false;
            highlightingView->setVisible(false);
            highlightingView->setImage(Legacy::Graphics::Texture::getWhiteTexture());
            highlightingView->setColor(AColor::fromHex(0x22222222));
            This::addView(highlightingView);
        }

        if (!selectionView->getParent())
        {
            selectionView->setName("selectionView");
            selectionView->setSizePolicy(SizePolicy::Fixed);
            selectionView->affectsParentLayout = false;
            selectionView->setVisible(false);
            selectionView->setImage(Legacy::Graphics::Texture::getWhiteTexture());
            selectionView->setColor(AColor::fromHex(0x44444444));
            This::addView(selectionView);
        }

        //contentView->setName("contentView");
        //addView(contentView);

        /*buttons->horizontalSizePolicy = SizePolicy::Fixed;
        buttons->verticalSizePolicy = SizePolicy::Fixed;*/

        auto checkItems = [this](const SharedReference<View> &view) {
            return ArrayUtils::FindFirst(items, view) != InvalidIndex;
        };

        if (!selectionRecognizer)
        {
            selectionRecognizer = SharedReference<SignleSelection>(Create<SignleSelection>());
            selectionRecognizer->setName(fmt::format("{} SignleSelection", This::getObjectDescription()));
            selectionRecognizer->predicate = checkItems;
            selectionRecognizer->selectionUpdated = [this](const SharedReference<View> &view, AWindowTouchDownEvent &event) {
                SizeType index = getIndexForItemView(view);
                if (index != InvalidIndex)
                {
                    selectionView->setVisible(true);
                    selectionView->setTransform(view->getTransform());
                    selectionView->setSize(view->getSize());

                    TapGestureEvent e(*this, event, *view, {});
                    onItemTapped(e, index);
                }
            };
            This::addGestureRecognizer(selectionRecognizer);
        }

        if (highlighting && !highlightingRecognizer)
        {
            highlightingRecognizer = SharedReference<Highlighting>(Create<Highlighting>());
            highlightingRecognizer->setName(fmt::format("{} Highlighting", This::getObjectDescription()));
            highlightingRecognizer->predicate = checkItems;
            highlightingRecognizer->entered = [this](const SharedReference<View> &view) {
                highlightingView->setVisible(true);
                highlightingView->setTransform(view->getTransform());
                highlightingView->setSize(view->getSize());
                highlightedView = view.get();
            };
            highlightingRecognizer->exited = [this](const SharedReference<View> &view) {
                if (highlightedView == view.get())
                {
                    highlightingView->setVisible(false);
                }
            };
            This::addGestureRecognizer(highlightingRecognizer);
        }

        ApplyStyle(*this);

        notifyUpdateAllItems();
    }

public:

    ADelegate<SizeInteger()> CountItems;
    ADelegate<SharedReference<UI::View>(SizeInteger index)> Item;
    ADelegate<void(SizeInteger index)> OnItemSelected;
    ADelegate<void(TapGestureEvent &event, SizeInteger index)> OnItemTapped;

    Map<String, ADelegate<void()>> additionalButtons;
    bool useAddButton = true;
    bool useRemoveButton = true;

    SizeType getCurrentIndex()
    {
        return currentIndex;
    }

    void setCurrentIndex(SizeType index)
    {
        currentIndex = index;
    }

    ~ItemView()
    {
        for (auto &item : items)
        {
            item->eventChannel.unregisterObserver(*this);
        }
    }

    void setAdapter(AdapterType *adapter) override
    {
        Super::setAdapter(adapter);

        notifyUpdateAllItems();

        /*Array<String> buttonNames;
        if (useAddButton)
        {
        buttonNames.append("+");
        }

        if (useRemoveButton)
        {
        buttonNames.append("-");
        }

        buttons->setButtons(buttonNames);
        if (useAddButton)
        {
        buttons->getButtons()[0]->eventChannel.registerDelegate<TapGestureEvent>([this](TapGestureEvent &event) {
        if (getAdapter() && getAdapter()->canAddItem(*this))
        {
        if (getAdapter()->requestAddItem(*this))
        {
        insertViewAtIndex(items.size());
        }
        }
        });
        }

        if (useRemoveButton)
        {
        buttons->getButtons()[useAddButton ? 1 : 0]->eventChannel.registerDelegate<TapGestureEvent>([this](TapGestureEvent &event) {
        if (getAdapter() && getAdapter()->canRemoveItem(*this, 0))
        {
        if (getAdapter()->requestRemoveItem(*this, 0))
        {
        removeViewAtIndex(0);
        }
        }
        });
        }*/
    }

    /*SharedReference<Legacy::Graphics::Texture> const &getImage() const
    {
    return contentView->getImage();
    }

    void setImage(SharedReference<Legacy::Graphics::Texture> const &image)
    {
    contentView->setImage(image);
    }

    void setImage(SharedReference<Legacy::Graphics::Texture> &&image)
    {
    contentView->setImage(std::move(image));
    }

    UIOffsets getBorder() const
    {
    return contentView->getBorder();
    }

    void setBorder(UIOffsets border)
    {
    contentView->setBorder(border);
    }*/

    SizeType getIndexForItemView(const View &view) const
    {
        for (SizeType i = 0; i < items.size(); ++i)
        {
            if (items[i].get() == &view)
            {
                return i;
            }
        }
        return InvalidIndex;
    }
    size_t getIndexForItemView(const SharedReference<View> &view) const { return ArrayUtils::FindFirst(items, view); }
    SharedReference<View> getItemViewAt(SizeType index) const { return items[index]; }
    const Array<SharedReference<View>> &getItemViews() const { return items; }

    void notifyUpdateAllItems() override
    {
        clearItems();

        if (!CountItems && !This::getAdapter())
        {
            return;
        }

        notifyInsertItems(0, CountItems ? CountItems() : This::getAdapter()->getCountItems(*this));
    }

    void notifyInsertItems(SizeType index, SizeType size = 1) override
    {
        const SizeType end = index + size;
        for (; index < end; ++index)
        {
            loadViewAtIndex(index);
        }
    }

    void notifyUpdateItems(SizeType index, SizeType size = 1) override
    {
        const SizeType end = index + size;
        for (; index < end; ++index)
        {
            removeViewAtIndex(index);
            loadViewAtIndex(index);
        }
    }

    void notifyRemoveItems(SizeType index, SizeType size = 1) override
    {
        for (SizeType i = 0; i < size; ++i)
        {
            removeViewAtIndex(index);
        }
    }

protected:

    void loadViewAtIndex(SizeType index)
    {
        auto view = Item ? SharedReference<UI::View>(Item(index)) : This::getAdapter()->provideViewForItem(*this, index);
        AAssert(view, "View should not be null");
        insertViewAtIndex(index, view);
    }

    virtual void insertViewAtIndex(SizeType index, const SharedReference<View> &view)
    {
        view->setName(fmt::format("Item {}", index));
        items.insert(items.begin() + index, view);
        This::contentView->insertView(index, view);
    }

    virtual void removeViewAtIndex(SizeType index)
    {
        items[index]->eventChannel.unregisterObserver(*this);
        This::contentView->removeView(items[index]);
        items.erase(items.begin() + index);
    }

    virtual void clearItems()
    {
        for (auto &item : items)
        {
            item->eventChannel.unregisterObserver(*this);
        }
        This::contentView->removeAllViews();
        items.clear();
    }

    virtual void onItemTapped(TapGestureEvent &event, SizeType index)
    {
        if (OnItemSelected)
        {
            OnItemSelected(index);
        }
        else if (This::getAdapter())
        {
            This::getAdapter()->onItemSelected(*this, event, index);
        }

        if (OnItemTapped)
        {
            OnItemTapped(event, index);
        }
        else if (This::getAdapter())
        {
            This::getAdapter()->onItemTapped(*this, event, index);
        }
    }
};

template<typename Item, typename Base = AObject>
class ItemController : public Base, public ItemAdapter
{
public:

    using ItemType = Item;

    Array<ItemType> data;

    virtual ItemType createNewItem(const AObject &sender) const = 0;

    Array<SharedReference<View>>::size_type getCountItems(const AObject &sender) const override
    {
        return data.size();
    }

    bool canAddItem(const AObject &sender) const override
    {
        return true;
    }

    bool requestAddItem(const AObject &sender) override
    {
        data.push_back(createNewItem(sender));
        return true;
    }

    bool canRemoveItem(const AObject &sender, Array<SharedReference<View>>::size_type index) const override
    {
        return data.size() > 0;
    }

    bool requestRemoveItem(const AObject &sender, Array<SharedReference<View>>::size_type index) override
    {
        ArrayUtils::Remove(data, index);
        return true;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
