/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include "Graphics/AMaterial.h"
#include "Includes/Texture.gen.h"

#include "Materials/ModelMaterial.g.h"

namespace UI
{

struct ImageMaterialData : public Legacy::Graphics::ModelMaterialData
{
    ::SharedReference<Legacy::Graphics::Texture> Image;
    Math::Vector ClippingTopLeft;
    Math::Vector ClippingBottomRight;
    Math::Vector ImageOffset;
    AColor Color = AColor::WhiteColor();
    Math::Vector ImageScale;
};

class ImageMaterial : public Legacy::Graphics::ModelMaterial
{
    typedef Legacy::Graphics::ModelMaterial Super;
    typedef ImageMaterial This;
public:
    ::SharedReference<Legacy::Graphics::Texture> Image;
    Math::Vector ClippingTopLeft;
    Math::Vector ClippingBottomRight;
    Math::Vector ImageOffset;
    AColor Color = AColor::WhiteColor();
    Math::Vector ImageScale;

    const Array<const char *> &getMeshLayout() const override
    {
         static Array<const char *> layout = {
            "Position",
            "Normal",
            "UV",
         };
         return layout;
    }
    String generateProperties() const override
    {
         return Super::generateProperties() + R"(uniform sampler2D Image;uniform vec2 ClippingTopLeft;uniform vec2 ClippingBottomRight;uniform vec2 ImageOffset;uniform vec4 Color;uniform vec2 ImageScale;)";
    }
    String generateVertexPosition() const override { return R"(vPosition = Position;
vUV = UV;
return ModelViewProjectionMatrix * vec4(Position, 1.0);)"; }

    String generateFragmentColor() const override { return R"(if(vUV.x < ClippingTopLeft.x || (ClippingBottomRight.x) < vUV.x  || vUV.y < ClippingTopLeft.y || (ClippingBottomRight.y) < vUV.y)
discard;
return texture2D(Image, (vUV * ImageScale) + ImageOffset) * Color;)"; }

    void apply() const override
    {
        Super::apply();
        if(Image) getHandle()->setTexture("Image", Image.get());
        getHandle()->setFloatVector2D("ClippingTopLeft", &ClippingTopLeft.x);
        getHandle()->setFloatVector2D("ClippingBottomRight", &ClippingBottomRight.x);
        getHandle()->setFloatVector2D("ImageOffset", &ImageOffset.x);
        getHandle()->setFloatVector4D("Color", Color.data());
        getHandle()->setFloatVector2D("ImageScale", &ImageScale.x);
    }

};

DeclareDynamicMaterial(ImageMaterial, ImageMaterialData)
{
    getMaterial().ModelViewProjectionMatrix = data.ModelViewProjectionMatrix;
    getMaterial().Image = data.Image;
    getMaterial().ClippingTopLeft = data.ClippingTopLeft;
    getMaterial().ClippingBottomRight = data.ClippingBottomRight;
    getMaterial().ImageOffset = data.ImageOffset;
    getMaterial().Color = data.Color;
    getMaterial().ImageScale = data.ImageScale;
    getMaterial().apply();
}

}
