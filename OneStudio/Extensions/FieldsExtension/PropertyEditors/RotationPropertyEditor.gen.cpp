//CLASSGEN GENERATED REGION: Includes
#include "RotationPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
RotationPropertyEditor::RotationPropertyEditor()
{
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    UI::FlexBoxData item_2_2;
    UI::FlexBoxData item_3_3;
    (*this).setData({item_0_0,item_1_1,item_2_2,item_3_3,});
    (*this).setDirection(UI::Direction::Vertical);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RotationPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void RotationPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RotationPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("RotationPropertyEditor");
    type = CreateShared<UI::DropDownList>([this](UI::DropDownList *v)
    {
    }
);
    (*type).setName("Type");
    {
    }
    (*this).addView(type);
    x = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*x).setName("X");
    {
    }
    (*x).setPlaceholder("X");
    (*this).addView(x);
    y = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*y).setName("Y");
    {
    }
    (*y).setPlaceholder("Y");
    (*this).addView(y);
    z = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*z).setName("Z");
    {
    }
    (*z).setPlaceholder("Z");
    (*this).addView(z);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
