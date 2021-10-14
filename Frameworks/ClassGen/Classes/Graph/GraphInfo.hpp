#pragma once

namespace ClassGen
{
struct GraphInfo
{
    using This = GraphInfo;
    Array<ClassGen::NodeInfo> Nodes;
    Array<ClassGen::ConnectionInfo> Connections;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Nodes"] & Nodes;
        data["Connections"] & Connections;
    }
};
}
