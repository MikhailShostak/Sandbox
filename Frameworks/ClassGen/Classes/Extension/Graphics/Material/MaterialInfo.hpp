#pragma once

namespace ClassGen
{
struct MaterialInfo
    : public ClassGen::BaseInfo
{
    using This = MaterialInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};

    virtual ~MaterialInfo() {}
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
