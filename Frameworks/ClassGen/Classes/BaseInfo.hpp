#pragma once

namespace ClassGen
{
struct BaseInfo
{
    using This = BaseInfo;
    std::string Namespace;

    virtual ~BaseInfo() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["Namespace"] & Namespace;
    }
};
}
