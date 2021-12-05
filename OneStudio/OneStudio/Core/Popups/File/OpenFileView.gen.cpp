//CLASSGEN GENERATED REGION: Includes
#include "OpenFileView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "OneStudioFlow.gen.h"
#include "FileManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
OpenFileView::OpenFileView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    UI::FlexBoxData item_453_0;
    item_453_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_455_1;
    item_455_1.Alignment = Core::Alignment::End;
    (*this).setData({item_453_0,item_455_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_459;
    padding_459.Top = 8.000000;
    padding_459.Right = 8.000000;
    padding_459.Bottom = 8.000000;
    padding_459.Left = 8.000000;
    (*this).setPadding(padding_459);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void OpenFileView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void OpenFileView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void OpenFileView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("OpenFileView");
    SharedReference<UI::FlexBox> pathGroup = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*pathGroup).setName("PathGroup");
    {
    }
    (*pathGroup).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*pathGroup).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_412_0;
    item_412_0.Alignment = Core::Alignment::Start;
    (*pathGroup).setData({item_412_0,});
    (*pathGroup).setDirection(UI::Direction::Horizontal);
    (*pathGroup).setSpacing(0.000000);
    Math::Offsets padding_416;
    padding_416.Top = 0.000000;
    padding_416.Right = 0.000000;
    padding_416.Bottom = 0.000000;
    padding_416.Left = 0.000000;
    (*pathGroup).setPadding(padding_416);
    pathField = CreateShared<UI::PathField>([this](UI::PathField *v)
    {
    }
);
    (*pathField).setName("PathField");
    {
    }
    (*pathField).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*pathField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*pathField).setDirection(UI::Direction::Horizontal);
    (*pathField).setSpacing(0.000000);
    Math::Offsets padding_425;
    padding_425.Top = 0.000000;
    padding_425.Right = 0.000000;
    padding_425.Bottom = 0.000000;
    padding_425.Left = 0.000000;
    (*pathField).setPadding(padding_425);
    (*pathGroup).addView(pathField);
    (*this).addView(pathGroup);
    SharedReference<UI::FlexBox> buttonsGroup = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*buttonsGroup).setName("ButtonsGroup");
    {
    }
    (*buttonsGroup).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*buttonsGroup).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_433_0;
    item_433_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_435_1;
    item_435_1.Alignment = Core::Alignment::Start;
    (*buttonsGroup).setData({item_433_0,item_435_1,});
    (*buttonsGroup).setDirection(UI::Direction::Horizontal);
    (*buttonsGroup).setSpacing(8.000000);
    Math::Offsets padding_439;
    padding_439.Top = 0.000000;
    padding_439.Right = 0.000000;
    padding_439.Bottom = 0.000000;
    padding_439.Left = 0.000000;
    (*buttonsGroup).setPadding(padding_439);
    openButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*openButton).setName("OpenButton");
    {
    }
    (*openButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*openButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*openButton).setText("Open");
    (*buttonsGroup).addView(openButton);
    cancelButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*cancelButton).setName("CancelButton");
    {
    }
    (*cancelButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*cancelButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*cancelButton).setText("Cancel");
    (*buttonsGroup).addView(cancelButton);
    (*this).addView(buttonsGroup);
}
//CLASSGEN END REGION
void OpenFileView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    openButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        OneStudio::FileManager::getThisInstance().openFile(pathField->pathField->getText());
        OneStudioFlow::sm.popState();
    });

    cancelButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        OneStudioFlow::sm.popState();
    });
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
