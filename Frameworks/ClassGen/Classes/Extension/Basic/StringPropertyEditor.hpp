#pragma once

namespace ClassGen
{
struct StringPropertyEditor
    : public ClassGen::ValuePropertyEditor<String>
{
    using This = StringPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<String>;

    virtual ~StringPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
