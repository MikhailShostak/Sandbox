#pragma once

namespace ClassGen
{
struct PropertyInfo
{
    using This = PropertyInfo;
    ClassGen::TypeInfo Type;
    std::string Name;
    std::vector<std::string> Attributes;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
        data["Attributes"] & Attributes;
    }
};
}
