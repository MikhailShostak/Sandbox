//CLASSGEN GENERATED REGION: Includes
#include "FindFilePopup.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FindFilePopup::FindFilePopup()
{
    Math::Transform transform_624;
    Math::Vector position_625;
    position_625.X = 0.000000;
    position_625.Y = 0.000000;
    position_625.Z = 0.000000;
    position_625.W = 0.000000;
    transform_624.Position = position_625;
    Math::Quaternion rotation_630;
    rotation_630.X = 0.000000;
    rotation_630.Y = 0.000000;
    rotation_630.Z = 0.000000;
    rotation_630.W = 1.000000;
    transform_624.Rotation = rotation_630;
    (*this).setTransform(transform_624);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FindFilePopup::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FindFilePopup::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FindFilePopup::onHierarchyCreate()
{
    SharedReference<UI::Label> header_overridden = CreateShared<UI::Label>();
    (*header_overridden).setName("Header_overridden");
    (*header_overridden).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*header_overridden).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*header_overridden).setText("Find File");
    (*header_overridden).setTextAlign(Core::TextAlign::Center);
    header = header_overridden;
    SharedReference<UI::FlexBox> content_overridden = CreateShared<UI::FlexBox>();
    (*content_overridden).setName("Content_overridden");
    (*content_overridden).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content_overridden).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_616_0;
    UI::FlexBoxData item_617_1;
    (*content_overridden).setData({item_616_0,item_617_1,});
    (*content_overridden).setDirection(UI::Direction::Vertical);
    (*content_overridden).setSpacing(8.000000);
    list = CreateShared<UI::ListView>();
    (*list).setName("List");
    (*list).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*list).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*content_overridden).addView(list);
    searchField = CreateShared<UI::TextField>();
    (*searchField).setName("SearchField");
    (*searchField).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*searchField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*content_overridden).addView(searchField);
    content = content_overridden;
    Super::onHierarchyCreate();
    setName("FindFilePopup");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
