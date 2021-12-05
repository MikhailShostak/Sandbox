//CLASSGEN GENERATED REGION: Includes
#include "Project.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Project::Project()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Project::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Targets", toJSONValue(Targets));
    object.insert("Entries", toJSONValue(Entries));
    object.insert("Configurations", toJSONValue(Configurations));
    object.insert("Settings", toJSONValue(Settings));
}
void Project::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Targets", value);
    fromJSONValue(value, Targets);
    value = AJSONValue();
    object.read("Entries", value);
    fromJSONValue(value, Entries);
    value = AJSONValue();
    object.read("Configurations", value);
    fromJSONValue(value, Configurations);
    value = AJSONValue();
    object.read("Settings", value);
    fromJSONValue(value, Settings);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
