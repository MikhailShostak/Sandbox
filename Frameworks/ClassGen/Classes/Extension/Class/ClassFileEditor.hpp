#pragma once

namespace ClassGen
{
struct ClassFileEditor
    : public ClassGen::FileEditor
{
    using This = ClassFileEditor;
    using Super = ClassGen::FileEditor;

    virtual ~ClassFileEditor() {}

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();
    virtual void ShowGraph(const System::Path & Path);
    virtual void RenderDetails(const System::Path & Path, ClassGen::ClassInfo & ClassInfo);
    virtual void RenderData(const System::Path & Path, ClassGen::ClassInfo & ClassInfo);
    virtual void RenderDataRecursively(const System::Path & Root, const String & Name);
};
}
