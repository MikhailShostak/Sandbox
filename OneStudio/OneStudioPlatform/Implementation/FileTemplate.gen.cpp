//CLASSGEN GENERATED REGION: Includes
#include "FileTemplate.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FileTemplate::FileTemplate()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FileTemplate::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("Description", toJSONValue(Description));
    object.insert("Extensions", toJSONValue(Extensions));
}
void FileTemplate::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("Description", value);
    fromJSONValue(value, Description);
    value = AJSONValue();
    object.read("Extensions", value);
    fromJSONValue(value, Extensions);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
