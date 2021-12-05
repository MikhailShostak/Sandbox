//CLASSGEN GENERATED REGION: Includes
#include "GroupPanel.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "MathClasses"
#include "Math"

//CLASSGEN END REGION
#include "FlexBox.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GroupPanel::GroupPanel()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GroupPanel::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void GroupPanel::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GroupPanel::onHierarchyCreate()
{
    SharedReference<UI::FlexBox> root = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*root).setName("Root");
    {
    }
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    (*root).setData({item_0_0,item_1_1,});
    (*root).setDirection(UI::Direction::Vertical);
    if (header)
    {
        (*root).addView(header);
    }
    else
    {
        SharedReference<UI::Overlay> defaultHeader = CreateShared<UI::Overlay>([this](UI::Overlay *v)
        {
        }
);
        (*defaultHeader).setName("DefaultHeader");
        {
        }
        UI::OverlayData item_2_0;
        UI::OverlayData item_3_1;
        Math::Offsets padding_4;
        padding_4.Top = 4.000000;
        padding_4.Right = 8.000000;
        padding_4.Bottom = 4.000000;
        padding_4.Left = 8.000000;
        item_3_1.Padding = padding_4;
        (*defaultHeader).setData({item_2_0,item_3_1,});
        headerBackground = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
        {
        }
);
        (*headerBackground).setName("HeaderBackground");
        {
        }
        (*headerBackground).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*headerBackground).setUseOriginalContentSize(false);
        (*defaultHeader).addView(headerBackground);
        headerLabel = CreateShared<UI::Label>([this](UI::Label *v)
        {
        }
);
        (*headerLabel).setName("HeaderLabel");
        {
        }
        (*headerLabel).setText("Header");
        (*defaultHeader).addView(headerLabel);
        (*root).addView(defaultHeader);
        header = defaultHeader;
    }
    if (body)
    {
        (*root).addView(body);
    }
    else
    {
        SharedReference<UI::Label> defaultHeader = CreateShared<UI::Label>([this](UI::Label *v)
        {
        }
);
        (*defaultHeader).setName("DefaultHeader");
        {
        }
        (*defaultHeader).setText("Body");
        (*root).addView(defaultHeader);
        body = defaultHeader;
    }
    (*this).root = root;
    Super::onHierarchyCreate();
    setName("GroupPanel");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
