//CLASSGEN GENERATED REGION: Includes
#include "DefaultIconItemView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <UIDarkTheme>

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DefaultIconItemView::DefaultIconItemView()
{
    UI::FlexBoxData item_350_0;
    item_350_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_352_1;
    item_352_1.Alignment = Core::Alignment::Center;
    (*this).setData({item_350_0,item_352_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultIconItemView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DefaultIconItemView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultIconItemView::onHierarchyCreate()
{
    icon = SharedReference<UI::ImageView>(Create<UI::ImageView>([this](UI::ImageView *v)
    {
    }
));
    (*icon).setName("Icon");
    {
    }
    (*icon).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*icon).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*icon).setAffectsParentLayout(true);
    (*icon).setImage(::FileIcon);
    (*this).addView(icon);
    Super::onHierarchyCreate();
    setName("DefaultIconItemView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
