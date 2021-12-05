#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExtensionContext.gen.h"
#include "Foundation"
#include "ExtensionDependency.gen.h"
#include "Task.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Extension
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Extension This;
    typedef void Super;
    typedef void Interfaces;
public:
    virtual ~Extension(){}
    virtual OneStudioPlatform::ExtensionContext getContext() const = 0;
    virtual Array<OneStudioPlatform::ExtensionDependency> getDependencies() const = 0;
    virtual UnorderedDictionary<String, OneStudioPlatform::ExtensionContext> /*SubTask*/ load() = 0;
    virtual SharedReference<OneStudioPlatform::Task> /*SubTask*/ unload() = 0;
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
