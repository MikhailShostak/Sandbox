#pragma once

namespace ClassGen
{
struct SceneInfo
    : public ClassGen::BaseInfo
{
    using This = SceneInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};
    String Name = {};
    Array<InstanceInfo> Systems = {};
    Array<ClassGen::EntityInfo> Entities = {};

    virtual ~SceneInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
        data["Name"] & Name;
        data["Systems"] & Systems;
        data["Entities"] & Entities;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
