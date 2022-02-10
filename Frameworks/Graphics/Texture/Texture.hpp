#pragma once

namespace Graphics
{
struct Texture
{
    using This = Texture;
    InplaceStorage<TexturePrivateData, 8, 8> Data;
    Array<uint8_t> Buffer = {};
    Int3 Size = {};
    uint8_t Channels = {};
    Graphics::TextureFiltration Filtration = {};
    Graphics::TextureWrapping Wrapping = {};
    bool IsCompiled = {};
    Texture();
    Texture(Texture &&other);
    Texture &operator =(Texture &&other);

     ~Texture();
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
}
