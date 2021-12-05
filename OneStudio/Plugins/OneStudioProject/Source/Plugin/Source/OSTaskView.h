#pragma once

#include <Foundation>
#include <OneStudioProjectLibrary>

#include "OSTaskItemView.h"

namespace UI
{

class OSTaskView : public View
{
    //Q_OBJECT

    //Ui::OSTaskView *ui;

    String stepType;
    String placeholder;
    Array<OSTargetTask *> tasks;
    SharedReference<OSProjectTargetDataInstance> target;
    Array<SharedReference<OSTaskItemView>> views;

public:

    explicit OSTaskView();
    ~OSTaskView();

    String getTitle() const;
    void setTitle(const String &title);

    String getPlaceholder() const;
    void setPlaceholder(const String &placeholder);

    const String &getStepType() const
    {
        return this->stepType;
    }

    void setStepType(const String &stepType)
    {
        this->stepType = stepType;
    }

    const Array<OSTargetTask *> &getTasks() const
    {
        return this->tasks;
    }

    void setTasks(const Array<OSTargetTask *> &tasks)
    {
        this->tasks = tasks;
        updateTasksList();
    }

    SharedReference<OSProjectTargetDataInstance> getTarget() const
    {
        return this->target;
    }

    void setTarget(const SharedReference<OSProjectTargetDataInstance> &target)
    {
        this->target = target;
        updateTasks();
    }

    //public slots:

    void addTask(int index);

private:

    void updateTasks();
    void updateTasksList();

    SharedReference<OSTaskItemView> createTaskView(const SharedReference<OSTaskDataObject> &taskData);
    SharedReference<OSTaskItemView> createTaskView(const SharedReference<OSTaskDataObject> &taskData, OSTargetTask *task);

};

}
