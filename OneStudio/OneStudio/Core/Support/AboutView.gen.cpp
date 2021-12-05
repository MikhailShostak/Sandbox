//CLASSGEN GENERATED REGION: Includes
#include "AboutView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
AboutView::AboutView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void AboutView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void AboutView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void AboutView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("AboutView");
    SharedReference<UI::ImageView> uIImageView = CreateShared<UI::ImageView>();
    (*uIImageView).setName("UIImageView");
    (*this).addView(uIImageView);
    SharedReference<UI::Label> uILabel = CreateShared<UI::Label>();
    (*uILabel).setName("UILabel");
    (*this).addView(uILabel);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
