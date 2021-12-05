#pragma once

#include <Foundation>

template<typename Type>
class StaticAsset
{
protected:
    using AssetInitializer = void(*)(Type &object);
    WeakReference<Type> object;
    AssetInitializer initializer;
public:
    StaticAsset(AssetInitializer initializer):
        initializer(initializer)
    {
        
    }

    SharedReference<Type> load()
    {
        SharedReference<Type> result;
        auto object = this->object.lock();
        if(object)
        {
            result = object;
        }
        else
        {
            result = CreateShared<Type>();
            initializer(*result);
            object = result;
        }
        return result;
    }
};

class AssetStorage : public ASingleton<AssetStorage>
{
    UnorderedDictionary<String, APair<size_t, void*>> assets;
public:

    template<typename Type>
    void add(const String &package, StaticAsset<Type> *asset)
    {
        assets[package] = { AMeta::getStaticTypeHash<StaticAsset<Type>>(), asset };
    }

    template<typename Type>
    void remove(const String &package)
    {
        assets.erase(package);
    }

    template<typename Type>
    SharedReference<Type> load(const String &package) const
    {
        SharedReference<Type> object;
        auto it = assets.find(package);
        if(it != assets.end() && it->second.first == AMeta::getStaticTypeHash<StaticAsset<Type>>())
        {
            object = reinterpret_cast<StaticAsset<Type>*>(it->second.second)->load();
        }
        return object;
    }    
};

template<typename Type>
class DynamicAsset : public StaticAsset<Type>
{
    String package;
public:
    DynamicAsset(const String &package, StaticAsset<Type>::AssetInitializer initializer):
        StaticAsset<Type>(initializer),
        package(package)
    {
        AssetStorage::getInstance().add<Type>(package, this);
    }

    ~DynamicAsset()
    {
        AssetStorage::getInstance().remove<Type>(package);
    }
};
