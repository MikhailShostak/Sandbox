#pragma once

namespace ClassGen
{
struct AssetFileEditor
    : public ClassGen::FileEditor
{
    using This = AssetFileEditor;
    using Super = ClassGen::FileEditor;
    ClassGen::ObjectPropertyEditor DataEditor = {};

    virtual ~AssetFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderDetails(const System::Path & Path, ClassGen::AssetInfo & AssetInfo);
    virtual void RenderData(const System::Path & Path, ClassGen::AssetInfo & AssetInfo);
    virtual void RenderFile();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
