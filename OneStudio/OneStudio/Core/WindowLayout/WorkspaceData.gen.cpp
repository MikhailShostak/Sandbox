//CLASSGEN GENERATED REGION: Includes
#include "WorkspaceData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Experimental>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
WorkspaceData::WorkspaceData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void WorkspaceData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("RecentFiles", toJSONValue(RecentFiles));
    object.insert("PinnedFiles", toJSONValue(PinnedFiles));
    object.insert("OpenedFiles", toJSONValue(OpenedFiles));
    object.insert("OpenedEditors", toJSONValue(OpenedEditors));
    object.insert("WindowLayout", toJSONValue(WindowLayout));
}
void WorkspaceData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("RecentFiles", value);
    fromJSONValue(value, RecentFiles);
    value = AJSONValue();
    object.read("PinnedFiles", value);
    fromJSONValue(value, PinnedFiles);
    value = AJSONValue();
    object.read("OpenedFiles", value);
    fromJSONValue(value, OpenedFiles);
    value = AJSONValue();
    object.read("OpenedEditors", value);
    fromJSONValue(value, OpenedEditors);
    value = AJSONValue();
    object.read("WindowLayout", value);
    fromJSONValue(value, WindowLayout);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
