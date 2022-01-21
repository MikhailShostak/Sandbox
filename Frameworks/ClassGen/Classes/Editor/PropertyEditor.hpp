#pragma once

namespace ClassGen
{
struct PropertyEditor
{
    using This = PropertyEditor;
    String ID = {};
    ClassGen::FileInfo TypeInfo = {};

    virtual ~PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    Meta::Function<void> Changed;
    virtual void Serialize(Serialization::Data & Data);
    virtual void Deserialize(const Serialization::Data & Data);
    virtual void DrawLabel(const String & Name);
    virtual void Draw();
    virtual void Clear();

    void Initialize()
    {
    }
};
}
