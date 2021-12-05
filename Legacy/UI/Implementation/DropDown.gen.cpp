//CLASSGEN GENERATED REGION: Includes
#include "DropDown.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "TextButton.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DropDown::DropDown()
{
    UI::OverlayData item_378_0;
    (*this).setData({item_378_0,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DropDown::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DropDown::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DropDown::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("DropDown");
    button = SharedReference<UI::TextButton>(Create<UI::TextButton>([this](UI::TextButton *v)
    {
    }
));
    (*button).setName("Button");
    {
    }
    (*button).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).addView(button);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
