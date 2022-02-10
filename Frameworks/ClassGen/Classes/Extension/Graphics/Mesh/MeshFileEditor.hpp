#pragma once

namespace ClassGen
{
struct MeshFileEditor
    : public ClassGen::FileEditor
{
    using This = MeshFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Mesh> Mesh = {};
    System::Path LastPath = {};
    ClassGen::PreviewViewport PreviewViewport = {};

    virtual ~MeshFileEditor() {}
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
