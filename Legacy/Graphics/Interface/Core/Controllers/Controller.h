#pragma once

#include <Foundation>

class Controller : public AObject
{
public:
    virtual void onActivate() {}
    virtual void onDeactivate() {}
};