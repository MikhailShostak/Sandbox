#pragma once

#include "UIGestureRecognizer.h"
#include "UITouchGestureRecognizer.h"

namespace UI
{

class DraggingGestureRecognizer : public GestureRecognizer
{
    bool viewTouched = false;
    Math::Vector startPosition;
public:
    Math::IntegerRectangle hitArea = Math::IntegerRectangle{ Math::IntegerVector{ (std::numeric_limits<int32_t>::min)() / 2, (std::numeric_limits<int32_t>::min)() / 2 }, Math::IntegerVector{ (std::numeric_limits<int32_t>::max)(), (std::numeric_limits<int32_t>::max)() } };
    Math::IntegerRectangle draggingArea = Math::IntegerRectangle{ Math::IntegerVector{ (std::numeric_limits<int32_t>::min)() / 2, (std::numeric_limits<int32_t>::min)() / 2 }, Math::IntegerVector{ (std::numeric_limits<int32_t>::max)(), (std::numeric_limits<int32_t>::max)() } };
    size_t gridSize = 0;
    bool useParentViewArea = false;
    bool moveViewToFront = true;
    using GestureRecognizer::GestureRecognizer;
    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!isInside)
        {
            return;
        }

        if (point.x > hitArea.position.x && point.y > hitArea.position.y && point.x < hitArea.position.x + hitArea.size.x && point.y < hitArea.position.y + hitArea.size.y)
        {
            event.accept();
            ALogMessage("GestureRecognizer", "Start drag at %d %d", point.x, point.y);
            viewTouched = true;
            startPosition = getView().getPosition() - event.getPosition().getXY<Math::Vector>();
            if (moveViewToFront)
            {
                getView().moveFront();
            }
        }
    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!viewTouched)
        {
            return;
        }

        Math::Vector p = startPosition + event.getPosition().getXY<Math::Vector>();
        if (gridSize > 0)
        {
            p.x -= std::fmod(p.x, gridSize);
            p.y -= std::fmod(p.y, gridSize);
            p.z -= std::fmod(p.z, gridSize);
        }
        getView().setPosition(p);
        if (useParentViewArea)
        {
            Math::IntegerVector parentSize = getView().getParent()->getSize();
            //TODO: clamp
            getView().setPosition({
                static_cast<float>(std::max<int32_t>(std::min<int32_t>(getView().getPosition().x, parentSize.x - getView().getSize().x), 0)),
                static_cast<float>(std::max<int32_t>(std::min<int32_t>(getView().getPosition().y, parentSize.y - getView().getSize().y), 0))
            });
        }
        else
        {
            //TODO: clamp
            getView().setPosition({
                static_cast<float>(std::min<int32_t>(std::max<int32_t>(getView().getPosition().x, draggingArea.position.x), draggingArea.position.x + draggingArea.size.x - getView().getSize().x)),
                static_cast<float>(std::min<int32_t>(std::max<int32_t>(getView().getPosition().y, draggingArea.position.y), draggingArea.position.y + draggingArea.size.y - getView().getSize().y))
            });
        }
        TouchMoveGestureEvent e(*this, event, getView(), point, isInside);
        sendAcceptableEventToView(e);
        event.accept();
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (!viewTouched)
        {
            return;
        }
        viewTouched = false;

        event.accept();
    }
};

}
