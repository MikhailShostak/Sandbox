/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include "Graphics/AMaterial.h"
#include "Includes/Texture.gen.h"
#include "Materials/ModelMaterial.g.h"


namespace Legacy::Graphics
{

class PBRMaterial : public ModelMaterial
{
    typedef ModelMaterial Super;
    typedef PBRMaterial This;
public:
    ::SharedReference<Graphics::Texture> ColorMap;
    ::SharedReference<Graphics::Texture> NormalMap;
    AColor BaseColor = AColor::WhiteColor();
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
         return Super::generateProperties() + R"(uniform sampler2D ColorMap;uniform sampler2D NormalMap;uniform vec4 BaseColor;)";
    }
    String generateVertexPosition() const override { return R"(vPosition = Position;
vNormal = normalize(Normal);
vUV = UV;
return ModelViewProjectionMatrix * vec4(Position, 1.0);)"; }

    String generateFragmentColor() const override { return R"(vec3 pos = vec3(0.0, 1.0, 0.0);
float radius = 10.0;

vec3 ambient = vec3(0.2);

float diffuse = max(dot(pos - vPosition, vNormal), 0.0);
float attenuation = max(1.0 -  length(pos - vPosition) / radius, 0.0);

vec4 color = texture2D(ColorMap, vUV) * BaseColor;
return vec4(color.rgb * (ambient + attenuation * diffuse), color.a);)"; }


    void apply() const override
    {
        Super::apply();
        if(ColorMap) getHandle()->setTexture("ColorMap", ColorMap.get());
        if(NormalMap) getHandle()->setTexture("NormalMap", NormalMap.get());
        getHandle()->setFloatVector4D("BaseColor", BaseColor.data());
    }

};

}
