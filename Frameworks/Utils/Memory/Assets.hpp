#pragma once

#include "Memory/References.hpp"
#include "Text/String.hpp"

template<typename Type>
class StaticAsset
{
protected:
    using AssetInitializer = void(*)(Type &instance);
    WeakReference<Type> m_Instance;
    AssetInitializer m_Initializer;
public:
    StaticAsset(AssetInitializer initializer):
        m_Initializer(initializer)
    {
        
    }

    SharedReference<Type> Load()
    {
        SharedReference<Type> result;
        auto instance = m_Instance.lock();
        if(instance)
        {
            result = instance;
        }
        else
        {
            result = CreateShared<Type>();
            m_Initializer(*result);
            m_Instance = result;
        }
        return result;
    }
};

class AssetStorage
{
    //TODO: this temp function should be replaced with singleton storage for plugin support
    static auto &Storage()
    {
        static Map<String, std::pair<size_t, void*>> storage;
        return storage;
    }
public:
    template<typename Type>
    static void Add(const String &package, StaticAsset<Type> *asset)
    {
        Storage()[package] = { typeid(Type).hash_code(), asset };
    }

    template<typename Type>
    static void Remove(const String &package)
    {
        Storage().erase(package);
    }

    template<typename Type>
    static SharedReference<Type> Load(const String &package)
    {
        SharedReference<Type> object;
        auto it = Storage().find(package);
        if(it != Storage().end() && it->second.first == typeid(Type).hash_code())
        {
            object = reinterpret_cast<StaticAsset<Type>*>(it->second.second)->Load();
        }
        return object;
    }    
};

template<typename Type>
class DynamicAsset : public StaticAsset<Type>
{
    String m_Name;
public:
    DynamicAsset(const String &name, typename StaticAsset<Type>::AssetInitializer initializer):
        StaticAsset<Type>(initializer),
        m_Name(name)
    {
        AssetStorage::Add<Type>(m_Name, this);
    }

    ~DynamicAsset()
    {
        AssetStorage::Remove<Type>(m_Name);
    }
};
