//CLASSGEN GENERATED REGION: Includes
#include "PinNodeViewWithPreview.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <Graphics>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PinNodeViewWithPreview::PinNodeViewWithPreview()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PinNodeViewWithPreview::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PinNodeViewWithPreview::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PinNodeViewWithPreview::onHierarchyCreate()
{
    SharedReference<UI::ImageView> nodeContent = SharedReference<UI::ImageView>(Create<UI::ImageView>([this](UI::ImageView *v)
    {
    }
));
    (*nodeContent).setName("NodeContent");
    {
    }
    Math::IntegerVector size_481;
    size_481.X = 100.000000;
    size_481.Y = 100.000000;
    (*nodeContent).setSize(size_481);
    (*nodeContent).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*nodeContent).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).nodeContent = nodeContent;
    Super::onHierarchyCreate();
    setName("PinNodeViewWithPreview");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
