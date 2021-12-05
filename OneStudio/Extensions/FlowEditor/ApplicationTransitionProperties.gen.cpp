//CLASSGEN GENERATED REGION: Includes
#include "ApplicationTransitionProperties.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationTransitionProperties::ApplicationTransitionProperties()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationTransitionProperties::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationTransitionProperties::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationTransitionProperties::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationTransitionProperties");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
