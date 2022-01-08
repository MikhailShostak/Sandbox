#pragma once

namespace System
{

template<typename InterfaceType>
inline InterfaceType *Extension<InterfaceType>::Deref()
{
    return Instance.get();
}

template<typename InterfaceType>
inline void Extension<InterfaceType>::Load(const System::Path &Path)
{
    this->Path = Path;
    File.load(Path);
    Handle = File.get_alias<System::ExtensionHandle<InterfaceType>()>("Main")();
    Instance = UniqueReference<InterfaceType>(Handle.Constructor());
}

template<typename InterfaceType>
inline void Extension<InterfaceType>::Unload()
{
    if (File.is_loaded())
    {
        Instance.release();
        Handle = {};
        File.unload();
    }
}

}
