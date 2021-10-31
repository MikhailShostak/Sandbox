#pragma once

namespace ClassGen
{
struct ClassExtension
    : public ClassGen::ExtensionInterface
{
    using This = ClassExtension;
    using Super = ClassGen::ExtensionInterface;

    virtual ~ClassExtension() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load(ClassGen::ExtensionLibrary & Library);
};
}
