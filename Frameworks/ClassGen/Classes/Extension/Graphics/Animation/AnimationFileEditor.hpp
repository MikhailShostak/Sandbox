#pragma once

namespace ClassGen
{
struct AnimationFileEditor
    : public ClassGen::FileEditor
{
    using This = AnimationFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Mesh> Animation = {};
    System::Path LastPath = {};

    virtual ~AnimationFileEditor() {}
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
