#pragma once

#include "AFlags.h"
#include "AEvent.h"
#include "String.h"
#include <Math>

class AWindow;

class AWindowEvent : public AEvent
{
public:
    AWindowEvent(AWindow &sender);
    AWindow &getWindow() const;
};

class AAddToWindowEvent : public AWindowEvent
{
public:
    using AWindowEvent::AWindowEvent;
};

class ARemoveFromWindowEvent : public AWindowEvent
{
public:
    using AWindowEvent::AWindowEvent;
};

enum class ATouchID
{
    Undefined = 0,
    Touch0 = 1 << 1,
    Touch1 = 1 << 2,
    Touch2 = 1 << 3,
    Touch3 = 1 << 4,
    Touch4 = 1 << 5,
    Touch5 = 1 << 6,
    Touch6 = 1 << 7,
    Touch7 = 1 << 8,
    Touch8 = 1 << 9,
    Touch9 = 1 << 10,
    LeftMouseButton = Touch0,
    RightMouseButton = Touch1,
    MiddleMouseButton = Touch2,
    X1MouseButton = Touch3,
    X2MouseButton = Touch4,
};

ADeclareFlagsOperators(ATouchID)

enum class ATouchModifier
{
    Undefined = 0,
    AltKey = 1 << 1,
    ControlKey = 1 << 2,
    ShiftKey = 1 << 3,
    AltControlKeys = AltKey | ControlKey,
    AltShiftKeys = AltKey | ShiftKey,
    ControlShiftKeys = ControlKey | ShiftKey,
    AltControlShiftKeys = AltKey | ControlKey | ShiftKey,
};

ADeclareFlagsOperators(ATouchModifier)

/*inline bool operator !(ATouchID value)
{
return uint64_t(value) == 0;
}

inline operator bool(ATouchModifier value)
{
return uint64_t(value) == 0;
}*/

class AWindowPointerEvent : public AAcceptableEvent
{
public:
    Math::IntegerVector position;
    ATouchModifier touchModifier; //TODO: rename to PointerModifier

    AWindowPointerEvent(AObject &sender, ATouchModifier touchModifier, const Math::IntegerVector &position):
        AAcceptableEvent(sender),
        touchModifier(touchModifier),
        position(position)
    {
    }

    ATouchModifier getTouchModifier() const { return this->touchModifier; }
    const Math::IntegerVector &getPosition() const { return this->position; }
};

class AWindowTouchWheelEvent : public AWindowPointerEvent
{
    int64_t value;
public:
    AWindowTouchWheelEvent(AObject &sender, ATouchModifier touchModifier, const Math::IntegerVector &position, int64_t value):
        AWindowPointerEvent(sender, touchModifier, position),
        value(value)
    {

    }

    int64_t getValue() const { return value; }
};

class AWindowTouchEvent : public AWindowPointerEvent
{
public:

private:
	ATouchID touchID;
public:

	AWindowTouchEvent(AObject &sender, ATouchID touchID, ATouchModifier touchModifier, const Math::IntegerVector &position):
        AWindowPointerEvent(sender, touchModifier, position),
        touchID(touchID)
	{}

    bool isPressed(ATouchID touchID) const { return uint64_t(this->touchID & touchID) != 0; }
    bool isReleased(ATouchID touchID) const { return uint64_t(this->touchID & touchID) != 0; }
    ATouchID getTouchID() const { return this->touchID; }
};

class AWindowTouchUpEvent : public AWindowTouchEvent
{
public:
	using AWindowTouchEvent::AWindowTouchEvent;
};

class AWindowTouchDownEvent : public AWindowTouchEvent
{
public:
	using AWindowTouchEvent::AWindowTouchEvent;
};

class AWindowTouchMoveEvent : public AWindowTouchEvent
{
public:
	using AWindowTouchEvent::AWindowTouchEvent;
};


class AWindowKeyEvent : public AAcceptableEvent
{
    uint64_t key = 0;
public:
    AWindowKeyEvent(AObject &sender, uint64_t key) :
        AAcceptableEvent(sender),
        key(key)
    {}

    uint64_t getKey() const { return this->key; }
};

class AWindowKeyPressEvent : public AWindowKeyEvent
{
public:
    using AWindowKeyEvent::AWindowKeyEvent;
};

class AWindowKeyReleaseEvent : public AWindowKeyEvent
{
public:
    using AWindowKeyEvent::AWindowKeyEvent;
};

class AWindowKeyCharEvent : public AAcceptableEvent
{
    char symbol = 0;
public:
    AWindowKeyCharEvent(AObject &sender, char symbol) :
        AAcceptableEvent(sender),
        symbol(symbol) 
    {}

    char getSymbol() const { return this->symbol; }
};

