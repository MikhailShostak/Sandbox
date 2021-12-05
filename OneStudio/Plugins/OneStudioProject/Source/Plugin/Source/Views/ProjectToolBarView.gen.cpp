//CLASSGEN GENERATED REGION: Includes
#include "ProjectToolBarView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ProjectToolBarView::ProjectToolBarView()
{
    Math::Transform transform_265;
    Math::Vector position_266;
    position_266.X = 0.000000;
    position_266.Y = 0.000000;
    position_266.Z = 0.000000;
    position_266.W = 0.000000;
    transform_265.Position = position_266;
    Math::Quaternion rotation_271;
    rotation_271.X = 0.000000;
    rotation_271.Y = 0.000000;
    rotation_271.Z = 0.000000;
    rotation_271.W = 1.000000;
    transform_265.Rotation = rotation_271;
    (*this).setTransform(transform_265);
    Math::IntegerVector size_276;
    size_276.X = 0.000000;
    size_276.Y = 0.000000;
    size_276.Z = 0.000000;
    size_276.W = 0.000000;
    (*this).setSize(size_276);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_289_0;
    item_289_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_291_1;
    item_291_1.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_293_2;
    item_293_2.Alignment = Core::Alignment::Start;
    (*this).setData({item_289_0,item_291_1,item_293_2,});
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_297;
    padding_297.Top = 0.000000;
    padding_297.Right = 0.000000;
    padding_297.Bottom = 0.000000;
    padding_297.Left = 0.000000;
    (*this).setPadding(padding_297);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProjectToolBarView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ProjectToolBarView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProjectToolBarView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ProjectToolBarView");
    projectList = Create<UI::DropDownList>();
    (*projectList).setName("ProjectList");
    {
    }
    Math::Transform transform_242;
    Math::Vector position_243;
    position_243.X = 0.000000;
    position_243.Y = 0.000000;
    position_243.Z = 0.000000;
    position_243.W = 0.000000;
    transform_242.Position = position_243;
    Math::Quaternion rotation_248;
    rotation_248.X = 0.000000;
    rotation_248.Y = 0.000000;
    rotation_248.Z = 0.000000;
    rotation_248.W = 1.000000;
    transform_242.Rotation = rotation_248;
    (*projectList).setTransform(transform_242);
    Math::IntegerVector size_253;
    size_253.X = 0.000000;
    size_253.Y = 0.000000;
    size_253.Z = 0.000000;
    size_253.W = 0.000000;
    (*projectList).setSize(size_253);
    (*projectList).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*projectList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*projectList).setAffectsParentLayout(false);
    (*this).addView(projectList);
    targetList = Create<UI::DropDownList>();
    (*targetList).setName("TargetList");
    {
    }
    (*targetList).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*targetList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).addView(targetList);
    configurationList = Create<UI::DropDownList>();
    (*configurationList).setName("ConfigurationList");
    {
    }
    (*configurationList).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*configurationList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).addView(configurationList);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
