//CLASSGEN GENERATED REGION: Includes
#include "FlexBoxData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FlexBoxData::FlexBoxData()
{
    (*this).Alignment = Core::Alignment::Start;
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FlexBoxData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Alignment", toJSONValue(Alignment));
}
void FlexBoxData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Alignment", value);
    fromJSONValue(value, Alignment);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
