//CLASSGEN GENERATED REGION: Includes
#include "WindowLayout.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
WindowLayout::WindowLayout()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void WindowLayout::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("ToolbarItems", toJSONValue(ToolbarItems));
    object.insert("DockEntries", toJSONValue(DockEntries));
    object.insert("DockDirection", toJSONValue(DockDirection));
}
void WindowLayout::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("ToolbarItems", value);
    fromJSONValue(value, ToolbarItems);
    value = AJSONValue();
    object.read("DockEntries", value);
    fromJSONValue(value, DockEntries);
    value = AJSONValue();
    object.read("DockDirection", value);
    fromJSONValue(value, DockDirection);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
