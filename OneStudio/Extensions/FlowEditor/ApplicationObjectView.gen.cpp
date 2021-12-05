//CLASSGEN GENERATED REGION: Includes
#include "ApplicationObjectView.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationObjectView::ApplicationObjectView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationObjectView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationObjectView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationObjectView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationObjectView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
