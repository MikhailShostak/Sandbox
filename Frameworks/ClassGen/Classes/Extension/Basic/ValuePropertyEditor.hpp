#pragma once

namespace ClassGen
{
template<typename ValueType>
struct ValuePropertyEditor
    : public ClassGen::PropertyEditor
{
    using This = ValuePropertyEditor;
    using Super = ClassGen::PropertyEditor;
    ValueType Value = {};

    virtual ~ValuePropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void SerializeProperty(Serialization::Data & Data);
    virtual void DeserializeProperty(const Serialization::Data & Data);
    virtual void Clear();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
