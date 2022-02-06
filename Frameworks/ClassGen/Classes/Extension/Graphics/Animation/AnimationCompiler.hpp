#pragma once

namespace ClassGen
{
struct AnimationCompiler
    : public ClassGen::Compiler
{
    using This = AnimationCompiler;
    using Super = ClassGen::Compiler;

    virtual ~AnimationCompiler() {}
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
