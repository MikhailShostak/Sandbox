//CLASSGEN GENERATED REGION: Includes
#include "ApplicationStateProperties.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationStateProperties::ApplicationStateProperties()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationStateProperties::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationStateProperties::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationStateProperties::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationStateProperties");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
