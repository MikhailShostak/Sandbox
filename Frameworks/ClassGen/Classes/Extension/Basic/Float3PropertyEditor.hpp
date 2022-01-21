#pragma once

namespace ClassGen
{
struct Float3PropertyEditor
    : public ClassGen::ValuePropertyEditor<Float3>
{
    using This = Float3PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Float3>;

    virtual ~Float3PropertyEditor() {}
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
