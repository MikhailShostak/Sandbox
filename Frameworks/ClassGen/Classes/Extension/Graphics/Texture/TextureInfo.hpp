#pragma once

namespace ClassGen
{
struct TextureInfo
    : public ClassGen::BaseInfo
{
    using This = TextureInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};
    SharedReference<Graphics::Texture> TextureInstance = {};

    virtual ~TextureInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
    }
    virtual SharedReference<Graphics::Texture>/*Texture*/ Load(Graphics::GraphicsContext & Context);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
