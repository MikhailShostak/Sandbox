//CLASSGEN GENERATED REGION: Includes
#include "TransitionData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TransitionData::TransitionData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TransitionData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Event", toJSONValue(Event));
    object.insert("TranstionType", toJSONValue(TranstionType));
}
void TransitionData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Event", value);
    fromJSONValue(value, Event);
    value = AJSONValue();
    object.read("TranstionType", value);
    fromJSONValue(value, TranstionType);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
