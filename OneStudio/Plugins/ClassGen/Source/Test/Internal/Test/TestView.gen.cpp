//CLASSGEN GENERATED REGION: Includes
#include "TestView.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TestView::TestView()
{
    Math::Transform transform_95;
    Math::Vector position_96;
    position_96.X = 0.000000;
    position_96.Y = 0.000000;
    position_96.Z = 0.000000;
    position_96.W = 0.000000;
    transform_95.Position = position_96;
    Math::Quaternion rotation_101;
    rotation_101.X = 0.000000;
    rotation_101.Y = 0.000000;
    rotation_101.Z = 0.000000;
    rotation_101.W = 1.000000;
    transform_95.Rotation = rotation_101;
    (*this).setTransform(transform_95);
    Math::IntegerVector size_106;
    size_106.X = 600.000000;
    size_106.Y = 800.000000;
    size_106.Z = 0.000000;
    size_106.W = 0.000000;
    (*this).setSize(size_106);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_119_0;
    item_119_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_121_1;
    item_121_1.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_123_2;
    item_123_2.Alignment = Core::Alignment::End;
    (*this).setData({item_119_0,item_121_1,item_123_2,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(50.000000);
    Math::Offsets padding_127;
    padding_127.Top = 10.000000;
    padding_127.Right = 10.000000;
    padding_127.Bottom = 10.000000;
    padding_127.Left = 10.000000;
    (*this).setPadding(padding_127);
    (*this).setTest1(false);
    (*this).setTest2(false);
SharedReference<UI::View> test1 = new UI::View();
Math::Transform transform_19;
Math::Vector position_20;
position_20.X = 10.000000;
position_20.Y = 0.000000;
position_20.Z = 0.000000;
position_20.W = 0.000000;
transform_19.Position = position_20;
Math::Quaternion rotation_25;
rotation_25.X = 0.000000;
rotation_25.Y = 0.000000;
rotation_25.Z = 0.000000;
rotation_25.W = 1.000000;
transform_19.Rotation = rotation_25;
(*test1).setTransform(transform_19);
Math::IntegerVector size_30;
size_30.X = 200.000000;
size_30.Y = 200.000000;
size_30.Z = 0.000000;
size_30.W = 0.000000;
(*test1).setSize(size_30);
(*test1).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
(*test1).setVerticalSizePolicy(UI::SizePolicy::Fixed);
(*test1).setAffectsParentLayout(false);
SharedReference<UI::Button> test1 = new UI::Button();
Math::Transform transform_38;
Math::Vector position_39;
position_39.X = 0.000000;
position_39.Y = 0.000000;
position_39.Z = 0.000000;
position_39.W = 0.000000;
transform_38.Position = position_39;
Math::Quaternion rotation_44;
rotation_44.X = 0.000000;
rotation_44.Y = 0.000000;
rotation_44.Z = 0.000000;
rotation_44.W = 1.000000;
transform_38.Rotation = rotation_44;
(*test1).setTransform(transform_38);
Math::IntegerVector size_49;
size_49.X = 230.000000;
size_49.Y = 60.000000;
size_49.Z = 0.000000;
size_49.W = 0.000000;
(*test1).setSize(size_49);
(*test1).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
(*test1).setVerticalSizePolicy(UI::SizePolicy::Fixed);
(*test1).setAffectsParentLayout(false);
(*test1).addView(test1);
(*this).addView(test1);
SharedReference<UI::ImageView> test2 = new UI::ImageView();
Math::Transform transform_57;
Math::Vector position_58;
position_58.X = 10.000000;
position_58.Y = 210.000000;
position_58.Z = 0.000000;
position_58.W = 0.000000;
transform_57.Position = position_58;
Math::Quaternion rotation_63;
rotation_63.X = 0.000000;
rotation_63.Y = 0.000000;
rotation_63.Z = 0.000000;
rotation_63.W = 1.000000;
transform_57.Rotation = rotation_63;
(*test2).setTransform(transform_57);
Math::IntegerVector size_68;
size_68.X = 200.000000;
size_68.Y = 200.000000;
size_68.Z = 0.000000;
size_68.W = 0.000000;
(*test2).setSize(size_68);
(*test2).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
(*test2).setVerticalSizePolicy(UI::SizePolicy::Expanded);
(*test2).setAffectsParentLayout(false);
(*this).addView(test2);
SharedReference<UI::Button> test3 = new UI::Button();
Math::Transform transform_76;
Math::Vector position_77;
position_77.X = 0.000000;
position_77.Y = 0.000000;
position_77.Z = 0.000000;
position_77.W = 0.000000;
transform_76.Position = position_77;
Math::Quaternion rotation_82;
rotation_82.X = 0.000000;
rotation_82.Y = 0.000000;
rotation_82.Z = 0.000000;
rotation_82.W = 1.000000;
transform_76.Rotation = rotation_82;
(*test3).setTransform(transform_76);
Math::IntegerVector size_87;
size_87.X = 200.000000;
size_87.Y = 200.000000;
size_87.Z = 0.000000;
size_87.W = 0.000000;
(*test3).setSize(size_87);
(*test3).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
(*test3).setVerticalSizePolicy(UI::SizePolicy::Fixed);
(*test3).setAffectsParentLayout(false);
(*this).addView(test3);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TestView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TestView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Boolean TestView::getTest1() const
{
    return this->Test1;
}
void TestView::setTest1(Boolean const &Test1)
{
    this->Test1 = Test1;
}
void TestView::setTest1(Boolean &&Test1)
{
    this->Test1 = std::move(Test1);
}
Boolean TestView::getTest2() const
{
    return this->Test2;
}
void TestView::setTest2(Boolean const &Test2)
{
    this->Test2 = Test2;
}
void TestView::setTest2(Boolean &&Test2)
{
    this->Test2 = std::move(Test2);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
