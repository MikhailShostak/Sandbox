//CLASSGEN GENERATED REGION: Includes
#include "DockEntry.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DockEntry::DockEntry()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DockEntry::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Entries", toJSONValue(Entries));
    object.insert("WindowIdentifiers", toJSONValue(WindowIdentifiers));
    object.insert("WindowSize", toJSONValue(WindowSize));
}
void DockEntry::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Entries", value);
    fromJSONValue(value, Entries);
    value = AJSONValue();
    object.read("WindowIdentifiers", value);
    fromJSONValue(value, WindowIdentifiers);
    value = AJSONValue();
    object.read("WindowSize", value);
    fromJSONValue(value, WindowSize);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
