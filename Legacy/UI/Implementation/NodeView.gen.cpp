//CLASSGEN GENERATED REGION: Includes
#include "NodeView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
NodeView::NodeView()
{
    UI::OverlayData item_449_0;
    UI::OverlayData item_450_1;
    Math::Offsets padding_451;
    padding_451.Top = 8.000000;
    padding_451.Right = 8.000000;
    padding_451.Bottom = 8.000000;
    padding_451.Left = 8.000000;
    item_450_1.Padding = padding_451;
    (*this).setData({item_449_0,item_450_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NodeView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void NodeView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NodeView::onHierarchyCreate()
{
    SharedReference<UI::BorderImageView> background = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
    {
    }
);
    (*background).setName("Background");
    {
    }
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setImage(Node);
    Math::Offsets border_442;
    border_442.Top = 8.000000;
    border_442.Right = 8.000000;
    border_442.Bottom = 8.000000;
    border_442.Left = 8.000000;
    (*background).setBorder(border_442);
    (*background).setUseOriginalContentSize(false);
    (*this).background = background;
    Super::onHierarchyCreate();
    setName("NodeView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
