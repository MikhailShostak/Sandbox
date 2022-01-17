#pragma once

namespace ClassGen
{

template<typename ValueType>
inline void ValuePropertyEditor<ValueType>::Serialize(Serialization::Data& Data)
{
    Data = Serialization::Serialize(Value);
}

template<typename ValueType>
inline void ValuePropertyEditor<ValueType>::Deserialize(const Serialization::Data& Data)
{
    Value = Serialization::Deserialize<ValueType>(Data);
}

}
