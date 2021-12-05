//CLASSGEN GENERATED REGION: Includes
#include "ConditionalTransitionData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ConditionalTransitionData::ConditionalTransitionData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ConditionalTransitionData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Condition", toJSONValue(Condition));
}
void ConditionalTransitionData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Condition", value);
    fromJSONValue(value, Condition);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
