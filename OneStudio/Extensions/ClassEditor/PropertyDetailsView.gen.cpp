//CLASSGEN GENERATED REGION: Includes
#include "PropertyDetailsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PropertyDetailsView::PropertyDetailsView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PropertyDetailsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PropertyDetailsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PropertyDetailsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("PropertyDetailsView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
