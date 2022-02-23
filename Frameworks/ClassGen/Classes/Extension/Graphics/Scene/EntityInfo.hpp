#pragma once

namespace ClassGen
{
struct EntityInfo
{
    using This = EntityInfo;
    String Name = {};
    Array<ClassGen::InstanceInfo> Components = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["Components"] & Components;
    }

    void Initialize()
    {
    }
};
}
