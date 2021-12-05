//CLASSGEN GENERATED REGION: Includes
#include "ExtensionDescription.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ExtensionDescription::ExtensionDescription()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionDescription::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Interface", toJSONValue(Interface));
    object.insert("Implementation", toJSONValue(Implementation));
    object.insert("Package", toJSONValue(Package));
    object.insert("Version", toJSONValue(Version));
    object.insert("Revision", toJSONValue(Revision));
}
void ExtensionDescription::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Interface", value);
    fromJSONValue(value, Interface);
    value = AJSONValue();
    object.read("Implementation", value);
    fromJSONValue(value, Implementation);
    value = AJSONValue();
    object.read("Package", value);
    fromJSONValue(value, Package);
    value = AJSONValue();
    object.read("Version", value);
    fromJSONValue(value, Version);
    value = AJSONValue();
    object.read("Revision", value);
    fromJSONValue(value, Revision);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
