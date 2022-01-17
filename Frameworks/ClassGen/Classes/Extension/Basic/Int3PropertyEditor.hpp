#pragma once

namespace ClassGen
{
struct Int3PropertyEditor
    : public ClassGen::ValuePropertyEditor<Int3>
{
    using This = Int3PropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Int3>;

    virtual ~Int3PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
