#pragma once

namespace ClassGen
{
struct SceneFileEditor
    : public ClassGen::FileEditor
{
    using This = SceneFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Scene> Scene = {};
    System::Path LastPath = {};

    virtual ~SceneFileEditor() {}
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
