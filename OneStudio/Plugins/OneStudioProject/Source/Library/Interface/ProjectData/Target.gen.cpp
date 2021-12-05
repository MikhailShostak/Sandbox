//CLASSGEN GENERATED REGION: Includes
#include "Target.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Target::Target()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Target::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("Run", toJSONValue(Run));
    object.insert("Actions", toJSONValue(Actions));
    object.insert("Settings", toJSONValue(Settings));
}
void Target::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("Run", value);
    fromJSONValue(value, Run);
    value = AJSONValue();
    object.read("Actions", value);
    fromJSONValue(value, Actions);
    value = AJSONValue();
    object.read("Settings", value);
    fromJSONValue(value, Settings);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
