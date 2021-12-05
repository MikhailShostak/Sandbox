//CLASSGEN GENERATED REGION: Includes
#include "MainView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "WindowManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
MainView::MainView()
{
    Math::Transform transform_217;
    Math::Vector position_218;
    position_218.X = 0.000000;
    position_218.Y = 0.000000;
    position_218.Z = 0.000000;
    position_218.W = 0.000000;
    transform_217.Position = position_218;
    Math::Quaternion rotation_223;
    rotation_223.X = 0.000000;
    rotation_223.Y = 0.000000;
    rotation_223.Z = 0.000000;
    rotation_223.W = 1.000000;
    transform_217.Rotation = rotation_223;
    (*this).setTransform(transform_217);
    Math::IntegerVector size_228;
    size_228.X = 0.000000;
    size_228.Y = 0.000000;
    size_228.Z = 0.000000;
    size_228.W = 0.000000;
    (*this).setSize(size_228);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_241_0;
    item_241_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_243_1;
    item_243_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_241_0,item_243_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_247;
    padding_247.Top = 0.000000;
    padding_247.Right = 0.000000;
    padding_247.Bottom = 0.000000;
    padding_247.Left = 0.000000;
    (*this).setPadding(padding_247);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void MainView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void MainView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void MainView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("MainView");
    toolbar = CreateShared<UI::FlexBox>();
    (*toolbar).setName("Toolbar");
    Math::Transform transform_158;
    Math::Vector position_159;
    position_159.X = 0.000000;
    position_159.Y = 0.000000;
    position_159.Z = 0.000000;
    position_159.W = 0.000000;
    transform_158.Position = position_159;
    Math::Quaternion rotation_164;
    rotation_164.X = 0.000000;
    rotation_164.Y = 0.000000;
    rotation_164.Z = 0.000000;
    rotation_164.W = 1.000000;
    transform_158.Rotation = rotation_164;
    (*toolbar).setTransform(transform_158);
    Math::IntegerVector size_169;
    size_169.X = 0.000000;
    size_169.Y = 0.000000;
    size_169.Z = 0.000000;
    size_169.W = 0.000000;
    (*toolbar).setSize(size_169);
    (*toolbar).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*toolbar).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*toolbar).setAffectsParentLayout(false);
    (*toolbar).setDirection(UI::Direction::Horizontal);
    (*toolbar).setSpacing(0.000000);
    Math::Offsets padding_179;
    padding_179.Top = 0.000000;
    padding_179.Right = 0.000000;
    padding_179.Bottom = 0.000000;
    padding_179.Left = 0.000000;
    (*toolbar).setPadding(padding_179);
    (*this).addView(toolbar);
    contentView = CreateShared<UI::DockView>();
    (*contentView).setName("ContentView");
    Math::Transform transform_184;
    Math::Vector position_185;
    position_185.X = 0.000000;
    position_185.Y = 0.000000;
    position_185.Z = 0.000000;
    position_185.W = 0.000000;
    transform_184.Position = position_185;
    Math::Quaternion rotation_190;
    rotation_190.X = 0.000000;
    rotation_190.Y = 0.000000;
    rotation_190.Z = 0.000000;
    rotation_190.W = 1.000000;
    transform_184.Rotation = rotation_190;
    (*contentView).setTransform(transform_184);
    Math::IntegerVector size_195;
    size_195.X = 0.000000;
    size_195.Y = 0.000000;
    size_195.Z = 0.000000;
    size_195.W = 0.000000;
    (*contentView).setSize(size_195);
    (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setAffectsParentLayout(false);
    UI::SplitViewLayoutData item_204_0;
    item_204_0.PrimaryAlignment = Core::Alignment::Start;
    item_204_0.SecondaryAlignment = Core::Alignment::Start;
    UI::SplitViewLayoutData item_207_1;
    item_207_1.PrimaryAlignment = Core::Alignment::Start;
    item_207_1.SecondaryAlignment = Core::Alignment::Start;
    (*contentView).setData({item_204_0,item_207_1,});
    (*contentView).setDirection(UI::Direction::Horizontal);
    (*contentView).setSpacing(0.000000);
    Math::Offsets padding_212;
    padding_212.Top = 0.000000;
    padding_212.Right = 0.000000;
    padding_212.Bottom = 0.000000;
    padding_212.Left = 0.000000;
    (*contentView).setPadding(padding_212);
    (*this).addView(contentView);
}
//CLASSGEN END REGION
void MainView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    if(!OneStudio::WindowManager::getThisInstance().mainView)
    {
        OneStudio::WindowManager::getThisInstance().mainView = this;
    }
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
