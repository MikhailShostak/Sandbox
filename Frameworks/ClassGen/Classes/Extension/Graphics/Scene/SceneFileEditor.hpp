#pragma once

namespace ClassGen
{
struct SceneFileEditor
    : public ClassGen::FileEditor
{
    using This = SceneFileEditor;
    using Super = ClassGen::FileEditor;
    SceneViewport Viewport = {};
    Map<String, SharedReference<ECS::System>> SystemInstances = {};
    ClassGen::ArrayPropertyEditor SystemDataEditor = {};
    ClassGen::ArrayPropertyEditor ComponentDataEditor = {};
    ClassGen::ObjectPropertyEditor DataEditor = {};
    bool Outdated = {};
    ClassGen::ObjectPropertyEditor SimulationDataEditor = {};
    bool Simulation = {};

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
