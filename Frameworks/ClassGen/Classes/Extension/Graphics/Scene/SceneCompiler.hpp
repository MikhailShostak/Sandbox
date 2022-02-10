#pragma once

namespace ClassGen
{
struct SceneCompiler
    : public ClassGen::Compiler
{
    using This = SceneCompiler;
    using Super = ClassGen::Compiler;

    virtual ~SceneCompiler() {}
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
