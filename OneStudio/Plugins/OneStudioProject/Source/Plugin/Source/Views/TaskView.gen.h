#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION

#include <Experimental>
#include <OneStudioProjectLibrary>

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TaskView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TaskView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    TaskView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::FlexBox> header;
    SharedReference<UI::TextField> descriptionTextField;
    SharedReference<UI::ImageView> separator;
    SharedReference<UI::ImageView> visibilityButton;
    SharedReference<UI::FlexBox> contentView;
    SharedReference<UI::TextField> packageField;
    SharedReference<UI::ListView> argumentsListView;
    void onHierarchyCreate();
//CLASSGEN END REGION

    OSTargetTask *task = nullptr;
    SharedReference<OSProjectTargetDataInstance> target;
    OneStudioProject2::Task taskData;
public:

    ADelegate<void()> TaskChanged;

    void onLoad(ALoadEvent &event);

    UI::SizeType getCountItems(const AObject &sender) const;
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index);

    bool isContentVisible() const;
    void setContentVisible(bool visible);

    OSTargetTask *getTask() const
    {
        return this->task;
    }

    void setTask(OSTargetTask *task)
    {
        this->task = task;
        updateData();
    }

    const OneStudioProject2::Task &getTaskData() const
    {
        return this->taskData;
    }

    void setTaskData(const OneStudioProject2::Task &task)
    {
        this->taskData = task;
        updateData();
    }

private:

    void updateData();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
