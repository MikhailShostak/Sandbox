//CLASSGEN GENERATED REGION: Includes
#include "ExtensionDependency.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ExtensionDependency::ExtensionDependency()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionDependency::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Package", toJSONValue(Package));
    object.insert("Version", toJSONValue(Version));
}
void ExtensionDependency::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Package", value);
    fromJSONValue(value, Package);
    value = AJSONValue();
    object.read("Version", value);
    fromJSONValue(value, Version);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
