#pragma once

namespace ClassGen
{
struct TextureInfo
    : public ClassGen::BaseInfo
{
    using This = TextureInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};
    Graphics::TextureFiltration TextureFiltration = {};
    Graphics::TextureWrapping TextureWrapping = {};
    SharedReference<Graphics::Texture> TextureInstance = {};

    virtual ~TextureInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
        data["TextureFiltration"] & TextureFiltration;
        data["TextureWrapping"] & TextureWrapping;
    }
    virtual SharedReference<Graphics::Texture>/*Texture*/ Load(Graphics::GraphicsContext & Context);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
