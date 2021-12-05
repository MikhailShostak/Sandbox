//CLASSGEN GENERATED REGION: Includes
#include "ArrayPropertyEditor.gen.h"
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
ArrayPropertyEditor::ArrayPropertyEditor()
{
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    (*this).setData({item_0_0,item_1_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(4.000000);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ArrayPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ArrayPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ArrayPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ArrayPropertyEditor");
    button = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*button).setName("Button");
    {
    }
    (*button).setText("Add");
    (*this).addView(button);
    list = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*list).setName("List");
    {
        (*list).CountItems = [this]()        {
            return items.size();
        };
;
        (*list).Item = [this](SizeInteger const& Index)        {
            return items[Index].second;
        };
;
    }
    (*this).addView(list);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
