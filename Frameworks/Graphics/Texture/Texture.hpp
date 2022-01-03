#pragma once

namespace Graphics
{
struct Texture
{
    using This = Texture;
    InplaceStorage<TexturePrivateData, 8, 8> Data;
    Array<uint8_t> Buffer;
    hlslpp::int3 Size;
    uint8_t Channels;
    Graphics::TextureFiltration Filtration;
    Graphics::TextureWrapping Wrapping;
    Texture();

     ~Texture();
    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
