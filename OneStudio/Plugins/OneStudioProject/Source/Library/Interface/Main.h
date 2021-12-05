#pragma once

#include "OSProject.h"
#include "OSProject.inl"
#include "OSSettings.h"

#include "ATableAdapter.h"
#include "OSTargetTask.h"
#include "OSBuildTask.h"

class OSTaskPlugin;

class OSProjectObserver
{
public:

    ~OSProjectObserver() {}

    virtual void onProjectLoad(OSProject *project) {}
    virtual void onProjectUnload(OSProject *project) {}

};

struct TaskData
{
    SharedReference<OSProject> project;
    OneStudioProject2::Target targetData;
    APair<String, StringHashMap<SharedReference<OSSettings>>> configuration;
};

class OSProjectTaskObserver
{
public:

    virtual void onBuildStart(OSProject &project, const OneStudioProject2::Target &target) {}
    virtual void onBuildFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) {}
    virtual void onCleanStart(OSProject &project, const OneStudioProject2::Target &target) {}
    virtual void onCleanFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) {}
    virtual void onInstallStart(OSProject &project, const OneStudioProject2::Target &target) {}
    virtual void onInstallFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) {}
    virtual void onUninstallStart(OSProject &project, const OneStudioProject2::Target &target) {}
    virtual void onUninstallFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) {}
    virtual void onRunStart(OSProject &project, const OneStudioProject2::Target &target) {}
    virtual void onRunFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) {}

    virtual void onBuildStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) {}
    virtual void onBuildFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) {}
    virtual void onCleanStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) {}
    virtual void onCleanFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) {}
    virtual void onInstallStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) {}
    virtual void onInstallFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) {}
    virtual void onUninstallStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) {}
    virtual void onUninstallFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) {}
    virtual void onRunStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) {}
    virtual void onRunFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) {}
};

class OSProjectContext : public AProcessObserver
{

public:

    using TaskPluginType = AApplicationPlugin<OSTaskPlugin>;

protected:

    AOperationDispatcher *operationDispatcher = nullptr;
    Map<String, SharedReference<TaskPluginType>> tasks;

    Map<String, SharedReference<OSSettings>> settings;
    Array<OneStudioProject2::Settings> s;

    Array<OSProjectObserver *> observers;

    APath developerDirectory;
    APath libraryDirectory;
    APath settingsDirectory;
    APath tasksDirectory;
    APath toolsDirectory;

public:

    OSProjectTaskObserver *taskObserver = nullptr;

    Array<StringsHashMap> environment;

    Array<SharedReference<OSTargetTask>> internalBuildTasks; //TODO: Replace with AUniquePointer
    Array<SharedReference<OSTargetTask>> internalTargetTasks; //TODO: Replace with AUniquePointer
    Array<OneStudioProject::Task *> allTasks;
    Array<OSTargetTask *> targetTasks;

    const APath &getDeveloperDirectory() const
    {
        return developerDirectory;
    }

    const APath &getLibraryDirectory() const
    {
        return libraryDirectory;
    }

    const APath &getSettingsDirectory() const
    {
        return settingsDirectory;
    }

    const APath &getTasksDirectory() const
    {
        return tasksDirectory;
    }

    const APath &getToolsDirectory() const
    {
        return toolsDirectory;
    }

    SharedReference<OSProject> loadProject(const APath &path)
    {
        SharedReference<OSProject> project = createNew<OSProject>();
        project->load(path);
        loadProject(project);

        return project;
    }

    void loadProject(const SharedReference<OSProject> &project)
    {
        for(auto &observer : observers)
        {
            observer->onProjectLoad(project.data());
        }
    }

    void addObserver(OSProjectObserver *observer)
    {
        observers.append(observer);
    }

    void removeObserver(OSProjectObserver *observer)
    {
        observers.remove(observer);
    }

    Map<String, SharedReference<OSSettings>> &getSettings()
    {
        return settings;
    }

    const Map<String, SharedReference<OSSettings>> &getSettings() const
    {
        return settings;
    }

    SharedReference<OSBuildTaskSettings> getBuildingSettings() const
    {
        return settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>();
    }

    const Map<String, SharedReference<TaskPluginType>> &getTasks() const
    {
        return tasks;
    }

    OSProjectContext();
    virtual ~OSProjectContext();

    virtual AOperationDispatcher &getOperationDispatcher() = 0;

    virtual void log(const String &text, const String &file = String(), const String &indication = String()) {}
    virtual void error(const String &text, const String &file = String(), const String &indication = String()) {}

    void registerTask(OneStudioProject::Task *task)
    {
        allTasks.append(task);
    }

    void registerTargetTask(OSTargetTask *task)
    {
        registerTask(task);
        targetTasks.append(task);
    }

    template<typename Type>
    void registerInternalTargetTask()
    {
        SharedReference<OSTargetTask> task = createNew<Type>();
        registerTargetTask(task.data());
        internalTargetTasks.append(std::move(task));
    }

    void load(const APath &developerDirectory);
    void unload();

    void build(const TaskData &data, const ADelegate<void(AError &&error)> &completion = ADelegate<void(AError &&error)>());
    void clean(const TaskData &data, const ADelegate<void(AError &&error)> &completion = ADelegate<void(AError &&error)>());
    void install(const TaskData &data, const ADelegate<void(AError &&error)> &completion = ADelegate<void(AError &&error)>());
    void uninstall(const TaskData &data, const ADelegate<void(AError &&error)> &completion = ADelegate<void(AError &&error)>());
    void run(const TaskData &data, const ADelegate<void(AError &&error)> &completion = ADelegate<void(AError &&error)>());

    void updateRootEnvironment(const TaskData &data);
    void updateRootEnvironment(const TaskData &data, const OSProjectTargetDataInstance &target);
    void updateRootEnvironment(const TaskData &data, const OneStudioProject2::Target &target);
    void pushEnvironment(const TaskData &data);
    void pushEnvironment(const TaskData &data, const OSProjectTargetDataInstance &target);
    void pushEnvironment(const TaskData &data, const OneStudioProject2::Target &target);
    void popEnvironment();

    void onOutputMessage(uint8_t *buffer, size_t size) override
    {
        log(Array<uint8_t>(buffer, buffer + size));
    }

    void onErrorMessage(uint8_t *buffer, size_t size) override
    {
        error(Array<uint8_t>(buffer, buffer + size));
    }

private:

    void loadSettings(APathInfo settingsDirectory);
    void unloadSettings();

    void loadTasks(APathInfo tasksDirectory, const String &pluginExtension = ADefaultPluginExtension);
    void unloadTasks();

    void runTargetTasks(const TaskData &data, const String &stepName, const ADelegate<void(AError &&error)> &completion);

};

extern OSProjectContext *ProjectContext;
