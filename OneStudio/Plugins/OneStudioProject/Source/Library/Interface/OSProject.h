#pragma once

#include <Data>

#include "OSProjectFeatureInfoDataObject.h"
#include "OSProjectTargetInfoDataObject.h"
#include "OSProjectEntryDataObject.h"
#include "OSProjectEntryDataObject.inl"

#include "OSProjectFeature.generated.h"
#include "OSProjectTargetDataInstance.h"
#include "OSBuildTask.h"

#include "ProjectData/Project.gen.h"

class OSTargetController;

class OSProject : public AFileDataInstance<AJSONDataStorage>
{

    StringHashMap<size_t> settingsMap;
    StringHashMap<SharedReference<OSSettings>> settings;
    struct Configuration
    {
        String name;
        StringHashMap<size_t> settingsMap;
        StringHashMap<SharedReference<OSSettings>> settings;
    };
    Array<Configuration> configurations;
    Array<SharedReference<OSProjectTargetInfoDataObject>> targetInfos;

    Map<String, SharedReference<OSProjectTargetDataInstance>> targets2;

    static String OSSettingsExtension;

public:

    OneStudioProject2::Project ProjectData = {};

    const StringHashMap<SharedReference<OSSettings>> &getSettings() const;
    size_t getCountConfigurations() const
    {
        return ProjectData.Configurations.size();
    }

    const String &getConfigurationName(size_t index) const
    {
        return ProjectData.Configurations[index].Name;
    }

    const StringHashMap<SharedReference<OSSettings>> &getConfigurationSettings(size_t index) const
    {
        return ProjectData.Configurations[index].settings;
    }

    SharedReference<OSProjectTargetInfoDataObject> createTargetInfo(const String &name);
    void removeTargetInfo(size_t index);

    const Array<OneStudioProject2::Target> &getTargetData() const { return ProjectData.Targets; }
    OneStudioProject2::Target *findTargetData(const String &name)
    {
        auto it = std::find_if(ProjectData.Targets.begin(), ProjectData.Targets.end(), [&](const auto &target) { return target.Name == name; });
        return it != ProjectData.Targets.end() ? &(*it) : nullptr;
    }

    const OneStudioProject2::Target *findTargetData(const String &name) const
    {
        return const_cast<OSProject *>(this)->findTargetData(name);
    }

    const Array<Path> &getEntries() const { return ProjectData.Entries; }

    void addTargetTask(const String &targetPackage, const String &taskPackage);
    void removeTargetTask(const String &targetPackage, const String &taskPackage);

    const SharedReference<OSProjectTargetDataInstance> &findTarget(const String &name) const { return targets2.at(name); }

    String getNewTargetName() const;
    String getNewConfigurationName() const;

    void addTarget(const String &name, size_t index);
    void addTarget(const String &name);
    void addTarget(size_t index);
    void addTarget();
    void removeTarget(const String &name);
    void removeTarget(size_t index);

    void addConfiguration(const String &name, size_t index);
    void addConfiguration(const String &name);
    void addConfiguration(size_t index);
    void addConfiguration();
    void removeConfiguration(const String &name);
    void removeConfiguration(size_t index);

    bool load(const Path &path);
    bool save(const Path &path);

private:

    void appendSettings(Array<OneStudioProject2::Settings> &s, const String &package, const String &path, const Map<String, SharedReference<OSSettings> > &parentSettings, Map<String, size_t> &settingsMap, Map<String, SharedReference<OSSettings> > &settingsContainer);

    APath getSettingsDirectory() const;
    APath getSettingsPath(const String &filename) const;
    APath getConfigurationsDirectory() const;
    APath getConfigurationDirectory(const String &configurationName) const;
    APath getConfigurationPath(const String &configurationName, const String &filename) const;
    APath getTargetsDirectory() const;
    APath getTargetDirectory(const String &targetName) const;
    APath getTargetSettingsPath(const String &targetName, const String &filename) const;
    SharedReference<OSProjectTargetDataInstance> createTargetInstance(const String &name);

};
