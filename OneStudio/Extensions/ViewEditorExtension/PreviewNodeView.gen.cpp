//CLASSGEN GENERATED REGION: Includes
#include "PreviewNodeView.gen.h"
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
PreviewNodeView::PreviewNodeView()
{
    UI::OverlayData item_27_0;
    UI::OverlayData item_28_1;
    (*this).setData({item_27_0,item_28_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PreviewNodeView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PreviewNodeView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<UI::View> PreviewNodeView::getInstance() const
{
    return this->Instance;
}
void PreviewNodeView::setInstance(SharedReference<UI::View> const &Instance)
{
    this->Instance = Instance;
}
void PreviewNodeView::setInstance(SharedReference<UI::View> &&Instance)
{
    this->Instance = std::move(Instance);
}
void PreviewNodeView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("PreviewNodeView");
    borderView = CreateShared<UI::BorderImageView>();
    (*borderView).setName("BorderView");
    (*this).addView(borderView);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
