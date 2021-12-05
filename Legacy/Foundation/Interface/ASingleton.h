#pragma once

class ASingletonStorage
{
    static Map<size_t, void *> *&getSingletonsData()
    {
        static Map<size_t, void *> *singletons = nullptr;
        return singletons;
    }

public:

    static Map<size_t, void *> * const &getSharedSingletons();

    static Map<size_t, void *> &getSingletons()
    {
        return *getSharedSingletons();
    }

    static void setSingletons(Map<size_t, void *> * const &singletons)
    {
        auto &data = getSingletonsData();
        data = singletons;
    }

    static void registerSingleton(size_t hash, void *singleton);
    static void *findSingleton(size_t hash);
};

template<typename Type>
class ASingleton
{
public:

    static Type &getInstance()
    {
        Type *existedSingleton = reinterpret_cast<Type *>(ASingletonStorage::findSingleton(typeid(Type).hash_code()));
        if(!existedSingleton)
        {
            static Type singleton;
            existedSingleton = &singleton;
        }
        return *existedSingleton;
    }

protected:

    ASingleton()
    {
        ASingletonStorage::registerSingleton(typeid(Type).hash_code(), static_cast<Type *>(this));
    }

};

inline Map<size_t, void *> * const &ASingletonStorage::getSharedSingletons()
{
    auto &data = getSingletonsData();
    if (!data)
    {
        data = new Map<size_t, void *>();
    }
    return data;
}

inline void ASingletonStorage::registerSingleton(size_t hash, void *singleton)
{
    getSingletons().insert({ hash, singleton });
}

inline void *ASingletonStorage::findSingleton(size_t hash)
{
    auto &data = getSingletons();
    auto it = data.find(hash);
    if (it != data.end())
    {
        return it->second;
    }

    return nullptr;
}
