//CLASSGEN GENERATED REGION: Includes
#include "EntryData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EntryData::EntryData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EntryData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Identifier", toJSONValue(Identifier));
    object.insert("InputParameters", toJSONValue(InputParameters));
    object.insert("OutputParameters", toJSONValue(OutputParameters));
}
void EntryData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Identifier", value);
    fromJSONValue(value, Identifier);
    value = AJSONValue();
    object.read("InputParameters", value);
    fromJSONValue(value, InputParameters);
    value = AJSONValue();
    object.read("OutputParameters", value);
    fromJSONValue(value, OutputParameters);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
