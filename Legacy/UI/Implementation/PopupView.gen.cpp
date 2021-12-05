//CLASSGEN GENERATED REGION: Includes
#include "PopupView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "FlexBox.gen.h"
#include "Direction.gen.h"
#include "Label.gen.h"
#include "TextButton.gen.h"

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
PopupView::PopupView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::OverlayData item_530_0;
    item_530_0.HorizontalAlignment = Core::Alignment::Center;
    item_530_0.VerticalAlignment = Core::Alignment::Center;
    UI::OverlayData item_533_1;
    Math::Offsets padding_534;
    padding_534.Top = 9.000000;
    padding_534.Right = 9.000000;
    padding_534.Bottom = 9.000000;
    padding_534.Left = 9.000000;
    item_533_1.Padding = padding_534;
    item_533_1.HorizontalAlignment = Core::Alignment::Center;
    item_533_1.VerticalAlignment = Core::Alignment::Center;
    (*this).setData({item_530_0,item_533_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PopupView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PopupView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PopupView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("PopupView");
    if (background)
    {
        (*this).addView(background);
    }
    else
    {
        SharedReference<UI::BorderImageView> defaultPopupBackground = CreateShared<UI::BorderImageView>([this](UI::BorderImageView *v)
        {
        }
);
        (*defaultPopupBackground).setName("DefaultPopupBackground");
        {
        }
        (*defaultPopupBackground).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultPopupBackground).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        Math::Offsets border_493;
        border_493.Top = 42.000000;
        border_493.Right = 16.000000;
        border_493.Bottom = 16.000000;
        border_493.Left = 16.000000;
        (*defaultPopupBackground).setBorder(border_493);
        (*this).addView(defaultPopupBackground);
        background = defaultPopupBackground;
    }
    SharedReference<UI::FlexBox> contentView = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*contentView).setName("ContentView");
    {
    }
    (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_501_0;
    item_501_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_503_1;
    item_503_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_505_2;
    item_505_2.Alignment = Core::Alignment::Center;
    (*contentView).setData({item_501_0,item_503_1,item_505_2,});
    (*contentView).setDirection(UI::Direction::Vertical);
    (*contentView).setSpacing(12.000000);
    Math::Offsets padding_509;
    padding_509.Top = 4.000000;
    padding_509.Right = 4.000000;
    padding_509.Bottom = 4.000000;
    padding_509.Left = 4.000000;
    (*contentView).setPadding(padding_509);
    if (header)
    {
        (*contentView).addView(header);
    }
    else
    {
        SharedReference<UI::Label> title = CreateShared<UI::Label>([this](UI::Label *v)
        {
        }
);
        (*title).setName("Title");
        {
        }
        (*title).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
        (*title).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
        (*title).setText("Popup Title");
        (*title).setTextAlign(Core::TextAlign::Center);
        (*contentView).addView(title);
        header = title;
    }
    if (content)
    {
        (*contentView).addView(content);
    }
    else
    {
        SharedReference<UI::Label> noContentLabel = CreateShared<UI::Label>([this](UI::Label *v)
        {
        }
);
        (*noContentLabel).setName("NoContentLabel");
        {
        }
        (*noContentLabel).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*noContentLabel).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*noContentLabel).setText("No Content");
        (*noContentLabel).setTextAlign(Core::TextAlign::Center);
        (*contentView).addView(noContentLabel);
        content = noContentLabel;
    }
    if (footer)
    {
        (*contentView).addView(footer);
    }
    else
    {
        SharedReference<UI::TextButton> closeButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
        {
        }
);
        (*closeButton).setName("CloseButton");
        {
        }
        Math::IntegerVector size_522;
        size_522.Y = 20.000000;
        (*closeButton).setSize(size_522);
        (*closeButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
        (*closeButton).setVerticalSizePolicy(UI::SizePolicy::Fixed);
        (*closeButton).setText("Close");
        (*contentView).addView(closeButton);
        footer = closeButton;
    }
    (*this).addView(contentView);
}
//CLASSGEN END REGION

void PopupView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    background->setImage(::Popup);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
