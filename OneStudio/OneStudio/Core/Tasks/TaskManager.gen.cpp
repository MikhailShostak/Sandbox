//CLASSGEN GENERATED REGION: Includes
#include "TaskManager.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

void TaskManager::onApplicationStart(const AApplication &application)
{
    onLoad();
}

void TaskManager::onLoad()
{
    view = CreateShared<OneStudio::TasksProgressView>();
    view->taskList->OnTreeItemTapped = [this](UI::TapGestureEvent &Event, PlainReference<OneStudio::Task> Item)
    {
        logView->setText(Item->log | rngv::join("\n") | rng::to<std::string>());
    };

    logView = CreateShared<UI::TextField>();
    logView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::Expanded);
}

SharedReference<OneStudioPlatform::Task> TaskManager::startTask()
{
    SharedReference<OneStudio::Task> task = CreateShared<OneStudio::Task>();

    view->taskList->items.push_back(task);
    task->onUpdated = [this](){
        view->taskList->notifyUpdateAllItems();
    };
    task->onSubtaskAdded = [this](){
        view->taskList->notifyUpdateAllItems();
    };
    //view->taskList->notifyInsertItems(taskManager.tasksView->items.size() - 1);
    view->taskList->notifyUpdateAllItems();
    return task;
}

void TaskManager::finishTask(const SharedReference<OneStudioPlatform::Task>& task)
{

}

void TaskManager::clearTasks()
{

}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
