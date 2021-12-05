#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ItemView.gen.h"
#include "Direction.gen.h"

//CLASSGEN END REGION
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

/*
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ListView This;
    typedef UI::ItemView<UI::ItemAdapter> Super;
    typedef std::tuple<ReorderingAdapter> Interfaces;
protected:
    UI::Direction Direction;
public:
    ListView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    UI::Direction getDirection() const;
    void setDirection(UI::Direction const &Direction);
    void setDirection(UI::Direction &&Direction);
//CLASSGEN END REGION
};
*/

//CLASSGEN GENERATED REGION: ClassHeader
class ListView : public UI::ItemView<UI::ItemAdapter>, public ReorderingAdapter
//CLASSGEN END REGION
{
CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef ListView This;
    typedef UI::ItemView<UI::ItemAdapter> Super;
    typedef std::tuple<ReorderingAdapter> Interfaces;
private:
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
CLASSGEN_END_REGION

    void onHierarchyCreate();

    struct ReorderingManager : public ASingleton<ReorderingManager>
    {
        SharedReference<View> sourceItem;
        SharedReference<View> targetItem;
        size_t oldIndex = -1;
        bool insertAfter = false;
        SharedReference<View> placeholder = std::make_shared<View>();
        Window window;
        Math::IntegerVector offset;

        ReorderingManager()
        {
            placeholder->setSizePolicy(SizePolicy::Fixed);
            window.setFlags(WindowFlags::Menu);
        }
    };

public:

    bool canReoredItemFrom(AWindowTouchDownEvent &event, const Math::IntegerVector &point, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) const override
    {
        /*if (!getAdapter() || !getAdapter()->canBeReoredered())
        {
        return false;
        }*/

        ReorderingManager &rm = ReorderingManager::getInstance();
        for (size_t i = 0; i < views.size(); ++i)
        {
            if (views[i].first == contentView)
            {
                if (i > 0)
                {
                    --i;
                    rm.sourceItem = views[i].first;
                    rm.offset = views[i].second;
                    rm.oldIndex = getIndexForItemView(rm.sourceItem);
                    rm.placeholder->setSize(rm.sourceItem->getSize());
                    return true;
                }
            }
        }
        return false;
    }

    bool canReoredItemTo(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) const override
    {
        ReorderingManager &rm = ReorderingManager::getInstance();

        Math::IntegerRectangle r = rm.window.getGeometry();
        r.position = getOwner()->getWindow()->getGeometry().position + event.getPosition() - rm.offset;
        rm.window.setGeometry(r);

        if (rm.sourceItem->getParent() == contentView.get())
        {
            UIApplication::getOperationDispatcher().addDelegate([this]() {
                ReorderingManager &rm = ReorderingManager::getInstance();
                if (rm.sourceItem->getParent() == contentView.get())
                {
                    SizeType oldIndex = getIndexForItemView(rm.sourceItem);
                    const_cast<This*>(this)->removeViewAtIndex(oldIndex);
                    const_cast<This*>(this)->insertViewAtIndex(oldIndex, rm.placeholder);

                    rm.window.setGeometry(Math::IntegerRectangle{ Math::IntegerVector{}, rm.sourceItem->getSize() });
                    rm.window.setView(rm.sourceItem);
                    rm.window.show();
                    rm.sourceItem->setPosition(Math::Vector{});
                }
                return AError::getEmptyError();
            }, true);
        }

        for (size_t i = 0; i < views.size(); ++i)
        {
            if (views[i].first == contentView)
            {
                if (i > 0)
                {
                    --i;
                    rm.targetItem = views[i].first;
                    rm.insertAfter = views[i].second.y > rm.targetItem->getSize().y / 2;

                    if (rm.targetItem == rm.placeholder || rm.targetItem == rm.sourceItem || getIndexForItemView(rm.targetItem) == InvalidIndex)
                    {
                        return false;
                    }

                    UIApplication::getOperationDispatcher().addDelegate([this]() {
                        ReorderingManager &rm = ReorderingManager::getInstance();
                        SizeType oldIndex = getIndexForItemView(rm.placeholder);
                        const_cast<This*>(this)->removeViewAtIndex(oldIndex);
                        SizeType newIndex = getIndexForItemView(rm.targetItem);
                        const_cast<This*>(this)->insertViewAtIndex(rm.insertAfter ? newIndex + 1 : newIndex, rm.placeholder);
                        return AError::getEmptyError();
                    }, true);

                    return true;
                }
            }
        }
        return false;
    }

    void acceptReoreding() override
    {
        ReorderingManager &rm = ReorderingManager::getInstance();

        SizeType index = getIndexForItemView(rm.placeholder);
        AAssert(index != InvalidIndex, "Source view is not found");
        removeViewAtIndex(index);
        //SizeType newIndex = getIndexForItemView(rm.targetItem);
        //AAssert(newIndex != InvalidIndex, "Target view is not found");
        rm.sourceItem->removeFromParent();
        rm.window.hide();
        insertViewAtIndex(index, rm.sourceItem);

        getAdapter()->onItemReoredered(rm.oldIndex, index);
    }

    void cancelReoreding() override
    {
        ReorderingManager &rm = ReorderingManager::getInstance();
        SizeType index = getIndexForItemView(rm.placeholder);
        const_cast<This*>(this)->removeViewAtIndex(index);
        rm.sourceItem->removeFromParent();
        rm.window.hide();
        const_cast<This*>(this)->insertViewAtIndex(rm.oldIndex, rm.sourceItem);
    }

    ListView()
    {
        /*auto *itemReorderingGestureRecognizer = new ItemReorderingGestureRecognizer();
        itemReorderingGestureRecognizer->setName(fmt::format("{} ItemReorderingGestureRecognizer", getObjectDescription()));
        itemReorderingGestureRecognizer->adapter = this;
        addGestureRecognizer(itemReorderingGestureRecognizer);*/
    }

    Math::IntegerVector getContentSize() const override
    {
        return contentView->getContentSize();
    }

    Direction getDirection() const
    {
        return StaticCast<FlexBox>(contentView)->getDirection();
    }

    void setDirection(Direction direction) const
    {
        return StaticCast<FlexBox>(contentView)->setDirection(direction);
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

        auto data = StaticCast<FlexBox>(contentView)->getData();
        ArrayUtils::Insert(data, data.begin() + index, {});
        StaticCast<FlexBox>(contentView)->setData(data);
    }

    void removeViewAtIndex(SizeType index) override
    {
        auto data = StaticCast<FlexBox>(contentView)->getData();
        data.erase(data.begin() + index);
        StaticCast<FlexBox>(contentView)->setData(data);

        Super::removeViewAtIndex(index);
    }

    void clearItems() override
    {
        StaticCast<FlexBox>(contentView)->setData({});
        contentView->removeAllViews();

        Super::clearItems();
    }

};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
