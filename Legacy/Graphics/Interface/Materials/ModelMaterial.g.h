/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include "Graphics/AMaterial.h"
#include "Includes/Texture.gen.h"

namespace Legacy::Graphics
{

struct ModelMaterialData
{
    Math::Matrix ModelViewProjectionMatrix;
};

class ModelMaterial : public Material
{
    typedef Material Super;
    typedef ModelMaterial This;
public:
    Math::Matrix ModelViewProjectionMatrix;
    String generateProperties() const override
    {
         return Super::generateProperties() + R"(uniform mat4 ModelViewProjectionMatrix;)";
    }
    String generateVertexPosition() const override { return R"(vPosition = Position;
return ModelViewProjectionMatrix * vec4(Position, 1.0);)"; }

    String generateFragmentColor() const override { return R"(return vec4(1.0, 1.0, 1.0, 1.0);)"; }

    void apply() const override
    {
        Super::apply();
        getHandle()->setMatrix("ModelViewProjectionMatrix", ModelViewProjectionMatrix);
    }

};

DeclareDynamicMaterial(ModelMaterial, ModelMaterialData)
{
    getMaterial().ModelViewProjectionMatrix = data.ModelViewProjectionMatrix;
    getMaterial().apply();
}

}
