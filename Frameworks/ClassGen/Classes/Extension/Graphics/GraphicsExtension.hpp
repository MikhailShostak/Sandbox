#pragma once

namespace ClassGen
{
struct GraphicsExtension
    : public ClassGen::ExtensionInterface
{
    using This = GraphicsExtension;
    using Super = ClassGen::ExtensionInterface;

    virtual ~GraphicsExtension() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load(ClassGen::ExtensionLibrary & Library);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
