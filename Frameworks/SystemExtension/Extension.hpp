#pragma once

namespace System
{
template<typename InterfaceType>
struct Extension
{
    using This = Extension;
    System::Path Path;
    boost::dll::shared_library File;
    System::ExtensionHandle<InterfaceType> Handle;
    UniqueReference<InterfaceType> Instance;
    Extension() = default;
    Extension(Extension &&other) = default;
    Extension &operator =(Extension &&other) = default;

    virtual ~Extension() {}

protected:
    InterfaceType *Deref();
public:
    InterfaceType &operator *() { return *Deref(); }
    const InterfaceType &operator *() const { return *ConstCast<decltype(this)>(this)->Deref(); }
    InterfaceType *operator ->() { return Deref(); }
    const InterfaceType *operator ->() const { return ConstCast<decltype(this)>(this)->Deref(); }

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load(const System::Path & Path);
    virtual void Unload();
};
}
