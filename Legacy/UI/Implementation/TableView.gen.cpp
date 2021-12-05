//CLASSGEN GENERATED REGION: Includes
#include "TableView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
TableView::TableView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TableView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TableView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
*/
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TableView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TableView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}

void TableView::onHierarchyCreate()
{
    SharedReference<SplitView> contentViewOverride = CreateShared<SplitView>();
    contentViewOverride->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
    contentView = contentViewOverride;

    Super::onHierarchyCreate();
}

#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
