//CLASSGEN GENERATED REGION: Includes
#include "DockViewTab.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DockViewTab::DockViewTab()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DockViewTab::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Title", toJSONValue(Title));
}
void DockViewTab::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
