//CLASSGEN GENERATED REGION: Includes
#include "RenameFileDialog.gen.h"
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
RenameFileDialog::RenameFileDialog()
{
    Math::IntegerVector size_602;
    size_602.X = 770.000000;
    size_602.Y = 70.000000;
    size_602.Z = 0.000000;
    size_602.W = 0.000000;
    (*this).setSize(size_602);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RenameFileDialog::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void RenameFileDialog::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RenameFileDialog::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("RenameFileDialog");
    SharedReference<UI::Label> newNameLabel = CreateShared<UI::Label>();
    (*newNameLabel).setName("NewNameLabel");
    Math::Transform transform_545;
    Math::Vector position_546;
    position_546.X = 10.000000;
    position_546.Y = 10.000000;
    position_546.Z = 0.000000;
    position_546.W = 0.000000;
    transform_545.Position = position_546;
    (*newNameLabel).setTransform(transform_545);
    Math::IntegerVector size_551;
    size_551.X = 250.000000;
    size_551.Y = 20.000000;
    size_551.Z = 0.000000;
    size_551.W = 0.000000;
    (*newNameLabel).setSize(size_551);
    (*newNameLabel).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*newNameLabel).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*newNameLabel).setText("New Name");
    (*newNameLabel).setTextAlign(Core::TextAlign::End);
    (*newNameLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(newNameLabel);
    SharedReference<UI::TextField> newNameTextField = CreateShared<UI::TextField>();
    (*newNameTextField).setName("NewNameTextField");
    Math::Transform transform_561;
    Math::Vector position_562;
    position_562.X = 270.000000;
    position_562.Y = 10.000000;
    position_562.Z = 0.000000;
    position_562.W = 0.000000;
    transform_561.Position = position_562;
    (*newNameTextField).setTransform(transform_561);
    Math::IntegerVector size_567;
    size_567.X = 490.000000;
    size_567.Y = 20.000000;
    size_567.Z = 0.000000;
    size_567.W = 0.000000;
    (*newNameTextField).setSize(size_567);
    (*newNameTextField).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*newNameTextField).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).addView(newNameTextField);
    SharedReference<UI::TextButton> renameButton = CreateShared<UI::TextButton>();
    (*renameButton).setName("RenameButton");
    Math::Transform transform_574;
    Math::Vector position_575;
    position_575.X = 590.000000;
    position_575.Y = 40.000000;
    position_575.Z = 0.000000;
    position_575.W = 0.000000;
    transform_574.Position = position_575;
    (*renameButton).setTransform(transform_574);
    Math::IntegerVector size_580;
    size_580.X = 80.000000;
    size_580.Y = 20.000000;
    size_580.Z = 0.000000;
    size_580.W = 0.000000;
    (*renameButton).setSize(size_580);
    (*renameButton).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*renameButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*renameButton).setText("Rename");
    (*this).addView(renameButton);
    SharedReference<UI::TextButton> closeButton = CreateShared<UI::TextButton>();
    (*closeButton).setName("CloseButton");
    Math::Transform transform_588;
    Math::Vector position_589;
    position_589.X = 680.000000;
    position_589.Y = 40.000000;
    position_589.Z = 0.000000;
    position_589.W = 0.000000;
    transform_588.Position = position_589;
    (*closeButton).setTransform(transform_588);
    Math::IntegerVector size_594;
    size_594.X = 80.000000;
    size_594.Y = 20.000000;
    size_594.Z = 0.000000;
    size_594.W = 0.000000;
    (*closeButton).setSize(size_594);
    (*closeButton).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*closeButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*closeButton).setText("Cancel");
    (*this).addView(closeButton);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
