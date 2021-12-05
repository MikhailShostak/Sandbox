#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include <OneStudioProjectLibrary>

#include "OSPlatformPlugin.h"

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ProjectSettingsView : public UI::SplitView
//CLASSGEN END REGION
, public UI::ItemAdapter, public UI::GroupAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ProjectSettingsView This;
    typedef UI::SplitView Super;
    typedef void Interfaces;
    ProjectSettingsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::ListView> targetsListView;
    SharedReference<UI::ListView> configurationsListView;
    SharedReference<UI::PageView> contentView;
    SharedReference<UI::GroupView> stepsSettingsView;
    SharedReference<UI::GroupView> targetSettingsView;
    SharedReference<UI::GroupView> configurationsSettingsView;
    void onHierarchyCreate();
//CLASSGEN END REGION

    SharedReference<OSProject> project;
    OneStudioProject2::Target currentTargetData;
    SharedReference<OSProjectTargetDataInstance> currentTarget;
    size_t currentTarget2 = 0;

    const OneStudioProject2::Target &getCurrentTarget() const { return project->getTargetData()[currentTarget2]; }

    Array<OSTargetTask *> tasks;
    UI::SuggestionsComponent tasksSuggestions;

    Array<OneStudioProject2::Target> targets;

//     SharedReference<UI::ListView> targetsListView = new UI::ListView();
//     SharedReference<UI::ListView> configurationsListView = new UI::ListView();
//     SharedReference<UI::GroupView> stepsListView = new UI::GroupView();
//     SharedReference<UI::GroupView> targetSettingsView = new UI::GroupView();
//     SharedReference<UI::GroupView> configurationSettingsView = new UI::GroupView();

    struct StepInfo
    {
        String name;
        String title;
        String description;
        Array<SharedReference<OSTaskDataObject>> tasks;
    };

    Array<APair<String, SharedReference<OSSettings>>> currentTargetSettings;
    Array<APair<String, SharedReference<OSSettings>>> currentConfigurationSettings;

public:

    void onLoad(ALoadEvent &event) override;
    UI::SizeType getCountItems(const AObject &sender) const override;
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override;

    bool shouldAddTouchGestureRecognizerToItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return false; }
    bool shouldReceiveInputFromItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return false; }
    UI::SizeType getCountGroups(const AObject &sender) const override;
    UI::SizeType getCountItems(const AObject &sender, UI::SizeType groupIndex) const override;
    SharedReference<UI::View> provideViewForGroup(const AObject &sender, UI::SizeType groupIndex) override;
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex) override;

    const Array<OSTargetTask *> &getTasks() const
    {
        return tasks;
    }

    void setTasks(const Array<OSTargetTask *> &tasks)
    {
        this->tasks = tasks;
        tasksSuggestions.items.clear();
        tasksSuggestions.items.reserve(tasks.size());
        for (auto &task : tasks)
        {
            tasksSuggestions.items.append(task->getPackage());
        }
        //TODO: suggestions view update is needed?
        updateTaskData();
    }

    SharedReference<OSProject> getProject() const
    {
        return project;
    }

    void setProject(const SharedReference<OSProject> &project)
    {
        this->project = project;
        updateProjectData();
    }

    //explicit ProjectSettingsView();
    //~ProjectSettingsView();

    void updateProjectData();
    void updateTaskData();

    void onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index);

    //public slots:

    void selectProjectSettings(int index);
    void selectTargetSettings(int index);

    void selectTarget(size_t index);

    void addTargetDependence(size_t index);
private:

    void updateTargetDependencies(size_t index);
    void closeAllViews();

    void onLayout(AUpdateEvent &event)
    {
        Super::onLayout(event);
    }


};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
