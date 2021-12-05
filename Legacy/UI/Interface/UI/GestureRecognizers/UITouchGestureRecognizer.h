#pragma once

#include <algorithm>

#include "UI/GestureRecognizers/UIGestureRecognizer.h"
#include "Core/AWindowEvents.h"

namespace UI
{

class TouchGestureEvent : public GestureEvent
{
    const AWindowTouchEvent &windowEvent;
public:
    TouchGestureEvent(AObject &sender, const AWindowTouchEvent &windowEvent, View &view, const Math::IntegerVector &point):
        GestureEvent(sender, view, point),
        windowEvent(windowEvent)
    {
    }

    const AWindowTouchEvent &getWindowTouchEvent() const
    {
        return windowEvent;
    }
};

class TemplateTouchGestureEvent : public TouchGestureEvent
{
    bool inside = false;
public:
    TemplateTouchGestureEvent(AObject &sender, const AWindowTouchEvent &windowEvent, View &view, const Math::IntegerVector &point, bool inside):
        TouchGestureEvent(sender, windowEvent, view, point),
        inside(inside)
    {
    }

    bool isInside() const { return inside; }
};

class TouchDownGestureEvent : public TemplateTouchGestureEvent
{
public:
    using TemplateTouchGestureEvent::TemplateTouchGestureEvent;
};

class TouchEnterGestureEvent : public TouchGestureEvent
{
public:
    using TouchGestureEvent::TouchGestureEvent;
};

class TouchMoveGestureEvent : public TemplateTouchGestureEvent
{
public:
    using TemplateTouchGestureEvent::TemplateTouchGestureEvent;
};

class TouchExitGestureEvent : public TouchGestureEvent
{
public:
    using TouchGestureEvent::TouchGestureEvent;
};

class TouchUpGestureEvent : public TemplateTouchGestureEvent
{
public:
    using TemplateTouchGestureEvent::TemplateTouchGestureEvent;
};

class TouchWheelGestureEvent : public GestureEvent
{
    const AWindowTouchWheelEvent &windowEvent;
    bool inside = false;
public:
    TouchWheelGestureEvent(AObject &sender, const AWindowTouchWheelEvent &windowEvent, View &view, const Math::IntegerVector &point, bool inside):
        GestureEvent(sender, view, point),
        windowEvent(windowEvent),
        inside(inside)
    {
    }

    const AWindowTouchWheelEvent &getWindowTouchEvent() const
    {
        return windowEvent;
    }

    bool isInside() const { return inside; }
};

class TapGestureEvent : public TouchGestureEvent
{
public:
    using TouchGestureEvent::TouchGestureEvent;
};

class DoubleTouchDownGestureEvent : public TemplateTouchGestureEvent
{
public:
    using TemplateTouchGestureEvent::TemplateTouchGestureEvent;
};

class DoubleTouchUpGestureEvent : public TemplateTouchGestureEvent
{
public:
    using TemplateTouchGestureEvent::TemplateTouchGestureEvent;
};

class DoubleTapGestureEvent : public TouchGestureEvent
{
public:
    using TouchGestureEvent::TouchGestureEvent;
};

class TouchWheelGestureRecognizer : public GestureRecognizer
{
public:
    void onTouchWheel(AWindowTouchWheelEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        TouchWheelGestureEvent e(*this, event, getView(), point, isInside);
        if (sendAcceptableEventToView(e))
        {
            event.accept();
        }
    }
};

class TouchGestureRecognizer : public GestureRecognizer
{
    bool viewTouched = false;
public:
    using GestureRecognizer::GestureRecognizer;
    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        TouchDownGestureEvent e(*this, event, getView(), point, isInside);
        if (sendAcceptableEventToView(e))
        {
            event.accept();
        }

        if (isInside)
        {
            viewTouched = true;
        }
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        TouchUpGestureEvent e(*this, event, getView(), point, isInside);
        if (sendAcceptableEventToView(e))
        {
            event.accept();
        }
        if (isInside && viewTouched)
        {
            TapGestureEvent e(*this, event, getView(), point);
            if (!event.isAccepted() && sendAcceptableEventToView(e))
            {
                event.accept();
            }
        }
        viewTouched = false;
    }
};

class DoubleTouchGestureRecognizer : public GestureRecognizer
{
    bool touchDownHappened = false;
    bool isTouchedInside = false;
    Math::IntegerVector lastTouchPoint = {};
    ATimePoint<ASystemClock> lastTapDown;
    ATimePoint<ASystemClock> lastTapUp;
public:
    float threshold = 10.0f;
    using GestureRecognizer::GestureRecognizer;

    bool isDoubleDown() const
    {
        return (ASystemClock::now() - lastTapDown) < AMilliseconds(GetDoubleClickTime());
    }
    bool isDoubleUp() const
    {
        return (ASystemClock::now() - lastTapUp) < AMilliseconds(GetDoubleClickTime());
    }

    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (isTouchedInside && isDoubleDown() && (lastTouchPoint.getDistance2(point) < threshold))
        {
            DoubleTouchDownGestureEvent e(*this, event, getView(), point, isInside);
            if (sendAcceptableEventToView(e))
            {
                event.accept();
            }
            touchDownHappened = true;
        }
        else
        {
            touchDownHappened = false;
        }

        lastTouchPoint = point;
        isTouchedInside = isInside;
        lastTapDown = ASystemClock::now();
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (touchDownHappened && isTouchedInside && isDoubleUp())
        {
            DoubleTouchUpGestureEvent e(*this, event, getView(), point, isInside);
            if (sendAcceptableEventToView(e))
            {
                event.accept();
            }
            if (isInside)
            {
                DoubleTapGestureEvent e(*this, event, getView(), point);
                if (!event.isAccepted() && sendAcceptableEventToView(e))
                {
                    event.accept();
                }
            }
            isTouchedInside = false;
            touchDownHappened = false;
        }

        lastTapUp = ATimePoint<ASystemClock>();
    }
};

class MoveGestureRecognizer : public GestureRecognizer
{
    bool wasInside = false;
public:
    using GestureRecognizer::GestureRecognizer;
    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        TouchMoveGestureEvent e(*this, event, getView(), point, isInside);
        if (sendAcceptableEventToView(e))
        {
            event.accept();
        }

        if (!wasInside)
        {
            if (isInside)
            {
                TouchEnterGestureEvent e(*this, event, getView(), point);
                if (sendAcceptableEventToView(e))
                {
                    event.accept();
                }
                wasInside = true;
            }
        }
        else
        {
            if (!isInside)
            {
                TouchExitGestureEvent e(*this, event, getView(), point);
                if (sendAcceptableEventToView(e))
                {
                    event.accept();
                }
                wasInside = false;
            }
        }
    }
};

class TextEvent : public ViewEvent
{
    String text;
public:
    TextEvent(AObject &sender, View &view, const String &text):
        ViewEvent(sender, view),
        text(text)
    {
    }

    const String &getText() const { return text; }
};

class TextEditStartedEvent : public TextEvent
{
public:
    using TextEvent::TextEvent;
};

class TextSelectedEvent : public TextEvent
{
public:
    using TextEvent::TextEvent;
};

class TextEditedEvent : public TextEvent
{
public:
    using TextEvent::TextEvent;
};

class TextEditFinishedEvent : public TextEvent
{
public:
    using TextEvent::TextEvent;
};

}
