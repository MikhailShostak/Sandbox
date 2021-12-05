#pragma once

#include <Foundation>

#include "AWindow.h"
#include "AWindowEvents.h"

inline Math::IntegerVector getCursorPosition()
{
    POINT p;
    GetCursorPos(&p);
    Math::IntegerVector point;
    return Math::IntegerVector{ p.x, p.y };
}

inline void setCursorPosition(const Math::IntegerVector &position, bool shouldBeCaptured = false)
{
    SetCursorPos(position.x, position.y);
}

inline void showCursor()
{
    ShowCursor(true);
}

inline void hideCursor()
{
    ShowCursor(false);
}

inline bool isCursorVisible()
{
    CURSORINFO info;
    GetCursorInfo(&info);
    return info.flags & CURSOR_SHOWING;
}

inline bool isCursorSuppressed()
{
    CURSORINFO info;
    GetCursorInfo(&info);
    return info.flags & CURSOR_SUPPRESSED;
}

class AInputController : public AObject
{
protected:
    AWindow &window;
public:

    AInputController(AWindow &window) :
        window(window)
    {
        ARegisterEventCallback(onTouchDown);
        ARegisterEventCallback(onTouchMove);
        ARegisterEventCallback(onTouchUp);

        ARegisterEventCallback(onKeyPress);
        ARegisterEventCallback(onKeyRelease);

        ARegisterEventCallback(onUpdate);

        window.eventChannel.registerObserver(*this);
        window.inputEventChannel.registerObserver(*this);
    }

    ~AInputController()
    {
        window.inputEventChannel.unregisterObserver(*this);
        window.eventChannel.unregisterObserver(*this);

        AUnregisterEventCallback(onUpdate);

        AUnregisterEventCallback(onKeyRelease);
        AUnregisterEventCallback(onKeyPress);

        AUnregisterEventCallback(onTouchUp);
        AUnregisterEventCallback(onTouchMove);
        AUnregisterEventCallback(onTouchDown);
    }

protected:
    virtual void onTouchDown(AWindowTouchDownEvent &event) {}
    virtual void onTouchMove(AWindowTouchMoveEvent &event) {}
    virtual void onTouchUp(AWindowTouchUpEvent &event) {}

    virtual void onKeyPress(AWindowKeyPressEvent &event) {}
    virtual void onKeyRelease(AWindowKeyReleaseEvent &event) {}

    virtual void onUpdate(AUpdateEvent &event) {}
};
