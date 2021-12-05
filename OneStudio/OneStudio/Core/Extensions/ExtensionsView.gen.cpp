//CLASSGEN GENERATED REGION: Includes
#include "ExtensionsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ExtensionsView::ExtensionsView()
{
    Math::Transform transform_135;
    Math::Vector position_136;
    position_136.X = 0.000000;
    position_136.Y = 0.000000;
    position_136.Z = 0.000000;
    position_136.W = 0.000000;
    transform_135.Position = position_136;
    Math::Quaternion rotation_141;
    rotation_141.X = 0.000000;
    rotation_141.Y = 0.000000;
    rotation_141.Z = 0.000000;
    rotation_141.W = 1.000000;
    transform_135.Rotation = rotation_141;
    (*this).setTransform(transform_135);
    Math::IntegerVector size_146;
    size_146.X = 0.000000;
    size_146.Y = 0.000000;
    size_146.Z = 0.000000;
    size_146.W = 0.000000;
    (*this).setSize(size_146);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ExtensionsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ExtensionsView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
