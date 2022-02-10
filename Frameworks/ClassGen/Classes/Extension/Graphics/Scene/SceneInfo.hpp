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

    virtual ~SceneInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
        data["Name"] & Name;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
