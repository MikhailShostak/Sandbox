#pragma once

namespace ClassGen
{
struct Float4PropertyEditor
    : public ClassGen::ValuePropertyEditor<Float4>
{
    using This = Float4PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Float4>;

    virtual ~Float4PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
