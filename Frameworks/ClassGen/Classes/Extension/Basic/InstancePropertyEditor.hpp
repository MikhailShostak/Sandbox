#pragma once

namespace ClassGen
{
struct InstancePropertyEditor
    : public ClassGen::ValuePropertyEditor<ClassGen::InstanceInfo>
{
    using This = InstancePropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<ClassGen::InstanceInfo>;
    SharedReference<Graphics::Texture> PreviewTexture = {};
    ClassGen::ObjectPropertyEditor ValuesEditor = {};

    virtual ~InstancePropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
