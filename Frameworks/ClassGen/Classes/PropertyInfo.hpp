#pragma once

namespace ClassGen
{
struct PropertyInfo
{
    using This = PropertyInfo;
    ClassGen::TypeInfo Type;
    String Name;
    Array<String> Attributes;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
        data["Attributes"] & Attributes;
    }
};
}
