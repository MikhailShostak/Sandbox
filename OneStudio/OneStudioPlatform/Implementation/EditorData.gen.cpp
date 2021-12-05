//CLASSGEN GENERATED REGION: Includes
#include "EditorData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EditorData::EditorData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EditorData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Identifier", toJSONValue(Identifier));
    object.insert("SuppoertedTypes", toJSONValue(SuppoertedTypes));
}
void EditorData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Identifier", value);
    fromJSONValue(value, Identifier);
    value = AJSONValue();
    object.read("SuppoertedTypes", value);
    fromJSONValue(value, SuppoertedTypes);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
