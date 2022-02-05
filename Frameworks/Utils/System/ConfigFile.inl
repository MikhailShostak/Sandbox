#pragma once

namespace System
{
template<typename Type>
inline Type* ConfigFile<Type>::GetIndirectValue()
{
    return &Data;
}

template<typename Type>
inline bool ConfigFile<Type>::Load()
{
    return Serialization::FromFile(Path, Data);
}

template<typename Type>
inline bool ConfigFile<Type>::Save()
{
    return Serialization::ToFile(Data, Path);
}
}
