//CLASSGEN GENERATED REGION: Includes
#include "CompilationSettings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
CompilationSettings::CompilationSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void CompilationSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Defines", toJSONValue(Defines));
    object.insert("Includes", toJSONValue(Includes));
    object.insert("IncludePaths", toJSONValue(IncludePaths));
    object.insert("ArgumentFiles", toJSONValue(ArgumentFiles));
}
void CompilationSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Defines", value);
    fromJSONValue(value, Defines);
    value = AJSONValue();
    object.read("Includes", value);
    fromJSONValue(value, Includes);
    value = AJSONValue();
    object.read("IncludePaths", value);
    fromJSONValue(value, IncludePaths);
    value = AJSONValue();
    object.read("ArgumentFiles", value);
    fromJSONValue(value, ArgumentFiles);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
