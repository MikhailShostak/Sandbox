//CLASSGEN GENERATED REGION: Includes
#include "EventSet.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EventSet::EventSet()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EventSet::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Events", toJSONValue(Events));
}
void EventSet::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Events", value);
    fromJSONValue(value, Events);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
