#pragma once

namespace ClassGen
{
struct ParticleSystemFileEditor
    : public ClassGen::FileEditor
{
    using This = ParticleSystemFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Mesh> ParticleSystem = {};
    System::Path LastPath = {};

    virtual ~ParticleSystemFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
