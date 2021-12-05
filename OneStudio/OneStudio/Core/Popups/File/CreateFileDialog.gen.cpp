//CLASSGEN GENERATED REGION: Includes
#include "CreateFileDialog.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
CreateFileDialog::CreateFileDialog()
{
    Math::IntegerVector size_483;
    size_483.X = 770.000000;
    size_483.Y = 130.000000;
    size_483.Z = 0.000000;
    size_483.W = 0.000000;
    (*this).setSize(size_483);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void CreateFileDialog::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void CreateFileDialog::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void CreateFileDialog::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("CreateFileDialog");
    SharedReference<UI::Label> typeLabel = CreateShared<UI::Label>();
    (*typeLabel).setName("TypeLabel");
    Math::Transform transform_366;
    Math::Vector position_367;
    position_367.X = 10.000000;
    position_367.Y = 10.000000;
    position_367.Z = 0.000000;
    position_367.W = 0.000000;
    transform_366.Position = position_367;
    (*typeLabel).setTransform(transform_366);
    Math::IntegerVector size_372;
    size_372.X = 250.000000;
    size_372.Y = 20.000000;
    size_372.Z = 0.000000;
    size_372.W = 0.000000;
    (*typeLabel).setSize(size_372);
    (*typeLabel).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*typeLabel).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*typeLabel).setText("Type");
    (*typeLabel).setTextAlign(Core::TextAlign::End);
    (*typeLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(typeLabel);
    typeList = CreateShared<UI::DropDownList>();
    (*typeList).setName("TypeList");
    Math::Transform transform_382;
    Math::Vector position_383;
    position_383.X = 270.000000;
    position_383.Y = 10.000000;
    position_383.Z = 0.000000;
    position_383.W = 0.000000;
    transform_382.Position = position_383;
    (*typeList).setTransform(transform_382);
    Math::IntegerVector size_388;
    size_388.X = 490.000000;
    size_388.Y = 20.000000;
    size_388.Z = 0.000000;
    size_388.W = 0.000000;
    (*typeList).setSize(size_388);
    (*typeList).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*typeList).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).addView(typeList);
    createButton = CreateShared<UI::TextButton>();
    (*createButton).setName("CreateButton");
    Math::Transform transform_395;
    Math::Vector position_396;
    position_396.X = 590.000000;
    position_396.Y = 100.000000;
    position_396.Z = 0.000000;
    position_396.W = 0.000000;
    transform_395.Position = position_396;
    (*createButton).setTransform(transform_395);
    Math::IntegerVector size_401;
    size_401.X = 80.000000;
    size_401.Y = 20.000000;
    size_401.Z = 0.000000;
    size_401.W = 0.000000;
    (*createButton).setSize(size_401);
    (*createButton).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*createButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*createButton).setText("Create");
    (*this).addView(createButton);
    cancelButton = CreateShared<UI::TextButton>();
    (*cancelButton).setName("CancelButton");
    Math::Transform transform_409;
    Math::Vector position_410;
    position_410.X = 680.000000;
    position_410.Y = 100.000000;
    position_410.Z = 0.000000;
    position_410.W = 0.000000;
    transform_409.Position = position_410;
    (*cancelButton).setTransform(transform_409);
    Math::IntegerVector size_415;
    size_415.X = 80.000000;
    size_415.Y = 20.000000;
    size_415.Z = 0.000000;
    size_415.W = 0.000000;
    (*cancelButton).setSize(size_415);
    (*cancelButton).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*cancelButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*cancelButton).setText("Cancel");
    (*this).addView(cancelButton);
    SharedReference<UI::Label> nameLabel = CreateShared<UI::Label>();
    (*nameLabel).setName("NameLabel");
    Math::Transform transform_423;
    Math::Vector position_424;
    position_424.X = 10.000000;
    position_424.Y = 40.000000;
    position_424.Z = 0.000000;
    position_424.W = 0.000000;
    transform_423.Position = position_424;
    (*nameLabel).setTransform(transform_423);
    Math::IntegerVector size_429;
    size_429.X = 250.000000;
    size_429.Y = 20.000000;
    size_429.Z = 0.000000;
    size_429.W = 0.000000;
    (*nameLabel).setSize(size_429);
    (*nameLabel).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*nameLabel).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*nameLabel).setAffectsParentLayout(false);
    (*nameLabel).setText("Name");
    (*nameLabel).setTextAlign(Core::TextAlign::End);
    (*nameLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(nameLabel);
    nameTextField = CreateShared<UI::TextField>();
    (*nameTextField).setName("NameTextField");
    Math::Transform transform_440;
    Math::Vector position_441;
    position_441.X = 270.000000;
    position_441.Y = 40.000000;
    position_441.Z = 0.000000;
    position_441.W = 0.000000;
    transform_440.Position = position_441;
    (*nameTextField).setTransform(transform_440);
    Math::IntegerVector size_446;
    size_446.X = 490.000000;
    size_446.Y = 20.000000;
    size_446.Z = 0.000000;
    size_446.W = 0.000000;
    (*nameTextField).setSize(size_446);
    (*nameTextField).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*nameTextField).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*nameTextField).setAffectsParentLayout(false);
    (*this).addView(nameTextField);
    SharedReference<UI::Label> namespaceLabel = CreateShared<UI::Label>();
    (*namespaceLabel).setName("NamespaceLabel");
    Math::Transform transform_454;
    Math::Vector position_455;
    position_455.X = 10.000000;
    position_455.Y = 70.000000;
    position_455.Z = 0.000000;
    position_455.W = 0.000000;
    transform_454.Position = position_455;
    (*namespaceLabel).setTransform(transform_454);
    Math::IntegerVector size_460;
    size_460.X = 250.000000;
    size_460.Y = 20.000000;
    size_460.Z = 0.000000;
    size_460.W = 0.000000;
    (*namespaceLabel).setSize(size_460);
    (*namespaceLabel).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*namespaceLabel).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*namespaceLabel).setText("Namespace");
    (*namespaceLabel).setTextAlign(Core::TextAlign::End);
    (*namespaceLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(namespaceLabel);
    namespaceTextField = CreateShared<UI::TextField>();
    (*namespaceTextField).setName("NamespaceTextField");
    Math::Transform transform_470;
    Math::Vector position_471;
    position_471.X = 270.000000;
    position_471.Y = 70.000000;
    position_471.Z = 0.000000;
    position_471.W = 0.000000;
    transform_470.Position = position_471;
    (*namespaceTextField).setTransform(transform_470);
    Math::IntegerVector size_476;
    size_476.X = 490.000000;
    size_476.Y = 20.000000;
    size_476.Z = 0.000000;
    size_476.W = 0.000000;
    (*namespaceTextField).setSize(size_476);
    (*namespaceTextField).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*namespaceTextField).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).addView(namespaceTextField);
}
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
