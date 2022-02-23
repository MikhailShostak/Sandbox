#pragma once

namespace ClassGen
{
struct TextureFileEditor
    : public ClassGen::FileEditor
{
    using This = TextureFileEditor;
    using Super = ClassGen::FileEditor;
    ClassGen::EnumerationPropertyEditor FiltrationEditor = {};
    ClassGen::EnumerationPropertyEditor WrappingEditor = {};
    SharedReference<Graphics::Texture> Texture = {};
    System::Path LastPath = {};
    Float2 Zoom = {};

    virtual ~TextureFileEditor() {}
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
