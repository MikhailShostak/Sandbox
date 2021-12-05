#pragma once

#include "Graphics.h"

#include <queue>

namespace Legacy::Graphics
{

//TODO: rewrite to meta class
template<typename Object>
class HardwareHandle
{
    constexpr Object &self() { return static_cast<Object &>(*this); }
    constexpr const Object &self() const { return static_cast<Object &>(*this); }
public:

    class Storage : public ASingleton<Storage>
    {
    public:
        std::set<HardwareHandle*> set;
    };

    static void LoadObjects()
    {
        auto &set = Storage::getInstance().set;
        for (HardwareHandle* handle : set)
        {
            handle->hardwareObject.load(handle->self());
        }
        set.clear();
    }

    API::HardwareObject<Object> hardwareObject;

    ~HardwareHandle() { unload(); }

    bool isLoaded() const
    {
        return hardwareObject.isValid();
    }

    void load()
    {
        if(isLoaded())
        {
            return;
        }

        Storage::getInstance().set.insert(this);
    }
    
    void activate()
    {
        hardwareObject.activate(self());
        self().onActivate();
    }

    void deactivate()
    {
        self().onDeactivate();
        hardwareObject.deactivate(self());
    }

    void unload()
    {
        Storage::getInstance().set.erase(this);
        hardwareObject.unload(self());
    }
};

}
