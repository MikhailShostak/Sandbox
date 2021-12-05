//CLASSGEN GENERATED REGION: Includes
#include "TypeInfo.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TypeInfo::TypeInfo()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TypeInfo::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("Parameters", toJSONValue(Parameters));
}
void TypeInfo::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("Parameters", value);
    fromJSONValue(value, Parameters);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
