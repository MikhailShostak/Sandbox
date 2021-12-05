//CLASSGEN GENERATED REGION: Includes
#include "EventDetailsView.gen.h"
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
EventDetailsView::EventDetailsView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EventDetailsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EventDetailsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EventDetailsView::onHierarchyCreate()
{
    SharedReference<UI::FlexBox> body = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*body).setName("Body");
    {
    }
    UI::FlexBoxData item_2_0;
    UI::FlexBoxData item_3_1;
    UI::FlexBoxData item_4_2;
    UI::FlexBoxData item_5_3;
    UI::FlexBoxData item_6_4;
    (*body).setData({item_2_0,item_3_1,item_4_2,item_5_3,item_6_4,});
    (*body).setDirection(UI::Direction::Vertical);
    (*body).setSpacing(8.000000);
    Math::Offsets padding_7;
    padding_7.Top = 8.000000;
    padding_7.Right = 8.000000;
    padding_7.Bottom = 8.000000;
    padding_7.Left = 8.000000;
    (*body).setPadding(padding_7);
    SharedReference<UI::Label> nameLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*nameLabel).setName("NameLabel");
    {
    }
    (*nameLabel).setText("Name");
    (*body).addView(nameLabel);
    nameView = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*nameView).setName("NameView");
    {
    }
    (*body).addView(nameView);
    SharedReference<UI::Label> parametersLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*parametersLabel).setName("ParametersLabel");
    {
    }
    (*parametersLabel).setText("Parameters");
    (*body).addView(parametersLabel);
    parametersAddButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*parametersAddButton).setName("ParametersAddButton");
    {
    }
    (*parametersAddButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*parametersAddButton).setText("Add");
    (*body).addView(parametersAddButton);
    parametersView = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*parametersView).setName("ParametersView");
    {
    }
    (*parametersView).setAffectsParentLayout(true);
    (*body).addView(parametersView);
    (*this).body = body;
    Super::onHierarchyCreate();
    setName("EventDetailsView");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
