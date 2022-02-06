#pragma once

namespace ClassGen
{
struct MeshInfo
    : public ClassGen::BaseInfo
{
    using This = MeshInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};

    virtual ~MeshInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
