#pragma once

namespace ClassGen
{
struct ParameterInfo
{
    using This = ParameterInfo;
    ClassGen::TypeInfo Type;
    String Name;
    bool Writable = false;
    bool Copy = false;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
        data["Writable"] & Writable;
        data["Copy"] & Copy;
    }
};
}
