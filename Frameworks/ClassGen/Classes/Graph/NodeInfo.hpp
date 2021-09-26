#pragma once

namespace ClassGen
{
struct NodeInfo
{
    using This = NodeInfo;
    std::string ID;
    std::string Name;

    virtual ~NodeInfo() {}

    template<typename T>
    void Serialize(T &&data)
    {
        data["ID"] & ID;
        data["Name"] & Name;
    }
};
}
