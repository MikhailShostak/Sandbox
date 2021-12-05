//CLASSGEN GENERATED REGION: Includes
#include "DefaultTabItemView.gen.h"
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
DefaultTabItemView::DefaultTabItemView()
{
    UI::FlexBoxData item_358_0;
    item_358_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_360_1;
    item_360_1.Alignment = Core::Alignment::Center;
    (*this).setData({item_358_0,item_360_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultTabItemView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DefaultTabItemView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultTabItemView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("DefaultTabItemView");
    closeButton = SharedReference<UI::Button>(Create<UI::Button>([this](UI::Button *v)
    {
    }
));
    (*closeButton).setName("CloseButton");
    {
    }
    (*closeButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*closeButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*closeButton).setAffectsParentLayout(true);
    (*this).addView(closeButton);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
