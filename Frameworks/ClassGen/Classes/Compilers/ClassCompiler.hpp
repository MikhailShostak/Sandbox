#pragma once

namespace ClassGen
{
struct ClassCompiler
    : public ClassGen::Compiler
{
    using This = ClassCompiler;
    using Super = ClassGen::Compiler;

    virtual ~ClassCompiler() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Compile(const SharedReference<ClassGen::BaseInfo> & BaseInfo, const System::Path & OutputFilePath);
};
}
