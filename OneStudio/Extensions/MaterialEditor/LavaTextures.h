#pragma once

#include <Graphics/Texture.h>

#include "TextureAsset.h"

//CLASSGEN GENERATED REGION: Lava_005_DISPBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_DISP_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_DISPHeader
struct Lava_005_DISP_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_DISPBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_DISP_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_DISP_TextureAsset Lava_005_DISP;
//CLASSGEN GENERATED REGION: Lava_005_DISPEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Lava_005_MASKBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_MASK_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_MASKHeader
struct Lava_005_MASK_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_MASKBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_MASK_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_MASK_TextureAsset Lava_005_MASK;
//CLASSGEN GENERATED REGION: Lava_005_MASKEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Lava_005_COLORBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_COLOR_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_COLORHeader
struct Lava_005_COLOR_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_COLORBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_COLOR_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_COLOR_TextureAsset Lava_005_COLOR;
//CLASSGEN GENERATED REGION: Lava_005_COLOREnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Lava_005_NORMBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_NORM_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_NORMHeader
struct Lava_005_NORM_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_NORMBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_NORM_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_NORM_TextureAsset Lava_005_NORM;
//CLASSGEN GENERATED REGION: Lava_005_NORMEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Lava_005_OCCBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_OCC_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_OCCHeader
struct Lava_005_OCC_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_OCCBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_OCC_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_OCC_TextureAsset Lava_005_OCC;
//CLASSGEN GENERATED REGION: Lava_005_OCCEnd
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Lava_005_ROUGHBegin
//CLASSGEN END REGION
Array<uint8_t> GetLava_005_ROUGH_TextureData();
//CLASSGEN GENERATED REGION: Lava_005_ROUGHHeader
struct Lava_005_ROUGH_TextureAsset : public TextureAsset
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: Lava_005_ROUGHBody
operator SharedReference<Graphics::Texture>() const
{
    static AWeakPointer<Graphics::Texture> cachedTexture;
    if (!cachedTexture)
    {
        SharedReference<Graphics::Texture> texture = load(GetLava_005_ROUGH_TextureData());
        cachedTexture = texture;
        cachedTexture->load();
        return texture;
    }
    return cachedTexture;
}
//CLASSGEN END REGION
};
constexpr static Lava_005_ROUGH_TextureAsset Lava_005_ROUGH;
//CLASSGEN GENERATED REGION: Lava_005_ROUGHEnd
//CLASSGEN END REGION
