#include <OneStudioProjectLibrary>

#include "Main.h"

#include "OSProjectEditor.h"
#include "ProjectToolBarView.gen.h"
#include "OSPlatformPlugin.h"
#include "OSPluginPreferencesView.h"

Map<String, OSPlatformPlugin*> PlatformPlugins;

class OSProjectApplicationPluginContext : public OSProjectContext
{

public:
    AOperationDispatcher &getOperationDispatcher() override
    {
        return *OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher();
    }

    void log(const String &text, const String &file = String(), const String &indication = String()) override
    {
        ALogMessage("Info", "%s%s%s", file, indication, text);
        OneStudioPlatform::ApplicationContext::getInstance().log(text, file, indication);
    }

    void error(const String &text, const String &file = String(), const String &indication = String()) override
    {
        ALogError("Error", "%s%s%s", file, indication, text);
        OneStudioPlatform::ApplicationContext::getInstance().error(text, file, indication);
    }

};

class OSProjectManager
{
public:
    Array<SharedReference<OSProject>> projects;
    TaskData currentData;
    Array<ADelegate<void(const SharedReference<OSProject> &project, const SharedReference<OneStudioProject2::Target> &targetData, const APair<String, SharedReference<OSSettings>> &configuration)>> onTargetChanged;
} projectManager;

class OSPrivateProjectPlugin : public OSTemplateEditorPlugin<OneStudioProject::ProjectEditor>, public OSProjectPluginContext, public OSProjectTaskObserver
{
public:
    using Super = OSTemplateEditorPlugin<OneStudioProject::ProjectEditor>;
    using This = OSPrivateProjectPlugin;
private:

    OSProjectApplicationPluginContext context;
    SharedReference<OneStudioProject::ProjectToolBarView> projectToolBarView = createNew<OneStudioProject::ProjectToolBarView>();
    SharedReference<OSProject> project;

public:

    void updateProjectSelection()
    {
        Array<String> projectNames;
        for (auto &project : projectManager.projects)
        {
            projectNames.append(project->getBaseName());
        }
        projectToolBarView->projectList->setCurrentIndex(-1); //TODO: hack, it's not possible to set the same index and update active text
        projectToolBarView->projectList->setElements(projectNames);

        projectManager.currentData.project = projectManager.projects[0];
        projectToolBarView->projectList->setCurrentIndex(0);
        updateTargetSelection();
        updateConfigurationSelection();
    }

    void updateTargetSelection()
    {
        auto &project = projectManager.currentData.project;

        if (!project)
        {
            return;
        }

        Array<String> targetsNames;
        for (auto &target : project->ProjectData.Targets)
        {
            targetsNames.append(target.Name);
        }
        projectToolBarView->targetList->setCurrentIndex(-1); //TODO: hack, it's not possible to set the same index and update active text
        projectToolBarView->targetList->setElements(targetsNames);
        if (targetsNames)
        {
            projectToolBarView->targetList->setCurrentIndex(0);
        }
    }

    void updateConfigurationSelection()
    {
        auto &project = projectManager.currentData.project;

        if (!project)
        {
            return;
        }

        Array<String> configurationsNames;
        for (auto &configuration : project->ProjectData.Configurations)
        {
            configurationsNames.append(configuration.Name);
        }
        projectToolBarView->configurationList->setCurrentIndex(-1); //TODO: hack, it's not possible to set the same index and update active text
        projectToolBarView->configurationList->setElements(configurationsNames);
        if (configurationsNames)
        {
            projectToolBarView->configurationList->setCurrentIndex(0);
        }
    }

    void registerPlatform(OSPlatformPlugin *platformPlugin)
    {
        PlatformPlugins.insert(platformPlugin->getPackage(), platformPlugin);
    }

    OSProjectContext &getProjectContext() override
    {
        return context;
    }

    OSPluginContext *getContext() override
    {
        return this;
    }

    class OSTaskPlugin *getTask(const String &package) override
    {
        auto it = this->context.getTasks().find(package);
        if(it == this->context.getTasks().end())
        {
            return nullptr;
        }
        return it->second->getInstance().data();
    }

    Array<String> getSupportedTypes() const override
    {
        return {"application/vnd.one-studio.project"};
    }

    String getIdentifier() const override
    {
        return "Editor";
    }

    void load(const Map<String, OSPluginContext *> &dependentPlugins) override
    {
        Super::load(dependentPlugins);

        //TODO: move to Static Run and link with GraphicsObjects
        glewExperimental = true;
        GLenum glewCompletionCode = glewInit();
        if (glewCompletionCode != GLEW_OK)
        {
            std::cout << glewGetErrorString(glewCompletionCode) << "\n";
            return;
        }
        Graphics::API::glCheckErrors(true);

        OneStudioPlatform::ApplicationContext &instance = OneStudioPlatform::ApplicationContext::getInstance();

#if ADebugBuild
        this->context.load(APath::getUserDirectory() + "DeveloperDebug");
#else
        this->context.load(APath::getUserDirectory() + "Developer");
#endif
        this->context.taskObserver = this;
        ProjectContext = &this->context;

        getEditor()->onLoadCallback = [this](const Array<SharedReference<OSProject>> &projects) {
            projectManager.projects = projects;
            updateProjectSelection();
        };
        projectToolBarView->setAffectsParentLayout(true);//TODO: move to UI file
        projectToolBarView->projectList->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);//TODO: move to UI file
        projectToolBarView->projectList->eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
            projectManager.currentData.project = event.getValue() != -1 ? projectManager.projects[event.getValue()] : nullptr;
            updateTargetSelection();
            updateConfigurationSelection();         
        });
        projectToolBarView->targetList->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);//TODO: move to UI file
        projectToolBarView->targetList->eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
            projectManager.currentData.targetData = event.getValue() != -1 ? projectManager.currentData.project->ProjectData.Targets[event.getValue()] : OneStudioProject2::Target();
        });
        projectToolBarView->configurationList->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);//TODO: move to UI file
        projectToolBarView->configurationList->eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
            if (event.getValue() == -1)
            {
                projectManager.currentData.configuration.first.clear();
                projectManager.currentData.configuration.second.clear();
                return;
            }
            auto &project = projectManager.currentData.project;
            const String &name = project->ProjectData.Configurations[event.getValue()].Name;

            for (size_t i = 0; i < project->getCountConfigurations(); ++i)
            {
                if (project->getConfigurationName(i) == name)
                {
                    projectManager.currentData.configuration.first = name;
                    projectManager.currentData.configuration.second = project->getConfigurationSettings(i);
                }
            }

        });
        projectToolBarView->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);//TODO: move to UI file

        instance.registerToolBarItem("Select", projectToolBarView);
        instance.registerToolBarItem("ProjectDebug", nullptr);
        instance.registerToolBarItem("Build", nullptr);
        instance.registerToolBarItem("Clean", nullptr);
        instance.registerToolBarItem("Rebuild", nullptr);
        instance.registerToolBarItem("Install", nullptr);
        instance.registerToolBarItem("Uninstall", nullptr);
        instance.registerToolBarItem("Reinstall", nullptr);
        instance.registerToolBarItem("Run", nullptr);

        instance.registerCommand("ProjectDebug", [this](const Array<String> &arguments) {
            auto &cd = projectManager.currentData;
            ALogMessage("", "Current Project: %s", cd.project ? cd.project->getBaseName() : String("Undefined"));
            ALogMessage("", "Current Target: %s", cd.targetData.Name ? cd.targetData.Name : String("Undefined"));
            ALogMessage("", "Current Configuration: %s", cd.configuration.first ? cd.configuration.first : String("Undefined"));
        });

        instance.registerCommand("Build", [this](const Array<String> &arguments) { build(); });
        instance.registerCommand("Clean", [this](const Array<String> &arguments) { clean(); });
        instance.registerCommand("Rebuild", [this](const Array<String> &arguments) { rebuild (); });
        instance.registerCommand("Install", [this](const Array<String> &arguments) { install(); });
        instance.registerCommand("Uninstall", [this](const Array<String> &arguments) { uninstall(); });
        instance.registerCommand("Reinstall", [this](const Array<String> &arguments) { reinstall(); });
        instance.registerCommand("Run", [this](const Array<String> &arguments) { run(); });
        instance.registerCommand("Select", [this](const Array<String> &arguments)
        {
            if (arguments.size() < 2)
            {
                return;
            }

            for (const SharedReference<OSProject> &project : projectManager.projects)
            {
                if (project->getBaseName() != arguments[0])
                {
                    continue;
                }

                for (const OneStudioProject2::Target &targetData : project->getTargetData())
                {
                    if (targetData.Name == arguments[1])
                    {
                        projectManager.currentData.project = project;
                        projectManager.currentData.targetData = targetData;
                        break;
                    }
                }

                if (arguments.size() > 2)
                {
                    for (size_t i = 0; i < project->getCountConfigurations(); ++i)
                    {
                        if (project->getConfigurationName(i) == arguments[2])
                        {
                            projectManager.currentData.configuration.first = arguments[2];
                            projectManager.currentData.configuration.second = project->getConfigurationSettings(i);
                        }
                    }
                }
            }
        });

        auto oneStudioProject = createNew<OneStudioPlatform::FileTemplate>();
        oneStudioProject->Name = "One Studio Project";
        oneStudioProject->Description = "Create One Studio project";
        oneStudioProject->Extensions  = {"osproject"};
        oneStudioProject->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newProject);

        auto textFile = createNew<OneStudioPlatform::FileTemplate>();
        textFile->Name = "Text file";
        textFile->Description = "Create text file";
        textFile->Extensions  = {"txt"};
        textFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto jsonFile = createNew<OneStudioPlatform::FileTemplate>();
        jsonFile->Name = "JSON file";
        jsonFile->Description = "Create JSON file";
        jsonFile->Extensions  = {"json"};
        jsonFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto xmlFile = createNew<OneStudioPlatform::FileTemplate>();
        xmlFile->Name = "XML file";
        xmlFile->Description = "Create XML file";
        xmlFile->Extensions  = {"xml"};
        xmlFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto cFile = createNew<OneStudioPlatform::FileTemplate>();
        cFile->Name = "C file";
        cFile->Description = "Create C file";
        cFile->Extensions  = {"c"};
        cFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto headerFile = createNew<OneStudioPlatform::FileTemplate>();
        headerFile->Name = "Header file";
        headerFile->Description = "Create .h file";
        headerFile->Extensions  = {"h"};
        headerFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto cppFile = createNew<OneStudioPlatform::FileTemplate>();
        cppFile->Name = "C++ file";
        cppFile->Description = "Create C++ file";
        cppFile->Extensions  = {"cpp"};
        cppFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto cppClassFile = createNew<OneStudioPlatform::FileTemplate>();
        cppClassFile->Name = "C++ class";
        cppClassFile->Description = "Create C++ file";
        cppClassFile->Extensions  = headerFile->Extensions + cppFile->Extensions;
        cppClassFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto objcFile = createNew<OneStudioPlatform::FileTemplate>();
        objcFile->Name = "Objective-C file";
        objcFile->Description = "Create Objective-C class";
        objcFile->Extensions  = {"m"};
        objcFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto objcppFile = createNew<OneStudioPlatform::FileTemplate>();
        objcppFile->Name = "Objective-C++ file";
        objcppFile->Description = "Create Objective-C++ class";
        objcppFile->Extensions  = {"mm"};
        objcppFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto objcClassFile = createNew<OneStudioPlatform::FileTemplate>();
        objcClassFile->Name = "Objective-C class";
        objcClassFile->Description = "Create Objective-C class";
        objcClassFile->Extensions  = headerFile->Extensions + objcFile->Extensions;
        objcClassFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto objcppClassFile = createNew<OneStudioPlatform::FileTemplate>();
        objcppClassFile->Name = "Objective-C++ class";
        objcppClassFile->Description = "Create Objective-C++ class";
        objcppClassFile->Extensions  = headerFile->Extensions + objcppFile->Extensions;
        objcppClassFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto javaFile = createNew<OneStudioPlatform::FileTemplate>();
        javaFile->Name = "Java file";
        javaFile->Description = "Create Java file";
        javaFile->Extensions  = {"java"};
        javaFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto dataEntityFile = createNew<OneStudioPlatform::FileTemplate>();
        dataEntityFile->Name = "Data entity";
        dataEntityFile->Description = "Create entity of data";
        dataEntityFile->Extensions  = {"dataentity"};
        dataEntityFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto dataInstanceFile = createNew<OneStudioPlatform::FileTemplate>();
        dataInstanceFile->Name = "Data instance";
        dataInstanceFile->Description = "Create data instance for manage data source";
        dataInstanceFile->Extensions  = {"datainstance"};
        dataInstanceFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto dataEntityAndInstanceFile = createNew<OneStudioPlatform::FileTemplate>();
        dataEntityAndInstanceFile->Name = "Data entity and instance";
        dataEntityAndInstanceFile->Description = "Create entity of data with instance for manage data source";
        dataEntityAndInstanceFile->Extensions  = dataEntityFile->Extensions + dataInstanceFile->Extensions;
        dataEntityAndInstanceFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto logicFile = createNew<OneStudioPlatform::FileTemplate>();
        logicFile->Name = "Logic";
        logicFile->Description = "Create One Studio logic file";
        logicFile->Extensions  = {"osl"};
        logicFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto aiFile = createNew<OneStudioPlatform::FileTemplate>();
        aiFile->Name = "AI logic";
        aiFile->Description = "Create One Studio AI logic file";
        aiFile->Extensions  = {"osai"};
        aiFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto animationFile = createNew<OneStudioPlatform::FileTemplate>();
        animationFile->Name = "Animation";
        animationFile->Description = "Create One Studio animation file";
        animationFile->Extensions  = {"osa"};
        animationFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto materialFile = createNew<OneStudioPlatform::FileTemplate>();
        materialFile->Name = "Material";
        materialFile->Description = "Create One Studio material";
        materialFile->Extensions  = {"osm"};
        materialFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto postEffectFile = createNew<OneStudioPlatform::FileTemplate>();
        postEffectFile->Name = "Post effect";
        postEffectFile->Description = "Create One Studio post effect file";
        postEffectFile->Extensions  = {"osfx"};
        postEffectFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto fragmentShaderFile = createNew<OneStudioPlatform::FileTemplate>();
        fragmentShaderFile->Name = "Fragment shader";
        fragmentShaderFile->Description = "Create fragment shader file";
        fragmentShaderFile->Extensions  = {"fsh"};
        fragmentShaderFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto vertexShaderFile = createNew<OneStudioPlatform::FileTemplate>();
        vertexShaderFile->Name = "Vertex shader";
        vertexShaderFile->Description = "Create vertex shader file";
        vertexShaderFile->Extensions  = {"vsh"};
        vertexShaderFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        auto geometryShaderFile = createNew<OneStudioPlatform::FileTemplate>();
        geometryShaderFile->Name = "Geometry shader";
        geometryShaderFile->Description = "Create geometry shader file";
        geometryShaderFile->Extensions  = {"gsh"};
        geometryShaderFile->callback = ADelegate<void(const APath &directory, const String &name)>(this, &OSPrivateProjectPlugin::newFile);

        OneStudioPlatform::FileContext *context = &OneStudioPlatform::FileContext::getInstance();
        context->registerFileTemplate("Projects", oneStudioProject);
        context->registerFileTemplate("Text", textFile);
        context->registerFileTemplate("Text", xmlFile);
        context->registerFileTemplate("Text", jsonFile);
        context->registerFileTemplate("Source Code", headerFile);
        context->registerFileTemplate("Source Code", cFile);
        context->registerFileTemplate("Source Code", cppFile);
        context->registerFileTemplate("Source Code", cppClassFile);
        context->registerFileTemplate("Source Code", objcFile);
        context->registerFileTemplate("Source Code", objcppFile);
        context->registerFileTemplate("Source Code", objcClassFile);
        context->registerFileTemplate("Source Code", objcppClassFile);
        context->registerFileTemplate("Source Code", javaFile);
        context->registerFileTemplate("Assets", logicFile);
        context->registerFileTemplate("Assets", aiFile);
        context->registerFileTemplate("Assets", animationFile);
        context->registerFileTemplate("Assets", materialFile);
        context->registerFileTemplate("Assets", postEffectFile);
        context->registerFileTemplate("Data", dataEntityFile);
        context->registerFileTemplate("Data", dataInstanceFile);
        context->registerFileTemplate("Data", dataEntityAndInstanceFile);
        context->registerFileTemplate("Shaders", fragmentShaderFile);
        context->registerFileTemplate("Shaders", vertexShaderFile);
        context->registerFileTemplate("Shaders", geometryShaderFile);

        //context->registerType("One Studio project file", AMIMEType("application/vnd.one-studio.project", "text/json"), {"osproject"});
    }

    void unload() override
    {
        Super::unload();
        ProjectContext->getOperationDispatcher().setExitAfterLastOperation(true);
        ProjectContext->getOperationDispatcher().exit();
        this->context.unload();
    }

    void newProject(const APath &directory, const String &name)
    {
        auto project = createNew<OSProject>();
        project->save(directory + APath(name).resolveWithExtension("osproject"));
    }

    void newFile(const APath &directory, const String &name)
    {
        APath path = directory + name;
        AFile file(path);
        if(file.open(AFileOpenMode::WriteBinary))
        {
            file << "This is template file: " << name;
        }
        file.close();

        SharedReference<OSFileSystemItem> projectItem = createNew<OSFileSystemItem>();
        projectItem->setText(name);
        projectItem->setPath(path);
        //projectItem->setImage(QFileIconProvider().icon(QFileInfo(path.toString().toUtf8().data())));
    }

    void showPreferences()
    {
        OSPluginPreferencesView *view = createNew<OSPluginPreferencesView>();
        view->show();
    }

    void openPlatformSettings()
    {
        //if(!project || !projectToolBarView->getCurrentTargetInfo())
        {
            return;
        }

        /*auto view = Platforms()[projectToolBarView->getCurrentTargetInfo()->getPackage()]->getProjectSettingsView(nullptr);
        view->show();*/
    }

    Stack<SharedReference<OneStudioPlatform::Task>> tasks;

    void startTask(const String &action, OSProject &project, const OneStudioProject2::Target &target)
    {
        String title = fmt::format("{} {} - {}", action, project.getName(), target.Name);
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this, title]() {
            if (!tasks.empty())
            {
                return AError::getEmptyError();
            }

            SharedReference<OneStudioPlatform::Task> task = OneStudioPlatform::TaskContext::getInstance().startTask();
            task->setTitle(title);
            tasks.push(task);
            return AError::getEmptyError();
        }, true);
    }

    void finishTask(OSProject &project, const OneStudioProject2::Target &targetData, const AError &error)
    {
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this, error]() {
            if (tasks.size() > 1)
            {
                return AError::getEmptyError();
            }

            SharedReference<OneStudioPlatform::Task> task = tasks.top();
            task->setTitle(task->getTitle() + (error ? " (Failed)" : " (Successful)"));
            tasks.pop();
            return AError::getEmptyError();
        }, true);
    }

    void startSubtask(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task)
    {
        String title = task.Title ? fmt::format("{} ({})", task.Title, task.Type) : task.Type;
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this, title]() {
            SharedReference<OneStudioPlatform::Task> currentTask = tasks.top();
            SharedReference<OneStudioPlatform::Task> subtask = currentTask->createSubTask();
            subtask->setTitle(title);
            tasks.push(subtask);
            return AError::getEmptyError();
        }, true);
    }

    void finishSubtask(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error)
    {
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this, error]() {
            SharedReference<OneStudioPlatform::Task> currentTask = tasks.top();
            currentTask->setTitle(currentTask->getTitle() + (error ? " (Failed)" : " (Successful)"));
            tasks.pop();
            return AError::getEmptyError();
        }, true);
    }

    void onBuildStart(OSProject &project, const OneStudioProject2::Target &target) override { startTask("Build", project, target); }
    void onBuildFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) override { finishTask(project, target, error); }
    void onCleanStart(OSProject &project, const OneStudioProject2::Target &target) override { startTask("Clean", project, target); }
    void onCleanFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) override { finishTask(project, target, error); }
    void onInstallStart(OSProject &project, const OneStudioProject2::Target &target) override { startTask("Install", project, target); }
    void onInstallFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) override { finishTask(project, target, error); }
    void onUninstallStart(OSProject &project, const OneStudioProject2::Target &target) override { startTask("Uninstall", project, target); }
    void onUninstallFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) override { finishTask(project, target, error); }
    void onRunStart(OSProject &project, const OneStudioProject2::Target &target) override { startTask("Run", project, target); }
    void onRunFinish(OSProject &project, const OneStudioProject2::Target &target, const AError &error) override { finishTask(project, target, error); }

    void onBuildStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) override { startSubtask(target, task); }
    void onBuildFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) override { finishSubtask(target, task, error); }
    void onCleanStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) override { startSubtask(target, task); }
    void onCleanFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) override { finishSubtask(target, task, error); }
    void onInstallStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) override { startSubtask(target, task); }
    void onInstallFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) override { finishSubtask(target, task, error); }
    void onUninstallStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) override { startSubtask(target, task); }
    void onUninstallFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) override { finishSubtask(target, task, error); }
    void onRunStart(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task) override { startSubtask(target, task); }
    void onRunFinish(const OneStudioProject2::Target &target, const OneStudioProject2::Task &task, const AError &error) override { finishSubtask(target, task, error); }

    void build()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.build(projectManager.currentData, [this](AError &&error) {
                OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                    //TODO: enable input
                    return AError::getEmptyError();
                }, true);
            });
            return AError();
        });
    }

    void clean()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.clean(projectManager.currentData, [this](AError &&error) {
                OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                    //TODO: enable input
                    return AError::getEmptyError();
                }, true);
            });
            return AError();
        });
    }

    void rebuild()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.clean(projectManager.currentData, [this](AError &&error) {
                context.build(projectManager.currentData, [this](AError &&error) {
                    OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                        //TODO: enable input
                        return AError::getEmptyError();
                    }, true);
                });
            });
            return AError();
        });
    }

    void install()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.install(projectManager.currentData, [this](AError &&error) {
                OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                    //TODO: enable input
                    return AError::getEmptyError();
                }, true);
            });
            return AError();
        });
    }

    void uninstall()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.uninstall(projectManager.currentData, [this](AError &&error) {
                OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                    //TODO: enable input
                    return AError::getEmptyError();
                }, true);
            });
            return AError();
        });
    }

    void reinstall()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.uninstall(projectManager.currentData, [this](AError &&error) {
                context.install(projectManager.currentData, [this](AError &&error) {
                    OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                        //TODO: enable input
                        return AError::getEmptyError();
                    }, true);
                });
            });
            return AError();
        });
    }

    void run()
    {
        //TODO: dissable input
        OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
            context.run(projectManager.currentData, [this](AError &&error) {
                OneStudioPlatform::TaskContext::getInstance().getOperationDispatcher()->addDelegate([this]() {
                    //TODO: enable input
                    return AError::getEmptyError();
                }, true);
            });
            return AError();
        });
    }

    void addDefinition(const String &definition, const String &path)
    {
        //DefinitionsView->addDefinition(definition, path);
    }

    void removeDefinition(const String &definition)
    {
        //DefinitionsView->removeDefinition(definition);
    }

};

AApplicationPluginImplementation(OSPlugin, OSPrivateProjectPlugin, 1, OSProjectPluginVersion, OSProjectPluginPackage)
