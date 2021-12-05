//CLASSGEN GENERATED REGION: Includes
#include "ToolbarSettingsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "WindowManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ToolbarSettingsView::ToolbarSettingsView()
{
    Math::IntegerVector size_800;
    size_800.X = 400.000000;
    size_800.Y = 400.000000;
    size_800.Z = 0.000000;
    size_800.W = 0.000000;
    (*this).setSize(size_800);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    UI::FlexBoxData item_808_0;
    item_808_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_810_1;
    item_810_1.Alignment = Core::Alignment::End;
    (*this).setData({item_808_0,item_810_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_814;
    padding_814.Top = 8.000000;
    padding_814.Right = 8.000000;
    padding_814.Bottom = 8.000000;
    padding_814.Left = 8.000000;
    (*this).setPadding(padding_814);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ToolbarSettingsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ToolbarSettingsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ToolbarSettingsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ToolbarSettingsView");
    SharedReference<UI::FlexBox> content = CreateShared<UI::FlexBox>();
    (*content).setName("Content");
    (*content).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_760_0;
    item_760_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_762_1;
    item_762_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_764_2;
    item_764_2.Alignment = Core::Alignment::Start;
    (*content).setData({item_760_0,item_762_1,item_764_2,});
    (*content).setDirection(UI::Direction::Horizontal);
    (*content).setSpacing(8.000000);
    Math::Offsets padding_768;
    padding_768.Top = 0.000000;
    padding_768.Right = 0.000000;
    padding_768.Bottom = 0.000000;
    padding_768.Left = 0.000000;
    (*content).setPadding(padding_768);
    currentItems = CreateShared<UI::ListView>();
    (*currentItems).setName("CurrentItems");
    (*currentItems).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*currentItems).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*content).addView(currentItems);
    addButton = CreateShared<UI::TextButton>();
    (*addButton).setName("AddButton");
    (*addButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*addButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*addButton).setText("+");
    (*content).addView(addButton);
    availableItems = CreateShared<UI::ListView>();
    (*availableItems).setName("AvailableItems");
    (*availableItems).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*availableItems).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*content).addView(availableItems);
    (*this).addView(content);
    SharedReference<UI::FlexBox> buttons = CreateShared<UI::FlexBox>();
    (*buttons).setName("Buttons");
    (*buttons).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*buttons).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::FlexBoxData item_783_0;
    item_783_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_785_1;
    item_785_1.Alignment = Core::Alignment::Start;
    (*buttons).setData({item_783_0,item_785_1,});
    (*buttons).setDirection(UI::Direction::Horizontal);
    (*buttons).setSpacing(0.000000);
    Math::Offsets padding_789;
    padding_789.Top = 0.000000;
    padding_789.Right = 0.000000;
    padding_789.Bottom = 0.000000;
    padding_789.Left = 0.000000;
    (*buttons).setPadding(padding_789);
    saveButton = CreateShared<UI::TextButton>();
    (*saveButton).setName("SaveButton");
    (*saveButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*saveButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*saveButton).setText("Save");
    (*buttons).addView(saveButton);
    cancelButton = CreateShared<UI::TextButton>();
    (*cancelButton).setName("CancelButton");
    (*cancelButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*cancelButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*cancelButton).setText("Cancel");
    (*buttons).addView(cancelButton);
    (*this).addView(buttons);
}
//CLASSGEN END REGION

void ToolbarSettingsView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    currentItems->setAdapter(this);
    availableItems->setAdapter(this);
}

UI::SizeType ToolbarSettingsView::getCountItems(const AObject &sender) const
{
    if (&sender == currentItems.get())
    {
        return WindowManager::getThisInstance().getCurrentToolbarCommands().size();
    }
    else if(&sender == availableItems.get())
    {
        return WindowManager::getThisInstance().getAvailableToolbarCommands().size();
    }
}

SharedReference<UI::View> ToolbarSettingsView::provideViewForItem(const AObject &sender, UI::SizeType index)
{
    if (&sender == currentItems.get())
    {
        auto commands = WindowManager::getThisInstance().getCurrentToolbarCommands();
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(commands[index]);
        return v;
    }
    else if (&sender == availableItems.get())
    {
        auto commands = WindowManager::getThisInstance().getAvailableToolbarCommands();
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(commands[index].getIdentifier());
        return v;
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
