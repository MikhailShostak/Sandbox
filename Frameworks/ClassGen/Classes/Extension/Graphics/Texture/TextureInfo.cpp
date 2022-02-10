#pragma once

namespace ClassGen
{

SharedReference<Graphics::Texture>/*Texture*/ TextureInfo::Load(Graphics::GraphicsContext &context)
{
    if (TextureInstance)
    {
        return TextureInstance;
    }

    TextureInstance = Graphics::LoadTexture(Path);
    TextureInstance->Wrapping = Graphics::TextureWrapping::TiledWrapping;
    context.Create2DTexture(*TextureInstance);

    return TextureInstance;
}

}
