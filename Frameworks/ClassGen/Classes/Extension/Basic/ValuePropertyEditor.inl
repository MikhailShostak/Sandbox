#pragma once

namespace ClassGen
{

template<typename ValueType>
inline void ValuePropertyEditor<ValueType>::SerializeProperty(Serialization::Data& Data)
{
    Data = Serialization::Serialize(Value);
}

template<typename ValueType>
inline void ValuePropertyEditor<ValueType>::DeserializeProperty(const Serialization::Data& Data)
{
    Value = Serialization::Deserialize<ValueType>(Data);
}

template<typename ValueType>
inline void ValuePropertyEditor<ValueType>::Clear()
{
    Value = ValueType();
}

}
