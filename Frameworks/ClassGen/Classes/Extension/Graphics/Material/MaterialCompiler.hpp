#pragma once

namespace ClassGen
{
struct MaterialCompiler
    : public ClassGen::Compiler
{
    using This = MaterialCompiler;
    using Super = ClassGen::Compiler;

    virtual ~MaterialCompiler() {}
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
