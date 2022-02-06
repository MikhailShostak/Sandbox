#pragma once

namespace ClassGen
{
struct ParticleSystemInfo
    : public ClassGen::BaseInfo
{
    using This = ParticleSystemInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};

    virtual ~ParticleSystemInfo() {}
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
