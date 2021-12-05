//CLASSGEN GENERATED REGION: Includes
#include "LinkageSettings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioCLanguage
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
LinkageSettings::LinkageSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void LinkageSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Libraries", toJSONValue(Libraries));
    object.insert("LibraryPaths", toJSONValue(LibraryPaths));
    object.insert("Frameworks", toJSONValue(Frameworks));
}
void LinkageSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Libraries", value);
    fromJSONValue(value, Libraries);
    value = AJSONValue();
    object.read("LibraryPaths", value);
    fromJSONValue(value, LibraryPaths);
    value = AJSONValue();
    object.read("Frameworks", value);
    fromJSONValue(value, Frameworks);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
