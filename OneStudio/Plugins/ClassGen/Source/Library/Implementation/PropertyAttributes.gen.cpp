//CLASSGEN GENERATED REGION: Includes
#include "PropertyAttributes.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Implementation
AStaticRun(PropertyAttributes)
{
    MetaObjectInformation::getInstance().flags.insert({ AMeta::getStaticTypeHash<PropertyAttributes>(), {"ClassGen.PropertyAttributes", { "ReadOnly", "Abstract", "Replicated", "Serialized", "Mapped" } } });
}
PropertyAttributes::PropertyAttributes()
{
    LinkStaticRun(PropertyAttributes);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
