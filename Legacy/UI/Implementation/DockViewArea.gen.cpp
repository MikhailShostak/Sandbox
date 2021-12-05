//CLASSGEN GENERATED REGION: Includes
#include "DockViewArea.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DockViewArea::DockViewArea()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DockViewArea::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Tabs", toJSONValue(Tabs));
}
void DockViewArea::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Tabs", value);
    fromJSONValue(value, Tabs);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
