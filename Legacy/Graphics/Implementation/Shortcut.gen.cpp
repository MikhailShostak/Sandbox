//CLASSGEN GENERATED REGION: Includes
#include "Shortcut.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Shortcut::Shortcut()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Shortcut::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("KeyCode", toJSONValue(KeyCode));
    object.insert("KeyModifier", toJSONValue(KeyModifier));
}
void Shortcut::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("KeyCode", value);
    fromJSONValue(value, KeyCode);
    value = AJSONValue();
    object.read("KeyModifier", value);
    fromJSONValue(value, KeyModifier);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
