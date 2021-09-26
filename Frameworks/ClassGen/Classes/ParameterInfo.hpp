#pragma once

namespace ClassGen
{
struct ParameterInfo
{
    using This = ParameterInfo;
    ClassGen::TypeInfo Type;
    std::string Name;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
    }
};
}
