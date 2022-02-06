#pragma once

namespace ClassGen
{
struct TextureCompiler
    : public ClassGen::Compiler
{
    using This = TextureCompiler;
    using Super = ClassGen::Compiler;

    virtual ~TextureCompiler() {}
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
