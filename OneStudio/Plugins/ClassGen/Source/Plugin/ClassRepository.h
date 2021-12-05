#pragma once

#include <Experimental>

#include "ClassDataInstance.h"

namespace LegacyClassGen
{

struct ClassRepository : public ASingleton<ClassRepository>
{
    Map<String, SharedReference<ClassDataInstance>> indexedTypes;
};

}
