//CLASSGEN GENERATED REGION: Includes
#include "TypeData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Experimental>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TypeData::TypeData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TypeData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Type", toJSONValue(Type));
    object.insert("Extensions", toJSONValue(Extensions));
    object.insert("AssociatedEditor", toJSONValue(AssociatedEditor));
}
void TypeData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Extensions", value);
    fromJSONValue(value, Extensions);
    value = AJSONValue();
    object.read("AssociatedEditor", value);
    fromJSONValue(value, AssociatedEditor);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
