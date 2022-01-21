#pragma once

namespace ClassGen
{
struct BooleanPropertyEditor
    : public ClassGen::ValuePropertyEditor<bool>
{
    using This = BooleanPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<bool>;

    virtual ~BooleanPropertyEditor() {}
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
