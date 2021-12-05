//CLASSGEN GENERATED REGION: Includes
#include "DefaultExpandableItemView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Button.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DefaultExpandableItemView::DefaultExpandableItemView()
{
    UI::FlexBoxData item_339_0;
    item_339_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_341_1;
    item_341_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_343_2;
    item_343_2.Alignment = Core::Alignment::Center;
    (*this).setData({item_339_0,item_341_1,item_343_2,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultExpandableItemView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DefaultExpandableItemView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultExpandableItemView::onHierarchyCreate()
{
    expandButton = SharedReference<UI::Button>(Create<UI::Button>([this](UI::Button *v)
    {
    }
));
    (*expandButton).setName("ExpandButton");
    {
    }
    (*expandButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*expandButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*expandButton).setAffectsParentLayout(true);
    (*this).addView(expandButton);
    Super::onHierarchyCreate();
    setName("DefaultExpandableItemView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
