//CLASSGEN GENERATED REGION: Includes
#include "EventInfo.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EventInfo::EventInfo()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EventInfo::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("BaseType", toJSONValue(BaseType));
    object.insert("InputArguments", toJSONValue(InputArguments));
}
void EventInfo::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("BaseType", value);
    fromJSONValue(value, BaseType);
    value = AJSONValue();
    object.read("InputArguments", value);
    fromJSONValue(value, InputArguments);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
