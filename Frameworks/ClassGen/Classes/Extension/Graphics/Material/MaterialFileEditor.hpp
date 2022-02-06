#pragma once

namespace ClassGen
{
struct MaterialFileEditor
    : public ClassGen::FileEditor
{
    using This = MaterialFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Material> Material = {};
    System::Path LastPath = {};

    virtual ~MaterialFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
