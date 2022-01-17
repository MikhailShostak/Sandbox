#pragma once

namespace ClassGen
{
template<typename ValueType>
struct ValuePropertyEditor
    : public ClassGen::PropertyEditor
{
    using This = ValuePropertyEditor;
    using Super = ClassGen::PropertyEditor;
    ValueType Value;

    virtual ~ValuePropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Serialize(Serialization::Data & Data);
    virtual void Deserialize(const Serialization::Data & Data);
};
}
