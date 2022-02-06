#pragma once

namespace ClassGen
{
struct MeshCompiler
    : public ClassGen::Compiler
{
    using This = MeshCompiler;
    using Super = ClassGen::Compiler;

    virtual ~MeshCompiler() {}
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
