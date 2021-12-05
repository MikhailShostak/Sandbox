//CLASSGEN GENERATED REGION: Includes
#include "SettingsEntry.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
SettingsEntry::SettingsEntry()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void SettingsEntry::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Title", toJSONValue(Title));
}
void SettingsEntry::deserialize(const AJSONObject &object)
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
