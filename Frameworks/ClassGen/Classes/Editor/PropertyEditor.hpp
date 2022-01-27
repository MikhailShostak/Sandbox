#pragma once

namespace ClassGen
{
struct PropertyEditor
{
    using This = PropertyEditor;
    String ID = {};
    ClassGen::TypeInfo TypeInfo = {};
    ClassGen::FileInfo FileInfo = {};

    virtual ~PropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    Meta::Function<void> Changed;
    virtual void SerializeProperty(Serialization::Data & Data);
    virtual void DeserializeProperty(const Serialization::Data & Data);
    virtual void DrawLabel(const String & Name);
    virtual void Draw();
    virtual void Clear();

    void Initialize()
    {
    }
};
}
