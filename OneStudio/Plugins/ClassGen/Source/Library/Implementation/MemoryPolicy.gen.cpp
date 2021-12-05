//CLASSGEN GENERATED REGION: Includes
#include "MemoryPolicy.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Implementation
AStaticRun(MemoryPolicy)
{
    MetaObjectInformation::getInstance().enums.insert({ AMeta::getStaticTypeHash<MemoryPolicy>(), { "ClassGen.MemoryPolicy", { "Embedded", "Shared", "Referenced" } } });
}
MemoryPolicy::MemoryPolicy()
{
    LinkStaticRun(MemoryPolicy);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
