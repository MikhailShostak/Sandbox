#pragma once

namespace ClassGen
{

SharedReference<Graphics::Texture>/*Texture*/ TextureInfo::Load(Graphics::GraphicsContext &context)
{
    if (TextureInstance)
    {
        return TextureInstance;
    }

    if (!System::IsRegularFile(Path))
    {
        TextureInstance = nullptr;
        return TextureInstance;
    }

    TextureInstance = Graphics::LoadTexture(Path);
    TextureInstance->Filtration = TextureFiltration;
    TextureInstance->Wrapping = TextureWrapping;
    return TextureInstance;
}

}
