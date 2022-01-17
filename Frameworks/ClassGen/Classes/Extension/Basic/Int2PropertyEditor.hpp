#pragma once

namespace ClassGen
{
struct Int2PropertyEditor
    : public ClassGen::ValuePropertyEditor<Int2>
{
    using This = Int2PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Int2>;

    virtual ~Int2PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
