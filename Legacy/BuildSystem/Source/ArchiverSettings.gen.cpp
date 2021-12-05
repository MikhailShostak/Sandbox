//CLASSGEN GENERATED REGION: Includes
#include "ArchiverSettings.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ArchiverSettings::ArchiverSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ArchiverSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Archiver", toJSONValue(Archiver));
    object.insert("OutputFileFlag", toJSONValue(OutputFileFlag));
    object.insert("Flags", toJSONValue(Flags));
}
void ArchiverSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Archiver", value);
    fromJSONValue(value, Archiver);
    value = AJSONValue();
    object.read("OutputFileFlag", value);
    fromJSONValue(value, OutputFileFlag);
    value = AJSONValue();
    object.read("Flags", value);
    fromJSONValue(value, Flags);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
