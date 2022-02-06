#pragma once

namespace ClassGen
{
struct TextureInfo
    : public ClassGen::BaseInfo
{
    using This = TextureInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};

    virtual ~TextureInfo() {}
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
