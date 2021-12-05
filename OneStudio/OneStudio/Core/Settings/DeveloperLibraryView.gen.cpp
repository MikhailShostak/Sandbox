//CLASSGEN GENERATED REGION: Includes
#include "DeveloperLibraryView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DeveloperLibraryView::DeveloperLibraryView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DeveloperLibraryView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DeveloperLibraryView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DeveloperLibraryView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("DeveloperLibraryView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
