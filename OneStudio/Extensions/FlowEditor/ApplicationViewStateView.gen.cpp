//CLASSGEN GENERATED REGION: Includes
#include "ApplicationViewStateView.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationViewStateView::ApplicationViewStateView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationViewStateView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationViewStateView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationViewStateView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationViewStateView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
