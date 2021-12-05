//CLASSGEN GENERATED REGION: Includes
#include "ApplicationStateView.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationStateView::ApplicationStateView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationStateView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationStateView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationStateView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationStateView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
