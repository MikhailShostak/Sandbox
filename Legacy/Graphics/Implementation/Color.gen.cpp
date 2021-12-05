//CLASSGEN GENERATED REGION: Includes
#include "Color.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
Color::Color()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Color::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Red", toJSONValue(Red));
    object.insert("Green", toJSONValue(Green));
    object.insert("Blue", toJSONValue(Blue));
    object.insert("Alpha", toJSONValue(Alpha));
}
void Color::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Red", value);
    fromJSONValue(value, Red);
    value = AJSONValue();
    object.read("Green", value);
    fromJSONValue(value, Green);
    value = AJSONValue();
    object.read("Blue", value);
    fromJSONValue(value, Blue);
    value = AJSONValue();
    object.read("Alpha", value);
    fromJSONValue(value, Alpha);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
*/
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
