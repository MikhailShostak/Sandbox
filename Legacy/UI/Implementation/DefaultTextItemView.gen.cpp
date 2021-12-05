//CLASSGEN GENERATED REGION: Includes
#include "DefaultTextItemView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Label.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DefaultTextItemView::DefaultTextItemView()
{
    (*this).setAffectsParentLayout(true);
    UI::FlexBoxData item_368_0;
    item_368_0.Alignment = Core::Alignment::Center;
    (*this).setData({item_368_0,});
    (*this).setSpacing(4.000000);
    Math::Offsets padding_371;
    padding_371.Top = 2.000000;
    padding_371.Right = 4.000000;
    padding_371.Bottom = 2.000000;
    padding_371.Left = 4.000000;
    (*this).setPadding(padding_371);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultTextItemView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DefaultTextItemView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DefaultTextItemView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("DefaultTextItemView");
    title = SharedReference<UI::Label>(Create<UI::Label>([this](UI::Label *v)
    {
    }
));
    (*title).setName("Title");
    {
    }
    (*title).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*title).setAffectsParentLayout(true);
    (*title).setTextAlign(Core::TextAlign::Start);
    (*title).setTextWrapping(Core::TextWrapping::Inline);
    (*this).addView(title);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
