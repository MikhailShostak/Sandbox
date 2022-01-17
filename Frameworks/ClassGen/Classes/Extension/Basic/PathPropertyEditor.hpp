#pragma once

namespace ClassGen
{
struct PathPropertyEditor
    : public ClassGen::ValuePropertyEditor<System::Path>
{
    using This = PathPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<System::Path>;

    virtual ~PathPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();
};
}
