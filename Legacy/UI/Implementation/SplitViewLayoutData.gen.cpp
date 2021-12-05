//CLASSGEN GENERATED REGION: Includes
#include "SplitViewLayoutData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
SplitViewLayoutData::SplitViewLayoutData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void SplitViewLayoutData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("PrimaryAlignment", toJSONValue(PrimaryAlignment));
    object.insert("SecondaryAlignment", toJSONValue(SecondaryAlignment));
}
void SplitViewLayoutData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("PrimaryAlignment", value);
    fromJSONValue(value, PrimaryAlignment);
    value = AJSONValue();
    object.read("SecondaryAlignment", value);
    fromJSONValue(value, SecondaryAlignment);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
