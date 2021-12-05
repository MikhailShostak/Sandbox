//CLASSGEN GENERATED REGION: Includes
#include "EditorView.gen.h"
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
EditorView::EditorView()
{
    UI::FlexBoxData item_32_0;
    item_32_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_34_1;
    item_34_1.Alignment = Core::Alignment::Center;
    (*this).setData({item_32_0,item_34_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EditorView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EditorView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EditorView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("EditorView");
    SharedReference<UI::FlexBox> actionBar = CreateShared<UI::FlexBox>();
    (*actionBar).setName("ActionBar");
    (*actionBar).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*actionBar).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*actionBar).setSpacing(8.000000);
    (*this).addView(actionBar);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
