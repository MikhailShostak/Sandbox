/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include "Graphics/AMaterial.h"
#include "Includes/Texture.gen.h"

#include "Materials/ModelMaterial.g.h"

namespace UI
{

struct LabelMaterialData : public Legacy::Graphics::ModelMaterial
{
    ::SharedReference<Legacy::Graphics::Texture> TextMask;
    AColor Color = AColor::WhiteColor();
};

class LabelMaterial : public Legacy::Graphics::ModelMaterial
{
    typedef Legacy::Graphics::ModelMaterial Super;
    typedef LabelMaterial This;
public:
    ::SharedReference<Legacy::Graphics::Texture> TextMask;
    AColor Color = AColor::WhiteColor();
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
         return Super::generateProperties() + R"(uniform sampler2D TextMask;uniform vec4 Color;)";
    }
    String generateVertexPosition() const override { return R"(vPosition = Position;
vUV = UV;
return ModelViewProjectionMatrix * vec4(Position, 1.0);)"; }

    String generateFragmentColor() const override { return R"(return Color * texture2D(TextMask, vUV).r;)"; }


    void apply() const override
    {
        Super::apply();
        if(TextMask) getHandle()->setTexture("TextMask", TextMask.get());
        getHandle()->setFloatVector4D("Color", Color.data());
    }

};

DeclareDynamicMaterial(LabelMaterial, LabelMaterialData)
{
    getMaterial().ModelViewProjectionMatrix = data.ModelViewProjectionMatrix;
    getMaterial().TextMask = data.TextMask;
    getMaterial().Color = data.Color;
    getMaterial().apply();
}

}
