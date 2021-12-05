//CLASSGEN GENERATED REGION: Includes
#include "TaskView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TaskView::TaskView()
{
    Math::Transform transform_426;
    Math::Vector position_427;
    position_427.X = 0.000000;
    position_427.Y = 0.000000;
    position_427.Z = 0.000000;
    position_427.W = 0.000000;
    transform_426.Position = position_427;
    Math::Quaternion rotation_432;
    rotation_432.X = 0.000000;
    rotation_432.Y = 0.000000;
    rotation_432.Z = 0.000000;
    rotation_432.W = 1.000000;
    transform_426.Rotation = rotation_432;
    (*this).setTransform(transform_426);
    Math::IntegerVector size_437;
    size_437.X = 800.000000;
    size_437.Y = 200.000000;
    size_437.Z = 0.000000;
    size_437.W = 0.000000;
    (*this).setSize(size_437);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_450_0;
    item_450_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_452_1;
    item_452_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_450_0,item_452_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_456;
    padding_456.Top = 0.000000;
    padding_456.Right = 0.000000;
    padding_456.Bottom = 0.000000;
    padding_456.Left = 0.000000;
    (*this).setPadding(padding_456);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TaskView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TaskView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TaskView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TaskView");
    header = Create<UI::FlexBox>();
    (*header).setName("Header");
    {
    }
    Math::Transform transform_265;
    Math::Vector position_266;
    position_266.X = 0.000000;
    position_266.Y = 0.000000;
    position_266.Z = 0.000000;
    position_266.W = 0.000000;
    transform_265.Position = position_266;
    Math::Quaternion rotation_271;
    rotation_271.X = 0.000000;
    rotation_271.Y = 0.000000;
    rotation_271.Z = 0.000000;
    rotation_271.W = 1.000000;
    transform_265.Rotation = rotation_271;
    (*header).setTransform(transform_265);
    Math::IntegerVector size_276;
    size_276.X = 0.000000;
    size_276.Y = 0.000000;
    size_276.Z = 0.000000;
    size_276.W = 0.000000;
    (*header).setSize(size_276);
    (*header).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*header).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*header).setAffectsParentLayout(false);
    UI::FlexBoxData item_285_0;
    item_285_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_287_1;
    item_287_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_289_2;
    item_289_2.Alignment = Core::Alignment::Center;
    (*header).setData({item_285_0,item_287_1,item_289_2,});
    (*header).setDirection(UI::Direction::Horizontal);
    (*header).setSpacing(8.000000);
    Math::Offsets padding_293;
    padding_293.Top = 8.000000;
    padding_293.Right = 8.000000;
    padding_293.Bottom = 8.000000;
    padding_293.Left = 8.000000;
    (*header).setPadding(padding_293);
    descriptionTextField = Create<UI::TextField>();
    (*descriptionTextField).setName("DescriptionTextField");
    {
    }
    Math::Transform transform_298;
    Math::Vector position_299;
    position_299.X = 0.000000;
    position_299.Y = 0.000000;
    position_299.Z = 0.000000;
    position_299.W = 0.000000;
    transform_298.Position = position_299;
    Math::Quaternion rotation_304;
    rotation_304.X = 0.000000;
    rotation_304.Y = 0.000000;
    rotation_304.Z = 0.000000;
    rotation_304.W = 1.000000;
    transform_298.Rotation = rotation_304;
    (*descriptionTextField).setTransform(transform_298);
    Math::IntegerVector size_309;
    size_309.X = 0.000000;
    size_309.Y = 0.000000;
    size_309.Z = 0.000000;
    size_309.W = 0.000000;
    (*descriptionTextField).setSize(size_309);
    (*descriptionTextField).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*descriptionTextField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*descriptionTextField).setAffectsParentLayout(false);
    (*descriptionTextField).setPlaceholder("Title");
    (*header).addView(descriptionTextField);
    separator = Create<UI::ImageView>();
    (*separator).setName("Separator");
    {
    }
    Math::Transform transform_318;
    Math::Vector position_319;
    position_319.X = 0.000000;
    position_319.Y = 0.000000;
    position_319.Z = 0.000000;
    position_319.W = 0.000000;
    transform_318.Position = position_319;
    Math::Quaternion rotation_324;
    rotation_324.X = 0.000000;
    rotation_324.Y = 0.000000;
    rotation_324.Z = 0.000000;
    rotation_324.W = 1.000000;
    transform_318.Rotation = rotation_324;
    (*separator).setTransform(transform_318);
    Math::IntegerVector size_329;
    size_329.X = 0.000000;
    size_329.Y = 0.000000;
    size_329.Z = 0.000000;
    size_329.W = 0.000000;
    (*separator).setSize(size_329);
    (*separator).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*separator).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*separator).setAffectsParentLayout(false);
    (*header).addView(separator);
    visibilityButton = Create<UI::ImageView>();
    (*visibilityButton).setName("VisibilityButton");
    {
    }
    Math::Transform transform_337;
    Math::Vector position_338;
    position_338.X = 0.000000;
    position_338.Y = 0.000000;
    position_338.Z = 0.000000;
    position_338.W = 0.000000;
    transform_337.Position = position_338;
    Math::Quaternion rotation_343;
    rotation_343.X = 0.000000;
    rotation_343.Y = 0.000000;
    rotation_343.Z = 0.000000;
    rotation_343.W = 1.000000;
    transform_337.Rotation = rotation_343;
    (*visibilityButton).setTransform(transform_337);
    Math::IntegerVector size_348;
    size_348.X = 0.000000;
    size_348.Y = 0.000000;
    size_348.Z = 0.000000;
    size_348.W = 0.000000;
    (*visibilityButton).setSize(size_348);
    (*visibilityButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*visibilityButton).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*visibilityButton).setAffectsParentLayout(false);
    (*header).addView(visibilityButton);
    (*this).addView(header);
    contentView = Create<UI::FlexBox>();
    (*contentView).setName("ContentView");
    {
    }
    Math::Transform transform_356;
    Math::Vector position_357;
    position_357.X = 0.000000;
    position_357.Y = 0.000000;
    position_357.Z = 0.000000;
    position_357.W = 0.000000;
    transform_356.Position = position_357;
    Math::Quaternion rotation_362;
    rotation_362.X = 0.000000;
    rotation_362.Y = 0.000000;
    rotation_362.Z = 0.000000;
    rotation_362.W = 1.000000;
    transform_356.Rotation = rotation_362;
    (*contentView).setTransform(transform_356);
    Math::IntegerVector size_367;
    size_367.X = 0.000000;
    size_367.Y = 0.000000;
    size_367.Z = 0.000000;
    size_367.W = 0.000000;
    (*contentView).setSize(size_367);
    (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*contentView).setAffectsParentLayout(false);
    UI::FlexBoxData item_376_0;
    item_376_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_378_1;
    item_378_1.Alignment = Core::Alignment::Start;
    (*contentView).setData({item_376_0,item_378_1,});
    (*contentView).setDirection(UI::Direction::Vertical);
    (*contentView).setSpacing(0.000000);
    Math::Offsets padding_382;
    padding_382.Top = 0.000000;
    padding_382.Right = 0.000000;
    padding_382.Bottom = 0.000000;
    padding_382.Left = 0.000000;
    (*contentView).setPadding(padding_382);
    packageField = Create<UI::TextField>();
    (*packageField).setName("PackageField");
    {
    }
    Math::Transform transform_387;
    Math::Vector position_388;
    position_388.X = 0.000000;
    position_388.Y = 0.000000;
    position_388.Z = 0.000000;
    position_388.W = 0.000000;
    transform_387.Position = position_388;
    Math::Quaternion rotation_393;
    rotation_393.X = 0.000000;
    rotation_393.Y = 0.000000;
    rotation_393.Z = 0.000000;
    rotation_393.W = 1.000000;
    transform_387.Rotation = rotation_393;
    (*packageField).setTransform(transform_387);
    Math::IntegerVector size_398;
    size_398.X = 0.000000;
    size_398.Y = 0.000000;
    size_398.Z = 0.000000;
    size_398.W = 0.000000;
    (*packageField).setSize(size_398);
    (*packageField).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*packageField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*packageField).setAffectsParentLayout(false);
    (*packageField).setPlaceholder("Package");
    (*contentView).addView(packageField);
    argumentsListView = Create<UI::ListView>();
    (*argumentsListView).setName("ArgumentsListView");
    {
    }
    Math::Transform transform_407;
    Math::Vector position_408;
    position_408.X = 0.000000;
    position_408.Y = 0.000000;
    position_408.Z = 0.000000;
    position_408.W = 0.000000;
    transform_407.Position = position_408;
    Math::Quaternion rotation_413;
    rotation_413.X = 0.000000;
    rotation_413.Y = 0.000000;
    rotation_413.Z = 0.000000;
    rotation_413.W = 1.000000;
    transform_407.Rotation = rotation_413;
    (*argumentsListView).setTransform(transform_407);
    Math::IntegerVector size_418;
    size_418.X = 0.000000;
    size_418.Y = 0.000000;
    size_418.Z = 0.000000;
    size_418.W = 0.000000;
    (*argumentsListView).setSize(size_418);
    (*argumentsListView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*argumentsListView).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*argumentsListView).setAffectsParentLayout(false);
    (*contentView).addView(argumentsListView);
    (*this).addView(contentView);
}
//CLASSGEN END REGION

void TaskView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    argumentsListView->setAdapter(this);

    //THIS CODE COPIED FROM TabItem.cpp (UI::TabItem)
    Array<uint8_t> data;
    data.resize(4 * 4);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            data[i * 4 + j] = (i == 0 && j == 0 || i == 2 && j == 2) ? 0x23 : 0x33;
        }
    }

    APixmap pixmap;
    pixmap.setBuffer(data, { 4, 4 }, APixmapDataFormat::Gray);

    SharedReference<Graphics::Texture> t = new Graphics::Texture();
    t->setPixmap(pixmap);
    t->setWrapping(Graphics::TextureWrapping::TiledWrapping);
    t->load();

    separator->setImage(t);
    separator->setVerticalSizePolicy(UI::SizePolicy::Fixed);
    separator->setSize({ 5, 5 });

    contentView->setExpanded(false);
    visibilityButton->addGestureRecognizer(new UI::TouchGestureRecognizer());
    visibilityButton->setImage(::DownButtonSmall);
    visibilityButton->eventChannel.registerDelegate([this](UI::TapGestureEvent &event) {
        contentView->setExpanded(!contentView->isExpanded());
        visibilityButton->setImage(contentView->isExpanded() ? SharedReference<Graphics::Texture>(::UpButtonSmall) : SharedReference<Graphics::Texture>(::DownButtonSmall));
    });

    descriptionTextField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
        taskData.Title = event.getText();
        TaskChanged();
    });

    packageField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
        taskData.Type = event.getText();
        argumentsListView->notifyUpdateAllItems();
        TaskChanged();
    });
}


bool TaskView::isContentVisible() const
{
    //return ui->content->isVisible();
    return false;
}

void TaskView::setContentVisible(bool visible)
{
    /* ui->content->setVisible(visible);
     ui->contentButton->setText(visible ?  QChar(0xF106) : QChar(0xF107));*/
}

UI::View *createBooleanView(const String &value, const String &arguments, const std::function<void(const String &value)> &callback)
{
    UI::Switch *switchView = createNew<UI::Switch>();
    switchView->setOn(value == "true");
    switchView->eventChannel.registerDelegate<UI::SwitchEvent>([&value, callback](UI::SwitchEvent &event) {
        callback(event.getValue() ? "true" : "false");
    });
    return switchView;
}

UI::View *createStringView(const String &value, const String &arguments, const std::function<void(const String &value)> &callback)
{
    UI::TextField *textField = createNew<UI::TextField>();
    textField->setText(value);
    textField->eventChannel.registerDelegate<UI::TextEditFinishedEvent>([&value, callback](UI::TextEditFinishedEvent &event) {
        callback(event.getText());
    });
    return textField;
}

UI::View *createPathView(const String &value, const String &arguments, const std::function<void(const String &value)> &callback)
{
    UI::TextField *textField = createNew<UI::TextField>();
    textField->setText(value);
    textField->eventChannel.registerDelegate<UI::TextEditFinishedEvent>([&value, callback](UI::TextEditFinishedEvent &event) {
        callback(event.getText());
    });
    return textField;
}

UI::View *createTextView(const String &value, const String &arguments, const std::function<void(const String &value)> &callback)
{
    UI::TextField *textField = createNew<UI::TextField>(); //TODO: multiline text
    textField->setText(value);
    textField->eventChannel.registerDelegate<UI::TextEditFinishedEvent>([&value, callback](UI::TextEditFinishedEvent &event) {
        callback(value);
    });
    return textField;
}

UI::View *createListView(const String &value, const String &arguments, const std::function<void(const String &value)> &callback)
{
    UI::DropDownList *view = createNew<UI::DropDownList>();
    view->setElements(arguments.split(','));
    view->setCurrentIndex(view->getElements().indexOf(value));
    return view;
}

void TaskView::updateData()
{
    if (!taskData.Type)
    {
        return;
    }

    descriptionTextField->setText(taskData.Title);
    packageField->setText(taskData.Type);

    argumentsListView->notifyUpdateAllItems();
}

UI::SizeType TaskView::getCountItems(const AObject &sender) const
{
    if (!taskData.Type || !task)
    {
        return 0;
    }

    return task->getProperties().size();
}
SharedReference<UI::View> TaskView::provideViewForItem(const AObject &sender, UI::SizeType index)
{
    UI::View *view = nullptr;
    auto definedProperties = task->getProperties();

    auto definedProperty = task->getProperties()[index];
    Array<String> data = definedProperty.second.split(':');
    String name = data.first();
    String arguments = data.last();

    auto &value = taskData.Values[name];

    ALogMessage("Info", "[%s] %s = %s", taskData.Title, name, value);
    auto callback = [this, &value](const String &v) { value = v; TaskChanged(); };
    switch (definedProperty.first)
    {
    case OSTargetTask::Boolean:
        view = createBooleanView(value, arguments, callback);
        break;
    case OSTargetTask::String:
        view = createStringView(value, arguments, callback);
        break;
    case OSTargetTask::Path:
        view = createPathView(value, arguments, callback);
        break;
    case OSTargetTask::Text:
        view = createTextView(value, arguments, callback);
        break;
    case OSTargetTask::List:
        view = createListView(value, arguments, callback);
        break;
    }

    UI::FlexBox *itemView = new UI::FlexBox();
    itemView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);

    SharedReference<UI::Label> nameView = new UI::Label(name);
    nameView->setSizePolicy(UI::SizePolicy::Fixed, UI::SizePolicy::ContentWrapped);
    nameView->setSize(Math::IntegerVector{ 150, 0 });
    itemView->addView(nameView);

    view->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    itemView->addView(view);

    itemView->setData({ {}, {} });

    return itemView;
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
