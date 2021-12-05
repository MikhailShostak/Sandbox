#pragma once

#include "APlugin.h"
#include "AApplicationContext.h"
#include "ASingleton.h"

template<typename Type>
class AApplicationPlugin final : public APlugin<Type>
{
public:

    using Super = APlugin<Type>;
    using This = AApplicationPlugin<Type>;

private:

    void(*onLoadFunction)(const SharedReference<Stack<AApplicationContext *>> &, Map<size_t, void *> * const &) = nullptr;
    void(*onUnloadFunction)() = nullptr;

public:

    bool load() override;
    bool load(const SharedReference<Stack<AApplicationContext *>> &contexts, Map<size_t, void *> * const &singletons);
    void unload() override;

protected:

    void clear() override;

};

template<typename Type>
inline bool AApplicationPlugin<Type>::load()
{
    return load(AApplicationContext::Data::getSharedContexts(), ASingletonStorage::getSharedSingletons());
}

template<typename Type>
inline bool AApplicationPlugin<Type>::load(const SharedReference<Stack<AApplicationContext *>> &contexts, Map<size_t, void *> * const &singletons)
{
    if(!Super::load())
    {
        return false;
    }

    onLoadFunction = reinterpret_cast<void (*)(const SharedReference<Stack<AApplicationContext *>> &, Map<size_t, void *> * const &)>(findFunction(this->handle, "pluginOnLoad"));
    if(!onLoadFunction)
    {
        clear();
        return false;
    }

    onUnloadFunction = reinterpret_cast<void (*)()>(findFunction(this->handle, "pluginOnUnload"));
    if(!onUnloadFunction)
    {
        clear();
        return false;
    }

    onLoadFunction(contexts, singletons);

    return true;
}

template<typename Type>
inline void AApplicationPlugin<Type>::unload()
{
    onUnloadFunction();
    Super::unload();
}

template<typename Type>
inline void AApplicationPlugin<Type>::clear()
{
    onLoadFunction = nullptr;
    onUnloadFunction = nullptr;
    Super::clear();
}

#define AApplicationPluginImplementation(Interface, Type, VersionCode, VersionName, Package) \
extern "C" { \
    APluginExport uint64_t pluginVersionCode() { return VersionCode; } \
    APluginExport const String &pluginVersionName() { static String versionName(VersionName); return versionName; } \
    APluginExport const String &pluginPackage() { static String package(Package); return package; } \
    APluginExport const SharedReference<Interface> &pluginInstance() \
    { \
        static SharedReference<Interface> object = CreateShared<Type>(); \
        return object; \
    } \
    APluginExport void pluginOnLoad(const SharedReference<Stack<AApplicationContext *>> &contexts, Map<size_t, void *> * const &singletons) \
    { \
        AApplicationContext::Data::setContexts(contexts);\
        ASingletonStorage::setSingletons(singletons);\
        ExecuteGlobalCalls();\
    } \
    APluginExport void pluginOnUnload() \
    { \
        \
    } \
}

#define AApplicationPluginImplementationWithCallbacks(Interface, Type, VersionCode, VersionName, Package, OnLoadCallback, OnUnloadCallback) \
extern "C" { \
    APluginExport uint64_t pluginVersionCode() { return VersionCode; } \
    APluginExport const String &pluginVersionName() { static String versionName(VersionName); return versionName; } \
    APluginExport const String &pluginPackage() { static String package(Package); return package; } \
    APluginExport const SharedReference<Interface> &pluginInstance() \
    { \
        static SharedReference<Interface> object = CreateShared<Type>(); \
        return object; \
    } \
    APluginExport void pluginOnLoad(const SharedReference<Stack<AApplicationContext *>> &contexts, Map<size_t, void *> * const &singletons) \
    { \
        AApplicationContext::Data::setContexts(contexts);\
        ASingletonStorage::setSingletons(singletons);\
        ExecuteGlobalCalls();\
        OnLoadCallback();\
    } \
    APluginExport void pluginOnUnload() \
    { \
        OnUnloadCallback();\
    } \
}
