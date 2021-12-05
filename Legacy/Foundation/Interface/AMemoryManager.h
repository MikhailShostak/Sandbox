#pragma once

#include "ASingleton.h"

struct AMemoryObjectInfo
{
    void *pointer;
    const char *name;
    size_t size;
    void *vtable = nullptr;
};

class AMemoryManagerObserver
{
public:

    virtual void onObjectCreate(const AMemoryObjectInfo &objectInfo) {}
    virtual void onObjectDestroy(const AMemoryObjectInfo &objectInfo) {}

};

class AMemoryManager : public ASingleton<AMemoryManager>
{

    Map<void *, AMemoryObjectInfo> objects;
    Array<AMemoryManagerObserver *> observers;

public:

    void addObject(const AMemoryObjectInfo &objectInfo)
    {
        objects.insert({ objectInfo.pointer, objectInfo });
        for(auto &observer : observers)
        {
            observer->onObjectCreate(objectInfo);
        }
    }

    void removeObject(void *pointer)
    {
        auto it = objects.find(pointer);
        if(it != objects.end())
        {
            for(auto &observer : observers)
            {
                observer->onObjectDestroy(it->second);
            }
            objects.erase(it);
        }
    }

    const Map<void *, AMemoryObjectInfo> &getObjects() const { return objects; }

    void addObserver(AMemoryManagerObserver *observer) { observers.push_back(observer); }
    void removeObserver(AMemoryManagerObserver *observer) { ArrayUtils::Remove(observers, observer); }

};

