#pragma once

#include "UIGestureRecognizer.h"
#include "UITouchGestureRecognizer.h"
#include "UI/UIApplication.h"

namespace UI
{

class ReorderingAdapter
{
public:
    virtual bool canReoredItemFrom(AWindowTouchDownEvent &event, const Math::IntegerVector &point, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) const = 0;
    virtual bool canReoredItemTo(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) const = 0;
    virtual void acceptReoreding() = 0;
    virtual void cancelReoreding() = 0;
};

class ItemReorderingGestureRecognizer : public GestureRecognizer
{
    bool reordering = false;
    bool accepted = false;
    Math::Vector startPosition;
public:

    ReorderingAdapter * adapter = nullptr;

    using GestureRecognizer::GestureRecognizer;
    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!isInside)
        {
            return;
        }

        if (adapter->canReoredItemFrom(event, point, views))
        {
            ALogMessage("GestureRecognizer", "Start reordering at %d %d", point.x, point.y);
            reordering = true;
        }
    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!reordering || !isInside)
        {
            return;
        }

        ALogMessage("GestureRecognizer", "Reordering to %d %d", point.x, point.y);
        if (adapter->canReoredItemTo(event, point, views))
        {
            accepted = true;
            ALogMessage("GestureRecognizer", "Accepted");
        }
        event.accept();
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!accepted || !isInside)
        {
            if (reordering)
            {
                UIApplication::getOperationDispatcher().addDelegate([this]() {
                    adapter->cancelReoreding();
                    return AError::getEmptyError();
                }, true);
            }
        }
        else
        {
            accepted = false;

            UIApplication::getOperationDispatcher().addDelegate([this]() {
                adapter->acceptReoreding();
                return AError::getEmptyError();
            }, true);
            event.accept();
        }
        reordering = false;
    }
};

}