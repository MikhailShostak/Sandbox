#pragma once

namespace ClassGen
{
struct ParameterInfo
{
    using This = ParameterInfo;
    ClassGen::TypeInfo Type;
    String Name;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
    }
};
}
