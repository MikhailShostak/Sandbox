#pragma once

namespace ClassGen
{
struct Int4PropertyEditor
    : public ClassGen::ValuePropertyEditor<Int4>
{
    using This = Int4PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Int4>;

    virtual ~Int4PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
