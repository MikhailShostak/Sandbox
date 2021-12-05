#include "OSProject.h"
#include "OSProject.inl"
#include "OSTaskPlugin.h"
#include "OSProjectTargetInfoDataObject.inl"
#include "Main.h"

String OSProject::OSSettingsExtension = "settings";

String TasksSettingsPackage = "com.InsaneTeam.OneStudio.Tasks";
String GeneralSettingsPackage = "com.InsaneTeam.OneStudio.General";

void bindSettings(Array<OneStudioProject2::Settings> &settingsContainer, const String &type, const SharedReference<OSSettings> settings)
{
    size_t index = 0;
    auto it = std::find_if(settingsContainer.begin(), settingsContainer.end(), [type](const OneStudioProject2::Settings &s) { return s.Type == type; });
    if (it != settingsContainer.end())
    {
        index = std::distance(settingsContainer.begin(), it);
        settingsContainer[index].DataInstance = settings->getBaseData().data();
        settingsContainer[index].DataInstance->deserialize(settingsContainer[index].Data);
    }
}

void resaveSettings(Array<OneStudioProject2::Settings> &settingsContainer, OSSettingsDataInstance *instance, const SharedReference<OSSettings> settings)
{
    if (!instance || !APathInfo(instance->getPath()).isFile())
    {
        return;
    }

    size_t index = 0;
    auto it = std::find_if(settingsContainer.begin(), settingsContainer.end(), [instance](const OneStudioProject2::Settings &s) { return s.Type == instance->getBaseName(); });
    if (it != settingsContainer.end())
    {
        index = std::distance(settingsContainer.begin(), it);
    }
    else
    {
        index = settingsContainer.size();
        OneStudioProject2::Settings newSettings;
        newSettings.Type = instance->getBaseName();
        settingsContainer.append(newSettings);
    }

    bool empty = true;
    for (size_t i = 0; i < settings->getGroupsCount(); ++i)
    {
        String groupTitle = settings->getGroupTitle(i).replace(" ", "");

        AJSONObject d;
        for (size_t j = 0; j < settings->getRowsCount(i); ++j)
        {
            String t = settings->getItem(i, j, 0 + 100000);
            String v = settings->getItem(i, j, 1 + 100000);
            if (!d.hasKey(t))
            {
                //ALogMessage("", "[%s] insert(%d, %d): [%s] %s", groupTitle, i, j, t, v);
                d.insert(t, v);
            }
        }
        if (d)
        {
            if (!settingsContainer[index].Data.hasKey(groupTitle))
            {
                settingsContainer[index].Data.insert(groupTitle, d);
            }
            empty = false;
        }
    }
    if (empty)
    {
        settingsContainer.erase(settingsContainer.begin() + index);
    }
    else
    {
        settingsContainer[index].DataInstance = settings->getBaseData().data();
        settingsContainer[index].DataInstance->deserialize(settingsContainer[index].Data);
    }
};

bool OSProject::load(const Path &path)
{
    ProjectData.deserialize(AJSON::valueFromFile(path).toObject());
    setPath(path);

    SharedReference<OSBuildTaskSettings> settings = createNew<OSBuildTaskSettings>();
    settings->DebugName = fmt::format("Project settings: {}", getName());
    settings->setParent(ProjectContext->getBuildingSettings().data());

    SharedReference<OSSettingsDataInstance> settingsInstance = settings->getFileData().cast<OSSettingsDataInstance>();
    bindSettings(ProjectData.Settings, GeneralSettingsPackage, settings);

    this->settings.insert(GeneralSettingsPackage, settings);

    APathInfo configurationDirectory = getConfigurationsDirectory();
    if (!ProjectData.Configurations && configurationDirectory.isExists())
    {
        const Array<APathInfo> &configurationDirectories = ADirectory(configurationDirectory).find(AFindFilter::AllDirectories);
        for (const APathInfo &configurationDirectory : configurationDirectories)
        {
            OneStudioProject2::Configuration c;
            c.Name = configurationDirectory.name();
            ProjectData.Configurations.append(c);
        }
    }

    for (OneStudioProject2::Configuration &c : ProjectData.Configurations)
    {
        SharedReference<OSBuildTaskSettings> configurationSettings = createNew<OSBuildTaskSettings>();
        configurationSettings->DebugName = fmt::format("Configuration settings: {}", getName());

        SharedReference<OSSettingsDataInstance> settingsInstance = configurationSettings->getFileData().cast<OSSettingsDataInstance>();
        bindSettings(c.Settings, GeneralSettingsPackage, configurationSettings);

        c.settings.insert(GeneralSettingsPackage, configurationSettings);
    }

    for (OneStudioProject2::Target &target : ProjectData.Targets)
    {
        createTargetInstance(target.Name);

        if (!target.settings)
        {
            SharedReference<OSBuildTaskSettings> targetBuildingSettings = createNew<OSBuildTaskSettings>();
            targetBuildingSettings->setParent(getSettings().at(GeneralSettingsPackage).data()); //TODO: optimize

            SharedReference<OSSettingsDataInstance> settingsInstance = targetBuildingSettings->getFileData().cast<OSSettingsDataInstance>();
            bindSettings(target.Settings, GeneralSettingsPackage, targetBuildingSettings);
            targetBuildingSettings->DebugName = fmt::format("Target settings: {}->{}", getName(), target.Name);
            target.settings.insert(GeneralSettingsPackage, targetBuildingSettings);
        }        
    }

    return true;
}

bool OSProject::save(const Path &path)
{
    AJSONObject d;
    ProjectData.serialize(d);
    return AJSON::saveToFile(d, path);
}

SharedReference<OSProjectTargetDataInstance> OSProject::createTargetInstance(const String &name)
{
    APathInfo targetDirectory = APathInfo(getTargetDirectory(name));
    SharedReference<OSProjectTargetDataInstance> target = createNew<OSProjectTargetDataInstance>();
    SharedReference<OSBuildTaskSettings> targetBuildingSettings = createNew<OSBuildTaskSettings>();
    targetBuildingSettings->setParent(getSettings().at(GeneralSettingsPackage).data()); //TODO: optimize
    targetBuildingSettings->DebugName = fmt::format("Target settings: {}->{}", getName(), name);
    target->settings.insert(GeneralSettingsPackage, targetBuildingSettings);

    OneStudioProject2::Target &t = *ProjectData.Targets.find([&](const OneStudioProject2::Target &target) {
        return target.Name == name;
    });
    SharedReference<OSSettingsDataInstance> settingsInstance = targetBuildingSettings->getFileData().cast<OSSettingsDataInstance>();
    bindSettings(t.Settings, GeneralSettingsPackage, targetBuildingSettings);
    t.settings.insert(GeneralSettingsPackage, targetBuildingSettings);
    
    auto &taskPlugins = ProjectContext->getTasks();
    for (OneStudioProject2::Action &action : t.Actions)
    {
        for (OneStudioProject2::Task &task : action.Tasks)
        {
            auto it = taskPlugins.find(task.Type);
            if (it == taskPlugins.end())
            {
                continue;
            }

            auto &taskPlugin = it->second->getInstance();
            
            auto loadSettingsFor = [&](const String &package) {
                //Project Settings
                appendSettings(ProjectData.Settings, package, getSettingsPath(package + "."), ProjectContext->getSettings(), settingsMap, settings);

                Map<String, SharedReference<OSSettings>> emptyParentSettings;
                size_t i = 0;
                //Configuration Settings
                for (auto &configuration : ProjectData.Configurations)
                {
                    appendSettings(configuration.Settings, package, getConfigurationPath(configuration.Name, package + "."), emptyParentSettings, configuration.settingsMap, configuration.settings);
                    ++i;
                }

                //Target Settings
                appendSettings(t.Settings, package, getTargetSettingsPath(t.Name, package + "."), settings, t.settingsMap, t.settings);
            };

            loadSettingsFor(task.Type);

            //Load settings for each dependency 
            for (auto &taskDependency : taskPlugin->getDependencies())
            {
                loadSettingsFor(taskDependency);
            }
        }
    }

    //targets.insert(targetInfo.data(), target);
    targets2.insert(name, target);
    return target;
}

void OSProject::appendSettings(Array<OneStudioProject2::Settings> &s, const String &package, const String &path, const Map<String, SharedReference<OSSettings>> &parentSettings, Map<String, size_t> &settingsMap, Map<String, SharedReference<OSSettings>> &settingsContainer)
{
    ALogMessage("", "AppendSettings[%s]: %s", package, path);
    auto &count = settingsMap[package];
    if (count == 0)
    {
        auto &taskPlugins = ProjectContext->getTasks();
        auto it = taskPlugins.find(package);
        if (it != taskPlugins.end())
        {
            SharedReference<OSTaskPlugin> taskPlugin = it->second->getInstance();
            SharedReference<OSSettings> settings = taskPlugin->createSettings();
            auto parentIt = parentSettings.find(package);
            if (parentIt != parentSettings.end())
            {
                settings->setParent(parentIt->second.data());
            }
            SharedReference<OSSettingsDataInstance> settingsInstance = settings->getFileData().cast<OSSettingsDataInstance>();
            bindSettings(s, package, settings);
            settingsContainer.insert(package, settings);
        }
    }
    ++count;
}

SharedReference<OSProjectTargetInfoDataObject> OSProject::createTargetInfo(const String &name)
{
    OneStudioProject2::Target t;
    t.Name = name;
    ProjectData.Targets.append(t);

    auto targetInfo = getDataContext()->create<OSProjectTargetInfoDataObject>();
    //targetInfo->setPackage(package);
    OneStudioProject2::Target target;
    targetInfo->setName(name);
    /*if(createTargetInstance(targetInfo)) FIX THIS CODE
    {
        targetInfo->save();
        targetInfos.append(targetInfo);
    }*/
    return targetInfo;
}

void OSProject::removeTargetInfo(size_t index)
{
    auto targetInfo = targetInfos.at(index);
    //targets.remove(targetInfo.data());
    targets2.remove(targetInfo->getName());
    targetInfos.remove(targetInfo);
    getDataContext()->remove(targetInfo);
    getDataContext()->saveAll();
    APathInfo(getTargetDirectory(targetInfo->getName())).remove();

    ProjectData.Targets.erase(ProjectData.Targets.begin() + index);
    //ProjectData.Targets.erase(std::find_if(ProjectData.Targets.begin(), ProjectData.Targets.end(), [&](const OneStudioProject2::Target &target) { return target.Name == targetInfo->getName(); }));
}

void OSProject::addTargetTask(const String &targetPackage, const String &taskPackage)
{

}

void OSProject::removeTargetTask(const String &targetPackage, const String &taskPackage)
{

}

String OSProject::getNewTargetName() const
{
    return "New Target";
}

String OSProject::getNewConfigurationName() const
{
    return "New Configuration";
}

void OSProject::addTarget(const String &name, size_t index)
{
    SharedReference<OSBuildTaskSettings> targetBuildingSettings = createNew<OSBuildTaskSettings>();
    targetBuildingSettings->setParent(getSettings().at(GeneralSettingsPackage).data()); //TODO: optimize
    targetBuildingSettings->getFileData()->setPath(getTargetSettingsPath(name, GeneralSettingsPackage + "."));
    APathInfo(targetBuildingSettings->getFileData()->getDirectory()).make();
    targetBuildingSettings->getFileData()->create();
    targetBuildingSettings->getFileData()->load(false);
    targetBuildingSettings->DebugName = fmt::format("Target settings: {}->{}", getName(), name);

    OneStudioProject2::Target t;
    t.Name = name;

    {
        OneStudioProject2::Action a;
        a.Name = "Build";
        t.Actions.append(a);
    } {
        OneStudioProject2::Action a;
        a.Name = "Clean";
        t.Actions.append(a);
    } {
        OneStudioProject2::Action a;
        a.Name = "Install";
        t.Actions.append(a);
    } {
        OneStudioProject2::Action a;
        a.Name = "Uninstall";
        t.Actions.append(a);
    }

    t.settings.insert(GeneralSettingsPackage, targetBuildingSettings);
    ProjectData.Targets.insert(ProjectData.Targets.begin() + index, t);
}

void OSProject::addTarget(const String &name)
{
    addTarget(name, ProjectData.Targets.size());
}

void OSProject::addTarget(size_t index)
{
    addTarget(getNewTargetName(), index);
}

void OSProject::addTarget()
{
    addTarget(ProjectData.Targets.size());
}

void OSProject::removeTarget(const String &name)
{
    
}

void OSProject::removeTarget(size_t index)
{
    ProjectData.Targets.erase(ProjectData.Targets.begin() + index);
}

void OSProject::addConfiguration(const String &name, size_t index)
{
    OneStudioProject2::Configuration c;
    c.Name = name;
    ProjectData.Configurations.insert(ProjectData.Configurations.begin() + index, c);
}

void OSProject::addConfiguration(const String &name)
{
    addConfiguration(name, ProjectData.Configurations.size());
}

void OSProject::addConfiguration(size_t index)
{
    addConfiguration(getNewConfigurationName(), index);
}

void OSProject::addConfiguration()
{
    addConfiguration(ProjectData.Configurations.size());
}

void OSProject::removeConfiguration(const String &name)
{

}

void OSProject::removeConfiguration(size_t index)
{
    ProjectData.Configurations.erase(ProjectData.Configurations.begin() + index);
}
