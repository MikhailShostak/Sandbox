#pragma once

namespace ClassGen
{
struct IntPropertyEditor
    : public ClassGen::ValuePropertyEditor<int>
{
    using This = IntPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<int>;

    virtual ~IntPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
