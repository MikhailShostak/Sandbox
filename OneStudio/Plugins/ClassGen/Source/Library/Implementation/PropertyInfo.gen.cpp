//CLASSGEN GENERATED REGION: Includes
#include "PropertyInfo.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PropertyInfo::PropertyInfo()
{
    (*this).Variable = false;
    (*this).CustomGetter = false;
    (*this).CustomSetter = false;
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PropertyInfo::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("Type", toJSONValue(Type));
    object.insert("Parameters", toJSONValue(Parameters));
    object.insert("PreCallbacks", toJSONValue(PreCallbacks));
    object.insert("PostCallbacks", toJSONValue(PostCallbacks));
    object.insert("Attributes", toJSONValue(Attributes));
}
void PropertyInfo::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Parameters", value);
    fromJSONValue(value, Parameters);
    value = AJSONValue();
    object.read("PreCallbacks", value);
    fromJSONValue(value, PreCallbacks);
    value = AJSONValue();
    object.read("PostCallbacks", value);
    fromJSONValue(value, PostCallbacks);
    value = AJSONValue();
    object.read("Attributes", value);
    fromJSONValue(value, Attributes);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
