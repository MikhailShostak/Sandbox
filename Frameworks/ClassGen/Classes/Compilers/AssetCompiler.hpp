#pragma once

namespace ClassGen
{
struct AssetCompiler
    : public ClassGen::Compiler
{
    using This = AssetCompiler;
    using Super = ClassGen::Compiler;

    virtual ~AssetCompiler() {}
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
