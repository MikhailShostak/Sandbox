//CLASSGEN GENERATED REGION: Includes
#include "AnchorView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
AnchorView::AnchorView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void AnchorView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void AnchorView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void AnchorView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("AnchorView");
}
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
