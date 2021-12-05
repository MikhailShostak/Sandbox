//CLASSGEN GENERATED REGION: Includes
#include "FilesSettings.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FilesSettings::FilesSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FilesSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("ObjectFileName", toJSONValue(ObjectFileName));
    object.insert("StaticLibraryFileName", toJSONValue(StaticLibraryFileName));
    object.insert("DynamicLibraryFileName", toJSONValue(DynamicLibraryFileName));
    object.insert("ApplicationFileName", toJSONValue(ApplicationFileName));
    object.insert("DebugSymbolsFileName", toJSONValue(DebugSymbolsFileName));
}
void FilesSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("ObjectFileName", value);
    fromJSONValue(value, ObjectFileName);
    value = AJSONValue();
    object.read("StaticLibraryFileName", value);
    fromJSONValue(value, StaticLibraryFileName);
    value = AJSONValue();
    object.read("DynamicLibraryFileName", value);
    fromJSONValue(value, DynamicLibraryFileName);
    value = AJSONValue();
    object.read("ApplicationFileName", value);
    fromJSONValue(value, ApplicationFileName);
    value = AJSONValue();
    object.read("DebugSymbolsFileName", value);
    fromJSONValue(value, DebugSymbolsFileName);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
