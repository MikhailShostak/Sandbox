#pragma once

namespace ClassGen
{
struct ClassFileEditor
    : public ClassGen::FileEditor
{
    using This = ClassFileEditor;
    using Super = ClassGen::FileEditor;
    ClassGen::ObjectPropertyEditor DataEditor = {};

    virtual ~ClassFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void ShowGraph(const System::Path & Path);
    virtual void RenderDetails(const System::Path & Path, ClassGen::ClassInfo & ClassInfo);
    virtual void RenderData(const System::Path & Path, ClassGen::ClassInfo & ClassInfo);
    virtual void RenderFile();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
