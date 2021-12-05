//CLASSGEN GENERATED REGION: Includes
#include "LinkerSettings.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
LinkerSettings::LinkerSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void LinkerSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Linker", toJSONValue(Linker));
    object.insert("LibraryFlag", toJSONValue(LibraryFlag));
    object.insert("LibraryPathFlag", toJSONValue(LibraryPathFlag));
    object.insert("OutputFileFlag", toJSONValue(OutputFileFlag));
    object.insert("LibraryFlags", toJSONValue(LibraryFlags));
    object.insert("ApplicationFlags", toJSONValue(ApplicationFlags));
    object.insert("Flags", toJSONValue(Flags));
}
void LinkerSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Linker", value);
    fromJSONValue(value, Linker);
    value = AJSONValue();
    object.read("LibraryFlag", value);
    fromJSONValue(value, LibraryFlag);
    value = AJSONValue();
    object.read("LibraryPathFlag", value);
    fromJSONValue(value, LibraryPathFlag);
    value = AJSONValue();
    object.read("OutputFileFlag", value);
    fromJSONValue(value, OutputFileFlag);
    value = AJSONValue();
    object.read("LibraryFlags", value);
    fromJSONValue(value, LibraryFlags);
    value = AJSONValue();
    object.read("ApplicationFlags", value);
    fromJSONValue(value, ApplicationFlags);
    value = AJSONValue();
    object.read("Flags", value);
    fromJSONValue(value, Flags);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
