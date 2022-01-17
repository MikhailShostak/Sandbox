#pragma once

namespace ClassGen
{
struct PropertyEditor
{
    using This = PropertyEditor;
    String ID;

    virtual ~PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Serialize(Serialization::Data & Data);
    virtual void Deserialize(const Serialization::Data & Data);
    virtual void Draw();
};
}
