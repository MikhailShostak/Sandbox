//CLASSGEN GENERATED REGION: Includes
#include "OverlayData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "MetaObjectSerializationHelper.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
OverlayData::OverlayData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void OverlayData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Padding", toJSONValue(Padding));
    object.insert("HorizontalAlignment", toJSONValue(HorizontalAlignment));
    object.insert("VerticalAlignment", toJSONValue(VerticalAlignment));
}
void OverlayData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Padding", value);
    fromJSONValue(value, Padding);
    value = AJSONValue();
    object.read("HorizontalAlignment", value);
    fromJSONValue(value, HorizontalAlignment);
    value = AJSONValue();
    object.read("VerticalAlignment", value);
    fromJSONValue(value, VerticalAlignment);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
