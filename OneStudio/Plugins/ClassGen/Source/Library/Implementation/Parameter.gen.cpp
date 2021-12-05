//CLASSGEN GENERATED REGION: Includes
#include "Parameter.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Parameter::Parameter()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Parameter::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Type", toJSONValue(Type));
    object.insert("Name", toJSONValue(Name));
}
void Parameter::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
