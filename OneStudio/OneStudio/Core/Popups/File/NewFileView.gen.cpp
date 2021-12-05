//CLASSGEN GENERATED REGION: Includes
#include "NewFileView.gen.h"
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
NewFileView::NewFileView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    UI::FlexBoxData item_401_0;
    item_401_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_403_1;
    item_403_1.Alignment = Core::Alignment::End;
    (*this).setData({item_401_0,item_403_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_407;
    padding_407.Top = 8.000000;
    padding_407.Right = 8.000000;
    padding_407.Bottom = 8.000000;
    padding_407.Left = 8.000000;
    (*this).setPadding(padding_407);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NewFileView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void NewFileView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NewFileView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("NewFileView");
    SharedReference<UI::FlexBox> pathGroup = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*pathGroup).setName("PathGroup");
    {
    }
    (*pathGroup).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*pathGroup).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_360_0;
    item_360_0.Alignment = Core::Alignment::Start;
    (*pathGroup).setData({item_360_0,});
    (*pathGroup).setDirection(UI::Direction::Horizontal);
    (*pathGroup).setSpacing(0.000000);
    Math::Offsets padding_364;
    padding_364.Top = 0.000000;
    padding_364.Right = 0.000000;
    padding_364.Bottom = 0.000000;
    padding_364.Left = 0.000000;
    (*pathGroup).setPadding(padding_364);
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
    Math::Offsets padding_373;
    padding_373.Top = 0.000000;
    padding_373.Right = 0.000000;
    padding_373.Bottom = 0.000000;
    padding_373.Left = 0.000000;
    (*pathField).setPadding(padding_373);
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
    UI::FlexBoxData item_381_0;
    item_381_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_383_1;
    item_383_1.Alignment = Core::Alignment::Start;
    (*buttonsGroup).setData({item_381_0,item_383_1,});
    (*buttonsGroup).setDirection(UI::Direction::Horizontal);
    (*buttonsGroup).setSpacing(8.000000);
    Math::Offsets padding_387;
    padding_387.Top = 0.000000;
    padding_387.Right = 0.000000;
    padding_387.Bottom = 0.000000;
    padding_387.Left = 0.000000;
    (*buttonsGroup).setPadding(padding_387);
    createButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*createButton).setName("CreateButton");
    {
    }
    (*createButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*createButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*createButton).setText("Create");
    (*buttonsGroup).addView(createButton);
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
void NewFileView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    createButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        OneStudio::FileManager::getThisInstance().newFile(pathField->pathField->getText());
        OneStudioFlow::sm.popState();
    });

    cancelButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        OneStudioFlow::sm.popState();
    });
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
