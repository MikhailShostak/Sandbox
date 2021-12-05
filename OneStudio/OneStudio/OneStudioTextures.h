#pragma once

#include <Graphics/Texture.h>

#include "TextureAsset.h"

//CLASSGEN GENERATED REGION: LightBegin
//CLASSGEN END REGION
Array<uint8_t> GetLight_TextureData();
//CLASSGEN GENERATED REGION: LightHeader
struct Light_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: LightBody
operator SharedReference<Legacy::Graphics::Texture>() const
{
    static WeakReference<Legacy::Graphics::Texture> cachedTextureWeak;
    auto cachedTexture = cachedTextureWeak.lock();
    if (!cachedTexture)
    {
        SharedReference<Legacy::Graphics::Texture> texture = load(GetLight_TextureData());
        cachedTexture = texture;
        cachedTexture->setFiltration(Legacy::Graphics::TextureFiltration::Bilinear);
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Light_TextureAsset Light;
//CLASSGEN GENERATED REGION: LightEnd
//CLASSGEN END REGION
