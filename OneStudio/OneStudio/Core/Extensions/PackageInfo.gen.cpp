//CLASSGEN GENERATED REGION: Includes
#include "PackageInfo.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Data>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PackageInfo::PackageInfo()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PackageInfo::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PackageInfo::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
