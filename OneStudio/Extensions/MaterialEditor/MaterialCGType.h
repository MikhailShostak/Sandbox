#pragma once

#include "Core/BaseCGType.h"
#include "Includes/TextureCompilation.gen.h"

namespace LegacyClassGen
{

class MaterialCGType : public BaseCGType
{
public:

    String getBaseType() const override
    {
        return "Graphics.Material";
    }

    void generate() override
    {
        //TODO: implement
    }
};

}
