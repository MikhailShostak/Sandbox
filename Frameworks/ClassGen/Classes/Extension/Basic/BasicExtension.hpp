#pragma once

namespace ClassGen
{
struct BasicExtension
    : public ClassGen::ExtensionInterface
{
    using This = BasicExtension;
    using Super = ClassGen::ExtensionInterface;

    virtual ~BasicExtension() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    void Load(ClassGen::ExtensionLibrary & Library);
};
}
