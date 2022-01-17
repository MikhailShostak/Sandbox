#pragma once

namespace ClassGen
{
struct Float2PropertyEditor
    : public ClassGen::ValuePropertyEditor<Float2>
{
    using This = Float2PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Float2>;

    virtual ~Float2PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
