#pragma once

namespace System
{
template<typename Type>
struct ConfigFile
{
    using This = ConfigFile;
    System::Path Path = {};
    Type Data = {};

protected:
    Type *GetIndirectValue();
public:
    Type &operator*() { return *GetIndirectValue(); }
    const Type &operator*() const { return *ConstCast(this)->GetIndirectValue(); }
    Type *operator->() { return GetIndirectValue(); }
    const Type *operator->() const { return ConstCast(this)->GetIndirectValue(); }

    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
    }
    virtual bool/*Result*/ Load();
    virtual bool/*Result*/ Save();

    void Initialize()
    {
    }
};
}
