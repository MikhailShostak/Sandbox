#pragma once

#include "APlatform.h"
#include "String.h"
#include "APath.h"
#include "AMemory.h"

#if APlatformWindowsDesktop
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#   define LibraryHandle HMODULE
#   define NullLibraryHandle LibraryHandle()
#   define initLibraryHandle(handle) handle
#   define loadLibrary(path) LoadLibraryA(path)
#   define findFunction(handle, name) GetProcAddress(handle, name)
#   define unloadLibrary(handle) FreeLibrary(handle)

#   define APluginExport __declspec(dllexport)
#   define APluginImport __declspec(dllimport)
#   define APluginHidden

#   define ADefaultPluginExtension "dll"

#else

#   include <dlfcn.h>
#   define LibraryHandle void *
#   define NullLibraryHandle nullptr
#   define initLibraryHandle(handle) handle = nullptr
#   define loadLibrary(path) dlopen(path, RTLD_LAZY)
#   define findFunction(handle, name) dlsym(handle, name)
#   define unloadLibrary(handle) dlclose(handle)

#   define APluginExport __attribute__((visibility("default")))
#   define APluginImport __attribute__((visibility("default")))
#   define APluginHidden __attribute__((visibility("hidden")))

#if APlatformOSX
#   define ADefaultPluginExtension "dylib"
#else
#   define ADefaultPluginExtension "so"
#endif

#endif

#define APluginImplementation(Interface, Type, VersionCode, VersionName, Package) \
extern "C" { \
    APluginExport uint64_t pluginVersionCode() { return VersionCode; } \
    APluginExport const String &pluginVersionName() { static String versionName(VersionName); return versionName; } \
    APluginExport const String &pluginPackage() { static String package(Package); return package; } \
    APluginExport const SharedReference<Interface> &pluginInstance() \
    { \
        static SharedReference<Interface> object = createNew<Type>(); \
        return object; \
    } \
}

template<typename Type>
class APlugin
{
public:

    using This = APlugin<Type>;

protected:

    LibraryHandle handle = NullLibraryHandle;
    uint64_t(*versionCodeFunction)() = nullptr;
    const String &(*versionNameFunction)() = nullptr;
    const String &(*packageFunction)() = nullptr;
    const SharedReference<Type> &(*instanceFunction)() = nullptr;

    APath path;

public:

    APlugin() {}

    APlugin(const APlugin &plugin) = delete;
    APlugin(APlugin &&plugin) = delete;

    virtual ~APlugin() {
        AAssert(!isLoaded(), "Plugin was destroyed but wasn't unloaded. Unload plugin before destroy");
    }

    const APath &getPath() const
    {
        return path;
    }

    void setPath(const APath &path)
    {
        AAssert(!isLoaded(), "Unload the plugin before changing the path");
        this->path = path;
    }

    uint64_t getVersionCode() const
    {
        AAssert(isLoaded(), "Plugin is not loaded");
        return versionCodeFunction();
    }

    const String &getVersionName() const
    {
        AAssert(isLoaded(), "Plugin is not loaded");
        return versionNameFunction();
    }

    const String &getPackage() const
    {
        AAssert(isLoaded(), "Plugin is not loaded");
        return packageFunction();
    }

    const SharedReference<Type> &getInstance() const
    {
        AAssert(isLoaded(), "Plugin is not loaded");
        return instanceFunction();
    }

    bool isLoaded() const { return handle != NullLibraryHandle; }

    virtual bool load();
    virtual void unload();

protected:

    virtual void clear();

};

template<typename Type>
inline bool APlugin<Type>::load()
{
    AAssert(!isLoaded(), "Plugin already loaded");

    handle = loadLibrary(path.toString().data());
    if(handle == NullLibraryHandle)
    {
        return false;
    }

    versionCodeFunction = reinterpret_cast<uint64_t (*)()>(findFunction(this->handle, "pluginVersionCode"));
    if(!versionCodeFunction)
    {
        clear();
        return false;
    }

    versionNameFunction = reinterpret_cast<const String &(*)()>(findFunction(this->handle, "pluginVersionName"));
    if(!versionNameFunction)
    {
        clear();
        return false;
    }

    packageFunction = reinterpret_cast<const String &(*)()>(findFunction(this->handle, "pluginPackage"));
    if(!packageFunction)
    {
        clear();
        return false;
    }

    instanceFunction = reinterpret_cast<const SharedReference<Type> &(*)()>(findFunction(this->handle, "pluginInstance"));
    if(!instanceFunction)
    {
        clear();
        return false;
    }

    return true;
}

template<typename Type>
inline void APlugin<Type>::unload()
{
    clear();
}

template<typename Type>
inline void APlugin<Type>::clear()
{
    if(handle != NullLibraryHandle)
    {
        unloadLibrary(handle);
        handle = NullLibraryHandle;
    }
}
