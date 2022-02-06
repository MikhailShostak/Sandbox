#pragma once

namespace ClassGen
{
struct AnimationInfo
    : public ClassGen::BaseInfo
{
    using This = AnimationInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};

    virtual ~AnimationInfo() {}
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
