#pragma once

namespace ClassGen
{
struct EnumerationExtension
    : public ClassGen::ExtensionInterface
{
    using This = EnumerationExtension;
    using Super = ClassGen::ExtensionInterface;

    virtual ~EnumerationExtension() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    void Load(ClassGen::ExtensionLibrary & Library);
};
}
