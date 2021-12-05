//CLASSGEN GENERATED REGION: Includes
#include "ClassContext.gen.h"
//CLASSGEN END REGION
#include "BaseCGType.h"
#include "ClassManager.h"
#include "PropertyInfo.gen.h"
#include "FunctionInfo.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ClassContext::ClassContext()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ClassContext::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ClassContext::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
