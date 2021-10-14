#pragma once

namespace ClassGen
{
struct TypeInfo
{
    using This = TypeInfo;
    String Name;
    Array<ClassGen::TypeInfo> Parameters;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["Parameters"] & Parameters;
    }
};
}
