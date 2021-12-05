//CLASSGEN GENERATED REGION: Includes
#include "ToolTipView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "Label.gen.h"

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
ToolTipView::ToolTipView()
{
    Math::Transform transform_511;
    Math::Vector position_512;
    position_512.X = 0.000000;
    position_512.Y = 0.000000;
    position_512.Z = 0.000000;
    position_512.W = 0.000000;
    transform_511.Position = position_512;
    Math::Quaternion rotation_517;
    rotation_517.X = 0.000000;
    rotation_517.Y = 0.000000;
    rotation_517.Z = 0.000000;
    rotation_517.W = 1.000000;
    transform_511.Rotation = rotation_517;
    (*this).setTransform(transform_511);
    Math::IntegerVector size_522;
    size_522.X = 500.000000;
    size_522.Y = 500.000000;
    size_522.Z = 0.000000;
    size_522.W = 0.000000;
    (*this).setSize(size_522);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::OverlayData item_535_0;
    Math::Offsets padding_536;
    padding_536.Top = 0.000000;
    padding_536.Right = 0.000000;
    padding_536.Bottom = 0.000000;
    padding_536.Left = 0.000000;
    item_535_0.Padding = padding_536;
    item_535_0.HorizontalAlignment = Core::Alignment::Start;
    item_535_0.VerticalAlignment = Core::Alignment::Start;
    UI::OverlayData item_543_1;
    Math::Offsets padding_544;
    padding_544.Top = 50.000000;
    padding_544.Right = 50.000000;
    padding_544.Bottom = 50.000000;
    padding_544.Left = 50.000000;
    item_543_1.Padding = padding_544;
    item_543_1.HorizontalAlignment = Core::Alignment::Start;
    item_543_1.VerticalAlignment = Core::Alignment::Start;
    UI::OverlayData item_551_2;
    Math::Offsets padding_552;
    padding_552.Top = 8.000000;
    padding_552.Right = 8.000000;
    padding_552.Bottom = 8.000000;
    padding_552.Left = 8.000000;
    item_551_2.Padding = padding_552;
    item_551_2.HorizontalAlignment = Core::Alignment::End;
    item_551_2.VerticalAlignment = Core::Alignment::Start;
    (*this).setData({item_535_0,item_543_1,item_551_2,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ToolTipView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ToolTipView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ToolTipView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ToolTipView");
    SharedReference<UI::BorderImageView> background = CreateShared<UI::BorderImageView>();
    (*background).setName("Background");
    Math::Transform transform_463;
    Math::Vector position_464;
    position_464.X = 0.000000;
    position_464.Y = 0.000000;
    position_464.Z = 0.000000;
    position_464.W = 0.000000;
    transform_463.Position = position_464;
    Math::Quaternion rotation_469;
    rotation_469.X = 0.000000;
    rotation_469.Y = 0.000000;
    rotation_469.Z = 0.000000;
    rotation_469.W = 1.000000;
    transform_463.Rotation = rotation_469;
    (*background).setTransform(transform_463);
    Math::IntegerVector size_474;
    size_474.X = 580.000000;
    size_474.Y = 610.000000;
    size_474.Z = 0.000000;
    size_474.W = 0.000000;
    (*background).setSize(size_474);
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setAffectsParentLayout(true);
    (*background).setImage(ToolTip);
    Math::Offsets border_483;
    border_483.Top = 8.000000;
    border_483.Right = 8.000000;
    border_483.Bottom = 15.000000;
    border_483.Left = 40.000000;
    (*background).setBorder(border_483);
    (*background).setFillCenter(true);
    (*this).addView(background);
    SharedReference<UI::Label> text = CreateShared<UI::Label>();
    (*text).setName("Text");
    Math::Transform transform_489;
    Math::Vector position_490;
    position_490.X = 170.000000;
    position_490.Y = 0.000000;
    position_490.Z = 0.000000;
    position_490.W = 0.000000;
    transform_489.Position = position_490;
    Math::Quaternion rotation_495;
    rotation_495.X = 0.000000;
    rotation_495.Y = 0.000000;
    rotation_495.Z = 0.000000;
    rotation_495.W = 1.000000;
    transform_489.Rotation = rotation_495;
    (*text).setTransform(transform_489);
    Math::IntegerVector size_500;
    size_500.X = 100.000000;
    size_500.Y = 100.000000;
    size_500.Z = 0.000000;
    size_500.W = 0.000000;
    (*text).setSize(size_500);
    (*text).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*text).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*text).setAffectsParentLayout(true);
    (*text).setText("Test");
    (*text).setTextAlign(Core::TextAlign::Center);
    (*text).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(text);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
