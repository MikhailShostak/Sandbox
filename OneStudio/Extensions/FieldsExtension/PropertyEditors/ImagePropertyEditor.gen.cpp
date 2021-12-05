//CLASSGEN GENERATED REGION: Includes
#include "ImagePropertyEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ExperimentalDebug"
#include "MathClasses"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ImagePropertyEditor::ImagePropertyEditor()
{
    UI::FlexBoxData item_2_0;
    UI::FlexBoxData item_3_1;
    (*this).setData({item_2_0,item_3_1,});
    (*this).setDirection(UI::Direction::Vertical);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ImagePropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ImagePropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ImagePropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ImagePropertyEditor");
    classPicker = CreateShared<LegacyClassGen::ClassPicker>([this](LegacyClassGen::ClassPicker *v)
    {
    }
);
    (*classPicker).setName("ClassPicker");
    {
    }
    (*this).addView(classPicker);
    previewImageView = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*previewImageView).setName("PreviewImageView");
    {
    }
    Math::IntegerVector size_0;
    size_0.X = 100.000000;
    size_0.Y = 100.000000;
    (*previewImageView).setSize(size_0);
    (*previewImageView).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*previewImageView).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).addView(previewImageView);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
