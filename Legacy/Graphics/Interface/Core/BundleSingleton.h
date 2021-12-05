#pragma once

#include <Foundation>

#include "ACommonEvents.h"
#include "StateMachine.h"
#include "Assets.h"

template<typename Type>
class BundleSingleton : public AObject, public ASingleton<Type>
{

    static Map<String, BundleSingleton*> &getBundles()
    {
        static Map<String, BundleSingleton*> bundles;
        return bundles;
    }

    String name;

protected:
    AssetsRepository assetsRepository;
public:

    static BundleSingleton *findBundle(const String &name)
    {
        auto it = getBundles().find(name);
        if (it == getBundles().end())
        {
            return nullptr;
        }

        return it->second;
    }

    BundleSingleton(const String &name):
        name(name)
    {
        ARegisterEventCallback(onLoad);
        ARegisterEventCallback(onUnload);
    }

    ~BundleSingleton()
    {
        AUnregisterEventCallback(onLoad);
        AUnregisterEventCallback(onUnload);
    }

    const String &getName() const { return name; }

    template<typename Type>
    ::SharedReference<Type> findObject(AssetID assetID) //TODO: const?
    {
        Asset *asset = assetsRepository.findAsset(assetID);
        return (asset ? StaticCast<Type>(asset->getObject()) : nullptr);
    }

protected:

    virtual void onLoad(ALoadEvent &event)
    {
        AAssert(!findBundle(name), "Bundle with that name already registered");
        getBundles().insert({name, this});
        onLoadAssets();
        assetsRepository.load();
    }

    virtual void onUnload(AUnloadEvent &event)
    {
        assetsRepository.unload();
        getBundles().erase(name);
    }

    virtual void onLoadAssets() = 0;
};

#define DeclareBundle(name)\
class name ## Bundle : public BundleSingleton<name ## Bundle>\
{\
public:\
    name ## Bundle() : BundleSingleton(#name) {}\
    void onLoadAssets() override;\
};

#define ImplementBundle(name)\
void name ## Bundle::onLoadAssets()
