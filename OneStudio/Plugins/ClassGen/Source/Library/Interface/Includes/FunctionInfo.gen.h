#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Function.gen.h"
#include "FunctionAttributes.gen.h"
#include "Foundation"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct FunctionInfo : public LegacyClassGen::Function
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FunctionInfo This;
    typedef LegacyClassGen::Function Super;
    typedef void Interfaces;
public:
    LegacyClassGen::FunctionAttributes Attributes;
    Array<String> ExecutionBranches;
    Boolean Callable;
public:
    FunctionInfo();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
