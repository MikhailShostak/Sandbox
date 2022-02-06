#pragma once

namespace ClassGen
{
struct ParticleSystemCompiler
    : public ClassGen::Compiler
{
    using This = ParticleSystemCompiler;
    using Super = ClassGen::Compiler;

    virtual ~ParticleSystemCompiler() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Compile(const SharedReference<ClassGen::BaseInfo> & BaseInfo, const System::Path & OutputFilePath);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
