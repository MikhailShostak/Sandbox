//CLASSGEN GENERATED REGION: Includes
#include "PropertySet.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PropertySet::PropertySet()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PropertySet::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Functions", toJSONValue(Functions));
}
void PropertySet::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Functions", value);
    fromJSONValue(value, Functions);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
