#pragma once

namespace Graphics
{
struct TextureSampler
{
    using This = TextureSampler;
    String Name;
    SharedReference<Graphics::Texture> Texture;
    ShaderFlags Flags;
    TextureSampler();

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
