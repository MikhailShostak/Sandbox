#pragma once

#include <Foundation>

#include "MetaObject.h"

using AssetID = AStaticInteger64;

class Asset;

class BaseAssetValue
{
protected:
    AssetID assetID;
    Asset *asset = nullptr;
public:
    BaseAssetValue(AssetID assetID):
        assetID(assetID)
    {}

    virtual ~BaseAssetValue() {}

    AssetID getAssetID() const { return assetID; }
    void setAsset(Asset *asset) { this->asset = asset; }
    Asset *getAsset() const { return asset; }

    virtual AVariant getValue() const = 0;
};

class Asset final
{
    AssetID id;
    Meta::ConstructorPointer<AObject> constructor;
    ::SharedReference<AObject> object;

    Map<String, AVariant> properties;
public:

    template<typename Type>
    static Asset create(AssetID assetID, const ::SharedReference<Type> &object = nullptr)
    {
        Asset asset;
        asset.id = assetID;
        asset.constructor = &CreateAs<Type, AObject>;
        asset.object = object;
        return asset;
    }

protected:
    Asset() {}

public:
    AssetID getID() const { return id; }
    const ::SharedReference<AObject> &getObject() const { return object; }

    Map<String, AVariant> &getProperties() { return properties; }
    const Map<String, AVariant> &getProperties() const { return properties; }

    template<typename Type>
    void setProperty(const String &name, const AssetID &assetID);

    void setProperty(const String &name, const AVariant &value)
    {
        properties.insert({ name, value });
    }

    void removeProperty(const String &name)
    {
        properties.erase(name);
    }

    bool isLoaded() const { return object.get(); }

    void load()
    {
        if (isLoaded())
        {
            return;
        }

        object = createNewObject();

        auto it = MetaObjectManager::getInstance().metaObjects.find(AMeta::getDynamicTypeHash(*object));
        if (it == MetaObjectManager::getInstance().metaObjects.end())
        {
            ALogMessage("Assets", "MetaObject not found for asset<%s>, properties can't be set", AMeta::getDynamicTypeName(*object));
            return;
        }

        MetaObject *metaObject = it->second;
        for (const auto &pair : properties)
        {
            const String &name = pair.first;
            const AVariant &value = pair.second;
            if (value.isValue<::SharedReference<BaseAssetValue>>())
            {
                const ::SharedReference<BaseAssetValue> &assetValue = value.asValue<::SharedReference<BaseAssetValue>>();
                metaObject->setProperty(object.get(), name, assetValue->getValue());
            }
            else
            {
                metaObject->setProperty(object.get(), name, value);
            }
        }
    }

    void unload()
    {
        if (!isLoaded())
        {
            return;
        }

        object = nullptr;
    }

    ::SharedReference<AObject> createNewObject() const { return ::SharedReference<AObject>(constructor()); }

    Asset duplicate(AssetID newID)
    {
        Asset newAsset;
        newAsset.id = id;
        newAsset.constructor = constructor;
        newAsset.object = createNewObject();
        Memory::Copy(*getObject(), *newAsset.getObject());
        return newAsset;
    }
};

template<typename Type>
class AssetValue : public BaseAssetValue
{
public:
    using BaseAssetValue::BaseAssetValue;
    virtual AVariant getValue() const { return static_cast<Type>(asset->getObject().get()); }
};

template<typename Type>
class AssetValue<::SharedReference<Type>> : public BaseAssetValue
{
public:
    using BaseAssetValue::BaseAssetValue;
    virtual AVariant getValue() const { return asset->getObject().as<Type>(); }
};

template<typename Type>
inline void Asset::setProperty(const String &name, const AssetID &assetID)
{
    setProperty(name, ::SharedReference<BaseAssetValue>(new AssetValue<Type>(assetID)));
}

class AssetsRepository
{
    Map<AssetID, Asset> assets;
    bool loaded = false;
public:

    template<typename Type>
    Asset &registerAsset(AssetID assetID = AssetID::Random())
    {
        loaded = false;
        Asset asset = Asset::create<Type>(assetID);
        assets.insert({ asset.getID(), asset });
        return *findAsset(asset.getID()); //TODO: optimize
    }

    void unregister(AssetID assetID)
    {
        assets.erase(assetID);
    }

    Asset *findAsset(AssetID assetID) //TODO: const?
    {
        auto it = assets.find(assetID);
        return it != assets.end() ? &it->second : nullptr;
    }

    size_t getSize() const
    {
        return assets.size();
    }

    void load()
    {
        for (auto &pair : assets)
        {
            Asset &asset = pair.second;
            if(!asset.isLoaded())
            {
                loadAsset(asset);
            }
        }
        loaded = true;
    }

    void loadAsset(Asset &asset)
    {
        for (auto &pair : asset.getProperties())
        {
            AVariant &value = pair.second;
            if (value.isValue<::SharedReference<BaseAssetValue>>())
            {
                ::SharedReference<BaseAssetValue> &assetValue = value.asValue<::SharedReference<BaseAssetValue>>();
                Asset *propertyAsset = findAsset(assetValue->getAssetID());
                loadAsset(*propertyAsset);
                assetValue->setAsset(propertyAsset);
            }
        }
        asset.load();
    }

    void unload()
    {
        size_t i = 0;
        size_t count = assets.size();
        for (auto &pair : assets)
        {
            Asset &asset = pair.second;
            asset.unload();
        }
        loaded = false;
    }

    ::SharedReference<AObject> createNewObject(AssetID assetID)
    {
        Asset *asset = findAsset(assetID);
        AAssert(asset, "Asset not found");
        return asset->createNewObject();
    }

    Asset &duplicateAsset(AssetID assetID)
    {
        AAssert(loaded, "Asset bundle wasn't loaded");
        Asset *asset = findAsset(assetID);
        AAssert(asset, "Asset not found");
        AssetID newID = AssetID::Random();
        assets.insert({ newID, asset->duplicate(newID) });
        return *findAsset(newID); //TODO: optimize
    }
};
