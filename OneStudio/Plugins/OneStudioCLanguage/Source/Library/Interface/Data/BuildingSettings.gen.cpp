//CLASSGEN GENERATED REGION: Includes
#include "BuildingSettings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioCLanguage
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
BuildingSettings::BuildingSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void BuildingSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("CompilerSettings", toJSONValue(CompilerSettings));
    object.insert("CompilationSettings", toJSONValue(CompilationSettings));
    object.insert("ArchiverSettings", toJSONValue(ArchiverSettings));
    object.insert("LinkerSettings", toJSONValue(LinkerSettings));
    object.insert("LinkageSettings", toJSONValue(LinkageSettings));
    object.insert("FilesSettings", toJSONValue(FilesSettings));
}
void BuildingSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("CompilerSettings", value);
    fromJSONValue(value, CompilerSettings);
    value = AJSONValue();
    object.read("CompilationSettings", value);
    fromJSONValue(value, CompilationSettings);
    value = AJSONValue();
    object.read("ArchiverSettings", value);
    fromJSONValue(value, ArchiverSettings);
    value = AJSONValue();
    object.read("LinkerSettings", value);
    fromJSONValue(value, LinkerSettings);
    value = AJSONValue();
    object.read("LinkageSettings", value);
    fromJSONValue(value, LinkageSettings);
    value = AJSONValue();
    object.read("FilesSettings", value);
    fromJSONValue(value, FilesSettings);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
