//CLASSGEN GENERATED REGION: Includes
#include "TransitionView.gen.h"
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
TransitionView::TransitionView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TransitionView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TransitionView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TransitionView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TransitionView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
