#include "OSTaskItemView.h"

namespace UI
{

OSTaskItemView::OSTaskItemView()
{
    descriptionView = Create<TextField>();
    descriptionView->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
    addView(descriptionView);

    propertiesView = Create<ListView>();
    propertiesView->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
    propertiesView->setExpanded(false);
    addView(propertiesView);

    expandButton = Create<TextButton>();
    expandButton->setText("+");
    expandButton->setSize(Math::IntegerVector{ 24, 24 });
    expandButton->setSizePolicy(SizePolicy::Fixed);
    expandButton->eventChannel.registerDelegate<TapGestureEvent>([this](TapGestureEvent &event)
    {
        propertiesView->setExpanded(!propertiesView->isExpanded());
        expandButton->setText(propertiesView->isExpanded() ? "-" : "+");
    });
    addView(expandButton);

    RelativeLayout* relativeLayout = new RelativeLayout();

    relativeLayout->addConstraint(*expandButton, ConstraintAnchor::Top, *this, ConstraintAnchor::Top);
    relativeLayout->addConstraint(*expandButton, ConstraintAnchor::Left, *this, ConstraintAnchor::Left);

    relativeLayout->addConstraint(*descriptionView, ConstraintAnchor::Left, *expandButton, ConstraintAnchor::Right, 4);
    relativeLayout->addConstraint(*descriptionView, ConstraintAnchor::Top, *this, ConstraintAnchor::Top);
    relativeLayout->addConstraint(*descriptionView, ConstraintAnchor::Right, *this, ConstraintAnchor::Right);

    relativeLayout->addConstraint(*propertiesView, ConstraintAnchor::Top, *descriptionView, ConstraintAnchor::Bottom, 4);
    relativeLayout->addConstraint(*propertiesView, ConstraintAnchor::Left, *this, ConstraintAnchor::Left);
    relativeLayout->addConstraint(*propertiesView, ConstraintAnchor::Right, *this, ConstraintAnchor::Right);
    relativeLayout->addConstraint(*propertiesView, ConstraintAnchor::Bottom, *this, ConstraintAnchor::Bottom);
    setLayout(relativeLayout);

    setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);

    propertiesView->setAdapter(this);

    /*ui->content->setVisible(false);

    connect(ui->descriptionFieldView, &QLineEdit::editingFinished, [this] {
        if (taskData)
        {
            taskData->setDescription(ui->descriptionFieldView->text().toUtf8().data());
        }
    });
    connect(ui->upButton, &QPushButton::clicked, this, &OSTaskItemView::up);
    connect(ui->downButton, &QPushButton::clicked, this, &OSTaskItemView::down);
    connect(ui->removeButton, &QPushButton::clicked, this, &OSTaskItemView::remove);*/
}

OSTaskItemView::~OSTaskItemView()
{
    /*views.clear();
    delete ui;*/
}

bool OSTaskItemView::isContentVisible() const
{
    //return ui->content->isVisible();
    return false;
}

void OSTaskItemView::setContentVisible(bool visible)
{
   /* ui->content->setVisible(visible);
    ui->contentButton->setText(visible ?  QChar(0xF106) : QChar(0xF107));*/
}

View *createBooleanView(const SharedReference<OSTaskPropertyDataObject> &property, const String &arguments)
{
    Switch *switchView = createNew<Switch>();
    switchView->setOn(property->getValue() == "true");
    switchView->eventChannel.registerDelegate<SwitchEvent>([property](SwitchEvent &event) {
        property->setValue(event.getValue() ? "true" : "false");
    });
    return switchView;
}

View *createStringView(const SharedReference<OSTaskPropertyDataObject> &property, const String &arguments)
{
    TextField *textField = createNew<TextField>();
    textField->setText(property->getValue());
    textField->eventChannel.registerDelegate<TextEditFinishedEvent>([property](TextEditFinishedEvent &event) {
        property->setValue(event.getText());
    });
    return textField;
}

View *createPathView(const SharedReference<OSTaskPropertyDataObject> &property, const String &arguments)
{
    TextField *textField = createNew<TextField>();
    textField->setText(property->getValue());
    textField->eventChannel.registerDelegate<TextEditFinishedEvent>([property](TextEditFinishedEvent &event) {
        property->setValue(event.getText());
    });
    return textField;
}

View *createTextView(const SharedReference<OSTaskPropertyDataObject> &property, const String &arguments)
{
    TextField *textField = createNew<TextField>(); //TODO: multiline text
    textField->setText(property->getValue());
    textField->eventChannel.registerDelegate<TextEditFinishedEvent>([property](TextEditFinishedEvent &event) {
        property->setValue(event.getText());
    });
    return textField;
}

View *createListView(const SharedReference<OSTaskPropertyDataObject> &property, const String &arguments)
{
    DropDownList *view = createNew<DropDownList>();
    view->setElements(arguments.split(','));
    view->setCurrentIndex(view->getElements().indexOf(property->getValue()));
    return view;
}

void OSTaskItemView::updateData()
{
    if(!target || !taskData) {
        return;
    }

    /*ui->descriptionFieldView->setText();
    ui->packageLabel->setText(fmt::format("({})", task->getName()).toUtf8().data());*/

    properties = target->findTaskProperties(taskData);

    if (!task)
    {
        descriptionView->setText(fmt::format("{} - Undefined task ({})", taskData->getDescription(), taskData->getPackage()));
        expandButton->setExpanded(false);
        propertiesView->setExpanded(false);
        return;
    }

    auto definedProperties = task->getProperties();
    if (definedProperties.isEmpty())
    {
        expandButton->setExpanded(false);
        propertiesView->setExpanded(false);
        return;
    }
    descriptionView->setText(taskData->getDescription() ? taskData->getDescription() : taskData->getPackage());

    propertiesView->notifyUpdateAllItems();

    /*auto properties = target->findTaskProperties(taskData);
    for(auto &taskProperty : taskProperties)
    {
        Array<String> data = taskProperty.second.split(':');
        String name = data.first();
        String arguments = data.last();
        SharedReference<OSTaskPropertyDataObject> property;
        for(auto &p : properties)
        {
            if(p->getName() == name)
            {
                property = p;
                break;
            }
        }

        if(!property)
        {
            property = target->createTaskProperty(taskData);
            property->setName(name);
        }

        QWidget *view = nullptr;
        switch(taskProperty.first)
        {
        case OSTargetTask::Boolean:
            view = createBooleanWidget(property, arguments);
            break;
        case OSTargetTask::String:
            view = createStringWidget(property, arguments);
            break;
        case OSTargetTask::Path:
            view = createPathWidget(property, arguments);
            break;
        case OSTargetTask::Text:
            view = createTextWidget(property, arguments);
            break;
        case OSTargetTask::List:
            view = createListWidget(property, arguments);
            break;
        }
        views.append(view);
        static_cast<QFormLayout *>(ui->content->layout())->addRow(new QLabel(property->getName().toUtf8().data()), view);
    }*/
}

SizeType OSTaskItemView::getCountItems(const AObject &sender) const
{
    if (!target || !taskData || !task)
    {
        return 0;
    }

    return task->getProperties().size();
}
SharedReference<View> OSTaskItemView::provideViewForItem(const AObject &sender, SizeType index)
{
    View *view = nullptr;
    auto definedProperties = task->getProperties();

    auto definedProperty = task->getProperties()[index];
    Array<String> data = definedProperty.second.split(':');
    String name = data.first();
    String arguments = data.last();
    SharedReference<OSTaskPropertyDataObject> currentPropertyData;
    for (auto &propertyData : properties)
    {
        if (propertyData->getName() == name)
        {
            currentPropertyData = propertyData;
            break;
        }
    }

    if (!currentPropertyData)
    {
        ALogMessage("Info", "Task property (%s) is not found. It will be created", name);
        currentPropertyData = target->createTaskProperty(taskData);
        currentPropertyData->setName(name);
    }

    ALogMessage("Info", "[%s] %s = %s", taskData->getDescription(), currentPropertyData->getName(), currentPropertyData->getValue());

    switch (definedProperty.first)
    {
    case OSTargetTask::Boolean:
        view = createBooleanView(currentPropertyData, arguments);
        break;
    case OSTargetTask::String:
        view = createStringView(currentPropertyData, arguments);
        break;
    case OSTargetTask::Path:
        view = createPathView(currentPropertyData, arguments);
        break;
    case OSTargetTask::Text:
        view = createTextView(currentPropertyData, arguments);
        break;
    case OSTargetTask::List:
        view = createListView(currentPropertyData, arguments);
        break;
    }

    View *itemView = new View();
    itemView->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);

    RelativeLayout *layout = new RelativeLayout();

    SharedReference<Label> nameView = new Label(currentPropertyData->getName());
    nameView->setSizePolicy(SizePolicy::Fixed, SizePolicy::ContentWrapped);
    nameView->setSize(Math::IntegerVector{150, 20});
    itemView->addView(nameView);

    view->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
    itemView->addView(view);

    layout->addConstraint(*nameView, ConstraintAnchor::Left, *itemView, ConstraintAnchor::Left);
    layout->addConstraint(*nameView, ConstraintAnchor::Top, *itemView, ConstraintAnchor::Top);
    layout->addConstraint(*nameView, ConstraintAnchor::Bottom, *itemView, ConstraintAnchor::Bottom);

    layout->addConstraint(*view, ConstraintAnchor::Left, *nameView, ConstraintAnchor::Right);
    layout->addConstraint(*view, ConstraintAnchor::Top, *itemView, ConstraintAnchor::Top);
    layout->addConstraint(*view, ConstraintAnchor::Bottom, *itemView, ConstraintAnchor::Bottom);
    layout->addConstraint(*view, ConstraintAnchor::Right, *itemView, ConstraintAnchor::Right);
    itemView->setLayout(layout);

    return itemView;
}

/*void OSTaskItemView::changeContentVisibility()
{
    setContentVisible(!isContentVisible());
}*/

}
