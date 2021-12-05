//CLASSGEN GENERATED REGION: Includes
#include "FindSymbolPopup.gen.h"
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
FindSymbolPopup::FindSymbolPopup()
{
    Math::Transform transform_657;
    Math::Vector position_658;
    position_658.X = 0.000000;
    position_658.Y = 0.000000;
    position_658.Z = 0.000000;
    position_658.W = 0.000000;
    transform_657.Position = position_658;
    Math::Quaternion rotation_663;
    rotation_663.X = 0.000000;
    rotation_663.Y = 0.000000;
    rotation_663.Z = 0.000000;
    rotation_663.W = 1.000000;
    transform_657.Rotation = rotation_663;
    (*this).setTransform(transform_657);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FindSymbolPopup::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FindSymbolPopup::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FindSymbolPopup::onHierarchyCreate()
{
    SharedReference<UI::Label> header_overridden = CreateShared<UI::Label>();
    (*header_overridden).setName("Header_overridden");
    (*header_overridden).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*header_overridden).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*header_overridden).setText("Find Symbol");
    (*header_overridden).setTextAlign(Core::TextAlign::Center);
    header = header_overridden;
    SharedReference<UI::FlexBox> content_overridden = CreateShared<UI::FlexBox>();
    (*content_overridden).setName("Content_overridden");
    (*content_overridden).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content_overridden).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_649_0;
    UI::FlexBoxData item_650_1;
    (*content_overridden).setData({item_649_0,item_650_1,});
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
    setName("FindSymbolPopup");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
