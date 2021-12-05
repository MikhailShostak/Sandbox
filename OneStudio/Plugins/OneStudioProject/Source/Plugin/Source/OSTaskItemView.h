#pragma once

#include <Experimental>
#include <OneStudioProjectLibrary>

namespace UI
{

class OSTaskItemView : public UI::View, public ItemAdapter
{
    SharedReference<TextField> descriptionView;
    SharedReference<ListView> propertiesView;
    SharedReference<TextButton> expandButton;

    OSTargetTask *task = nullptr;
    SharedReference<OSProjectTargetDataInstance> target;
    SharedReference<OSTaskDataObject> taskData;
    Array<SharedReference<OSTaskPropertyDataObject>> properties;
    //Array<SharedReference<QWidget>> views;

/*signals:

    void up();
    void down();
    void remove();*/

public:

    explicit OSTaskItemView();
    ~OSTaskItemView();

    SizeType getCountItems(const AObject &sender) const;
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType index);

    bool isContentVisible() const;
    void setContentVisible(bool visible);

    const SharedReference<OSProjectTargetDataInstance> &getTarget() const
    {
        return this->target;
    }

    void setTarget(const SharedReference<OSProjectTargetDataInstance> &target)
    {
        this->target = target;
        updateData();
    }

    OSTargetTask *getTask() const
    {
        return this->task;
    }

    void setTask(OSTargetTask *task)
    {
        this->task = task;
        updateData();
    }

    const SharedReference<OSTaskDataObject> &getTaskData() const
    {
        return this->taskData;
    }

    void setTaskData(const SharedReference<OSTaskDataObject> &task)
    {
        this->taskData = task;
        updateData();
    }


    /*public slots:

        void changeContentVisibility();*/

private:

    void updateData();

};

}