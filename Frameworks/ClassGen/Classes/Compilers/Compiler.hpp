#pragma once

namespace ClassGen
{
struct Compiler
{
    using This = Compiler;

    virtual ~Compiler() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void CompileFile(const System::Path & Path);
    virtual void Compile(const SharedReference<ClassGen::BaseInfo> & BaseInfo, const System::Path & OutputFilePath);
};
}
