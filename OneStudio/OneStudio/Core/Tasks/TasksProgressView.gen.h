#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

#include "Foundation"
#include "ExperimentalDebug"
#include "TasksWidget.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TasksProgressView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TasksProgressView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    TasksProgressView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void executeCommand();
    SharedReference<UI::GroupPanel> tasksGroupView;
        SharedReference<OneStudio::TasksWidget> taskList;
    SharedReference<UI::GroupPanel> commandsGroupPanel;
        SharedReference<UI::TextField> commandLineField;
        SharedReference<UI::TextButton> commandLineRunButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
void onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    tasksGroupView->headerLabel->setText("Tasks");
    commandsGroupPanel->headerLabel->setText("Command Line");
}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
