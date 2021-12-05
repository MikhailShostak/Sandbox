//CLASSGEN GENERATED REGION: Includes
#include "TasksProgressEntryView.gen.h"
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
TasksProgressEntryView::TasksProgressEntryView()
{
    Math::IntegerVector size_877;
    size_877.X = 0.000000;
    size_877.Y = 0.000000;
    size_877.Z = 0.000000;
    size_877.W = 0.000000;
    (*this).setSize(size_877);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_888_0;
    item_888_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_890_1;
    item_890_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_892_2;
    item_892_2.Alignment = Core::Alignment::Center;
    (*this).setData({item_888_0,item_890_1,item_892_2,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_896;
    padding_896.Top = 8.000000;
    padding_896.Right = 8.000000;
    padding_896.Bottom = 8.000000;
    padding_896.Left = 8.000000;
    (*this).setPadding(padding_896);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TasksProgressEntryView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TasksProgressEntryView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TasksProgressEntryView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TasksProgressEntryView");
    expandIcon = CreateShared<UI::ImageView>();
    (*expandIcon).setName("ExpandIcon");
    Math::Transform transform_819;
    Math::Vector position_820;
    position_820.X = 280.000000;
    position_820.Y = 0.000000;
    position_820.Z = 0.000000;
    position_820.W = 0.000000;
    transform_819.Position = position_820;
    Math::Quaternion rotation_825;
    rotation_825.X = 0.000000;
    rotation_825.Y = 0.000000;
    rotation_825.Z = 0.000000;
    rotation_825.W = 1.000000;
    transform_819.Rotation = rotation_825;
    (*expandIcon).setTransform(transform_819);
    Math::IntegerVector size_830;
    size_830.X = 190.000000;
    size_830.Y = 80.000000;
    size_830.Z = 0.000000;
    size_830.W = 0.000000;
    (*expandIcon).setSize(size_830);
    (*expandIcon).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*expandIcon).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*expandIcon).setAffectsParentLayout(false);
    (*this).addView(expandIcon);
    statusIcon = CreateShared<UI::ImageView>();
    (*statusIcon).setName("StatusIcon");
    Math::Transform transform_838;
    Math::Vector position_839;
    position_839.X = 280.000000;
    position_839.Y = 0.000000;
    position_839.Z = 0.000000;
    position_839.W = 0.000000;
    transform_838.Position = position_839;
    Math::Quaternion rotation_844;
    rotation_844.X = 0.000000;
    rotation_844.Y = 0.000000;
    rotation_844.Z = 0.000000;
    rotation_844.W = 1.000000;
    transform_838.Rotation = rotation_844;
    (*statusIcon).setTransform(transform_838);
    Math::IntegerVector size_849;
    size_849.X = 190.000000;
    size_849.Y = 80.000000;
    size_849.Z = 0.000000;
    size_849.W = 0.000000;
    (*statusIcon).setSize(size_849);
    (*statusIcon).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*statusIcon).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*statusIcon).setAffectsParentLayout(false);
    (*this).addView(statusIcon);
    title = CreateShared<UI::Label>();
    (*title).setName("Title");
    Math::Transform transform_857;
    Math::Vector position_858;
    position_858.X = 280.000000;
    position_858.Y = 0.000000;
    position_858.Z = 0.000000;
    position_858.W = 0.000000;
    transform_857.Position = position_858;
    Math::Quaternion rotation_863;
    rotation_863.X = 0.000000;
    rotation_863.Y = 0.000000;
    rotation_863.Z = 0.000000;
    rotation_863.W = 1.000000;
    transform_857.Rotation = rotation_863;
    (*title).setTransform(transform_857);
    Math::IntegerVector size_868;
    size_868.X = 190.000000;
    size_868.Y = 80.000000;
    size_868.Z = 0.000000;
    size_868.W = 0.000000;
    (*title).setSize(size_868);
    (*title).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*title).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*title).setAffectsParentLayout(false);
    (*title).setText("Stop");
    (*this).addView(title);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
