//CLASSGEN GENERATED REGION: Includes
#include "EnvironmentVariablesGroupView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EnvironmentVariablesGroupView::EnvironmentVariablesGroupView()
{
    Math::Transform transform_40;
    Math::Vector position_41;
    position_41.X = 0.000000;
    position_41.Y = 0.000000;
    position_41.Z = 0.000000;
    position_41.W = 0.000000;
    transform_40.Position = position_41;
    Math::Quaternion rotation_46;
    rotation_46.X = 0.000000;
    rotation_46.Y = 0.000000;
    rotation_46.Z = 0.000000;
    rotation_46.W = 1.000000;
    transform_40.Rotation = rotation_46;
    (*this).setTransform(transform_40);
    Math::IntegerVector size_51;
    size_51.X = 0.000000;
    size_51.Y = 0.000000;
    size_51.Z = 0.000000;
    size_51.W = 0.000000;
    (*this).setSize(size_51);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_64_0;
    item_64_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_66_1;
    item_66_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_64_0,item_66_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_70;
    padding_70.Top = 0.000000;
    padding_70.Right = 0.000000;
    padding_70.Bottom = 0.000000;
    padding_70.Left = 0.000000;
    (*this).setPadding(padding_70);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnvironmentVariablesGroupView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Title", toJSONValue(Title));
}
void EnvironmentVariablesGroupView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Text EnvironmentVariablesGroupView::getTitle() const
{
    return this->Title;
}
void EnvironmentVariablesGroupView::setTitle(Text const &Title)
{
    this->Title = Title;
}
void EnvironmentVariablesGroupView::setTitle(Text &&Title)
{
    this->Title = std::move(Title);
}
void EnvironmentVariablesGroupView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("EnvironmentVariablesGroupView");
    title = CreateShared<UI::Label>();
    (*title).setName("Title");
    Math::Transform transform_0;
    Math::Vector position_1;
    position_1.X = 0.000000;
    position_1.Y = 0.000000;
    position_1.Z = 0.000000;
    position_1.W = 0.000000;
    transform_0.Position = position_1;
    Math::Quaternion rotation_6;
    rotation_6.X = 0.000000;
    rotation_6.Y = 0.000000;
    rotation_6.Z = 0.000000;
    rotation_6.W = 1.000000;
    transform_0.Rotation = rotation_6;
    (*title).setTransform(transform_0);
    Math::IntegerVector size_11;
    size_11.X = 0.000000;
    size_11.Y = 0.000000;
    size_11.Z = 0.000000;
    size_11.W = 0.000000;
    (*title).setSize(size_11);
    (*title).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*title).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setAffectsParentLayout(false);
    (*title).setTextAlign(Core::TextAlign::Start);
    (*title).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(title);
    list = CreateShared<UI::ListView>();
    (*list).setName("List");
    Math::Transform transform_21;
    Math::Vector position_22;
    position_22.X = 0.000000;
    position_22.Y = 0.000000;
    position_22.Z = 0.000000;
    position_22.W = 0.000000;
    transform_21.Position = position_22;
    Math::Quaternion rotation_27;
    rotation_27.X = 0.000000;
    rotation_27.Y = 0.000000;
    rotation_27.Z = 0.000000;
    rotation_27.W = 1.000000;
    transform_21.Rotation = rotation_27;
    (*list).setTransform(transform_21);
    Math::IntegerVector size_32;
    size_32.X = 0.000000;
    size_32.Y = 0.000000;
    size_32.Z = 0.000000;
    size_32.W = 0.000000;
    (*list).setSize(size_32);
    (*list).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*list).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*list).setAffectsParentLayout(false);
    (*this).addView(list);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
