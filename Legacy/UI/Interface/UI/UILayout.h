#pragma once

#include <Foundation>

namespace UI
{

class View;

class Layout : public AObject
{
public:
    virtual ~Layout() {}

    virtual void load(View &parent) {}
    virtual void unload() {}

    virtual Math::IntegerVector getContentSize() const = 0;

    virtual void onLayout(View &view) = 0;
};

}