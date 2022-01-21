#pragma once

namespace ClassGen
{
struct NodeInfo
{
    using This = NodeInfo;
    String ID = {};
    String Name = {};

    virtual ~NodeInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["ID"] & ID;
        data["Name"] & Name;
    }

    void Initialize()
    {
    }
};
}
