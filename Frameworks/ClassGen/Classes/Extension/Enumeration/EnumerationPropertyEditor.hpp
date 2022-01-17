#pragma once

namespace ClassGen
{
struct EnumerationPropertyEditor
    : public ClassGen::ValuePropertyEditor<String>
{
    using This = EnumerationPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<String>;

    virtual ~EnumerationPropertyEditor() {}
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
