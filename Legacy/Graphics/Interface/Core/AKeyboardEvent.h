#pragma once

#include "AEvent.h"

class AKeyboardEvent : public AEvent
{

    int keyCode;
    int modifier;

public:

    int getModifier() const
    {
        return modifier;
    }

    int getKeyCode() const
    {
        return keyCode;
    }

    AKeyboardEvent(AObject &sender, int keyCode, int modifier):
        AEvent(sender),
        keyCode(keyCode),
        modifier(modifier)
    {

    }

};
