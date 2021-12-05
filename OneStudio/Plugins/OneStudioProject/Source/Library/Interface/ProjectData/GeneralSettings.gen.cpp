//CLASSGEN GENERATED REGION: Includes
#include "GeneralSettings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GeneralSettings::GeneralSettings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GeneralSettings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("BuildingSettings", toJSONValue(BuildingSettings));
}
void GeneralSettings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("BuildingSettings", value);
    fromJSONValue(value, BuildingSettings);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
