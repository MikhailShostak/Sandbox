#pragma once

namespace System
{
template<typename InterfaceType>
struct ExtensionLibrary
{
    using This = ExtensionLibrary;
    System::Path Root;
    Array<Extension<InterfaceType>> Extensions;

    virtual ~ExtensionLibrary() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Root"] & Root;
    }
    virtual void Load();
    virtual void Unload();
};
}
