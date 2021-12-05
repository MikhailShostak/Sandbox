//CLASSGEN GENERATED REGION: Includes
#include "BuildingSettings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
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
    object.insert("ProductName", toJSONValue(ProductName));
    object.insert("SourcePaths", toJSONValue(SourcePaths));
    object.insert("BuildingDirectory", toJSONValue(BuildingDirectory));
    object.insert("DestinationDirectory", toJSONValue(DestinationDirectory));
}
void BuildingSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("ProductName", value);
    fromJSONValue(value, ProductName);
    value = AJSONValue();
    object.read("SourcePaths", value);
    fromJSONValue(value, SourcePaths);
    value = AJSONValue();
    object.read("BuildingDirectory", value);
    fromJSONValue(value, BuildingDirectory);
    value = AJSONValue();
    object.read("DestinationDirectory", value);
    fromJSONValue(value, DestinationDirectory);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
