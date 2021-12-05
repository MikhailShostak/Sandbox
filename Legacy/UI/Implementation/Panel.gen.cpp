//CLASSGEN GENERATED REGION: Includes
#include "Panel.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <UIDarkTheme>
#include <Graphics>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Panel::Panel()
{
    UI::OverlayData item_418_0;
    UI::OverlayData item_419_1;
    Math::Offsets padding_420;
    padding_420.Top = 1.000000;
    padding_420.Right = 1.000000;
    padding_420.Bottom = 1.000000;
    padding_420.Left = 1.000000;
    item_419_1.Padding = padding_420;
    (*this).setData({item_418_0,item_419_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Panel::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void Panel::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Panel::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("Panel");
    if (background)
    {
        (*this).addView(background);
    }
    else
    {
        SharedReference<UI::BorderImageView> defaultBackground = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
        {
        }
);
        (*defaultBackground).setName("DefaultBackground");
        {
        }
        (*defaultBackground).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultBackground).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultBackground).setImage(FlatPanel);
        Math::Offsets border_402;
        border_402.Top = 2.000000;
        border_402.Right = 2.000000;
        border_402.Bottom = 2.000000;
        border_402.Left = 2.000000;
        (*defaultBackground).setBorder(border_402);
        (*defaultBackground).setFillCenter(false);
        (*this).addView(defaultBackground);
        background = defaultBackground;
    }
    if (root)
    {
        (*this).addView(root);
    }
    else
    {
        SharedReference<UI::BorderImageView> image = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
        {
        }
);
        (*image).setName("Image");
        {
        }
        (*image).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*image).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*image).setImage(FlatPanel);
        Math::Offsets border_411;
        border_411.Top = 2.000000;
        border_411.Right = 2.000000;
        border_411.Bottom = 2.000000;
        border_411.Left = 2.000000;
        (*image).setBorder(border_411);
        (*image).setFillCenter(false);
        (*this).addView(image);
        root = image;
    }
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
