#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "OneStudioPlatform"

//CLASSGEN END REGION
#include "TaskStatus.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class Task : public OneStudioPlatform::Task
{
    String title;
    Array<SharedReference<Task>> subtasks;
public:

    TaskStatus status = TaskStatus::Scheduled;

    bool IsActive() { return status == TaskStatus::Started || status == TaskStatus::Paused; }
    bool IsInterrupted() { return status == TaskStatus::Canceled || status == TaskStatus::Failed; }
    int error_code = 0;

    Array<String> log;

    ATimePoint<ASystemClock> startTime = ASystemClock::now();
    ATimePoint<ASystemClock> endTime = startTime;

    ADelegate<void()> onUpdated;
    ADelegate<void()> onSubtaskAdded;

    bool isExpanded = true;
    const Array<SharedReference<Task>> &getItems() const { return subtasks; }

    const String &getTitle() const
    {
        return title;
    }

    void setTitle(const String &title)
    {
        this->title = title;
        if (onUpdated)
        {
            onUpdated();
        }
    }
    const String &getText() const
    {
        return log[0];
    }

    void setText(const String &title)
    {
        //this->title = te;
        if (onUpdated)
        {
            onUpdated();
        }
    }

    void startInternal();

    void start();

    void pause()
    {
        status = TaskStatus::Paused;
        for(auto &subtask : subtasks)
        {
            subtask->pause();
        }
        if (onUpdated)
        {
            onUpdated();
        }
    }

    void cancel()
    {
        status = TaskStatus::Canceled;
        for(auto &subtask : subtasks)
        {
            subtask->cancel();
        }
        if (onUpdated)
        {
            onUpdated();
        }
    }

    std::function<void(OneStudio::Task &task)> action;
    void setAction(const std::function<void(OneStudioPlatform::Task &task)> &action) override { this->action = [this, action](OneStudio::Task &task) { action(task); }; }
    void Log(const String &line) override { this->log.push_back(line); }

    SharedReference<OneStudioPlatform::Task> createSubTask()
    {
        SharedReference<Task> task = CreateShared<Task>();
        subtasks.push_back(task);
        if (onSubtaskAdded)
        {
            onSubtaskAdded();
        }
        return task;
    }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
