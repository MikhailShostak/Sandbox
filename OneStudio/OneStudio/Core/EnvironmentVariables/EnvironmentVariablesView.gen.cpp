//CLASSGEN GENERATED REGION: Includes
#include "EnvironmentVariablesView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "EnvironmentVariablesGroupView.gen.h"
#include "Math"
#include "Experimental"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EnvironmentVariablesView::EnvironmentVariablesView()
{
    Math::Transform transform_102;
    Math::Vector position_103;
    position_103.X = 0.000000;
    position_103.Y = 0.000000;
    position_103.Z = 0.000000;
    position_103.W = 0.000000;
    transform_102.Position = position_103;
    Math::Quaternion rotation_108;
    rotation_108.X = 0.000000;
    rotation_108.Y = 0.000000;
    rotation_108.Z = 0.000000;
    rotation_108.W = 1.000000;
    transform_102.Rotation = rotation_108;
    (*this).setTransform(transform_102);
    Math::IntegerVector size_113;
    size_113.X = 0.000000;
    size_113.Y = 0.000000;
    size_113.Z = 0.000000;
    size_113.W = 0.000000;
    (*this).setSize(size_113);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_126_0;
    item_126_0.Alignment = Core::Alignment::Start;
    (*this).setData({item_126_0,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_130;
    padding_130.Top = 8.000000;
    padding_130.Right = 8.000000;
    padding_130.Bottom = 8.000000;
    padding_130.Left = 8.000000;
    (*this).setPadding(padding_130);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnvironmentVariablesView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EnvironmentVariablesView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnvironmentVariablesView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("EnvironmentVariablesView");
    systemVariables = CreateShared<OneStudio::EnvironmentVariablesGroupView>();
    (*systemVariables).setName("SystemVariables");
    Math::Transform transform_75;
    Math::Vector position_76;
    position_76.X = 0.000000;
    position_76.Y = 0.000000;
    position_76.Z = 0.000000;
    position_76.W = 0.000000;
    transform_75.Position = position_76;
    Math::Quaternion rotation_81;
    rotation_81.X = 0.000000;
    rotation_81.Y = 0.000000;
    rotation_81.Z = 0.000000;
    rotation_81.W = 1.000000;
    transform_75.Rotation = rotation_81;
    (*systemVariables).setTransform(transform_75);
    Math::IntegerVector size_86;
    size_86.X = 0.000000;
    size_86.Y = 0.000000;
    size_86.Z = 0.000000;
    size_86.W = 0.000000;
    (*systemVariables).setSize(size_86);
    (*systemVariables).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*systemVariables).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*systemVariables).setAffectsParentLayout(false);
    (*systemVariables).setDirection(UI::Direction::Vertical);
    (*systemVariables).setSpacing(8.000000);
    Math::Offsets padding_96;
    padding_96.Top = 0.000000;
    padding_96.Right = 0.000000;
    padding_96.Bottom = 0.000000;
    padding_96.Left = 0.000000;
    (*systemVariables).setPadding(padding_96);
    (*systemVariables).setTitle("System Variables");
    (*this).addView(systemVariables);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
