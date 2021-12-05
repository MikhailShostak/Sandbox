#pragma once

#include "UIGestureRecognizer.h"

namespace UI
{

class DragAndDropGestureRecognizer : public GestureRecognizer
{
    bool viewTouched = false;
    Math::IntegerVector lastPosition;
public:
    using GestureRecognizer::GestureRecognizer;
    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (raycastToView(event.getPosition()))
        {
            event.accept();
            ALogMessage("GestureRecognizer", "Start drag at %d %d", getPoint().x, getPoint().y);
            viewTouched = true;
            lastPosition = event.getPosition();
            return;
        }
        viewTouched = false;
    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (viewTouched)
        {
            raycastToView(event.getPosition());
            getView().setPosition(getView().getPosition() + Math::Vector{
                static_cast<float>(event.getPosition().x - lastPosition.x),
                static_cast<float>(-(event.getPosition().y - lastPosition.y))
            });
            lastPosition = event.getPosition();
            event.accept();
            ALogMessage("GestureRecognizer", "Move at %d %d", getPoint().x, getPoint().y);
        }
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (viewTouched)
        {
            event.accept();

            viewTouched = false;
            if (raycastToView(event.getPosition()))
            {
            }

            ALogMessage("GestureRecognizer", "Drop at %d %d", getPoint().x, getPoint().y);
        }
    }
};

}
