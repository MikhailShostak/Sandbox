#pragma once

namespace ClassGen
{
struct ExtensionInterface
{
    using This = ExtensionInterface;

    virtual ~ExtensionInterface() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load(ClassGen::ExtensionLibrary & Library);

    void Initialize()
    {
    }
};
}
