//CLASSGEN GENERATED REGION: Includes
#include "InvertedPanel.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include <Graphics>

//CLASSGEN END REGION
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
InvertedPanel::InvertedPanel()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void InvertedPanel::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void InvertedPanel::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void InvertedPanel::onHierarchyCreate()
{
    SharedReference<UI::BorderImageView> background = SharedReference<UI::BorderImageView>(Create<UI::BorderImageView>([this](UI::BorderImageView *v)
    {
    }
));
    (*background).setName("Background");
    {
    }
    (*background).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*background).setImage(InvertedFlatPanel);
    Math::Offsets border_382;
    border_382.Top = 2.000000;
    border_382.Right = 2.000000;
    border_382.Bottom = 2.000000;
    border_382.Left = 2.000000;
    (*background).setBorder(border_382);
    (*background).setFillCenter(false);
    (*this).background = background;
    Super::onHierarchyCreate();
    setName("InvertedPanel");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
