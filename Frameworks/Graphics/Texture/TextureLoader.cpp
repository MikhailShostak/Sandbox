#include <stb_image.h>

namespace Graphics
{

SharedReference<Graphics::Texture> CreateTextureBuffer(const Int3& size)
{
    SharedReference<Graphics::Texture> texture = CreateShared<Graphics::Texture>();
    texture->Size = size;
    texture->Channels = 4;

    size_t s = texture->Size.x * texture->Size.y * texture->Size.z * texture->Channels;
    texture->Buffer.resize(s);

    return texture;
}

SharedReference<Graphics::Texture> CreateTexture(const Color& color, const Int3& size)
{
    SharedReference<Graphics::Texture> texture = CreateTextureBuffer(size);

    Color colorBytes = color * std::numeric_limits<uint8_t>::max();
    for (size_t i = 0; i < texture->Buffer.size(); i += texture->Channels)
    {
        texture->Buffer[i] = colorBytes.r;
        texture->Buffer[i + 1] = colorBytes.g;
        texture->Buffer[i + 2] = colorBytes.b;
        texture->Buffer[i + 3] = colorBytes.a;
    }

    return texture;
}

void LoadTexture(Graphics::Texture& texture, const System::Path& path)
{
    int width, height, channels;
    unsigned char* data = stbi_load(path.string().data(), &width, &height, &channels, 0);

    texture.Size.x = width;
    texture.Size.y = height;
    texture.Channels = channels;
    if (texture.Channels == 3)
    {
        texture.Channels = 4;
        size_t originalSize = width * height * channels;
        size_t newSize = width * height * texture.Channels;
        texture.Buffer.resize(newSize);
        size_t i = 0;
        size_t j = 0;
        while (i < originalSize)
        {
            texture.Buffer[j] = data[i];
            texture.Buffer[j + 1] = data[i + 1];
            texture.Buffer[j + 2] = data[i + 2];
            texture.Buffer[j + 3] = std::numeric_limits<std::remove_reference_t<decltype(texture.Buffer[j + 3])>>::max();
            i += channels;
            j += texture.Channels;
        }
    }
    else
    {
        texture.Buffer = Array<uint8_t>(data, data + width * height * channels);
    }
}

SharedReference<Graphics::Texture> LoadTexture(const System::Path &path)
{
    SharedReference<Graphics::Texture> texture = CreateShared<Graphics::Texture>();
    LoadTexture(*texture, path);
    return texture;
}

void SaveTexture(const Graphics::Texture &texture, const System::Path &path)
{

}

}
