#pragma once

namespace ClassGen
{
struct GraphInfo
{
    using This = GraphInfo;
    std::vector<ClassGen::NodeInfo> Nodes;
    std::vector<ClassGen::ConnectionInfo> Connections;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Nodes"] & Nodes;
        data["Connections"] & Connections;
    }
};
}
