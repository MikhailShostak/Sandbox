#pragma once

#include <Data>

class OSTargetBuilder
{
public:

    virtual bool onBuild(const APath &projectDirectory) { return true; }
    virtual bool onClean(const APath &projectDirectory) { return true; }

    virtual bool onInstall(const APath &projectDirectory) { return true; }
    virtual bool onUninstall(const APath &projectDirectory) { return true; }

    virtual bool onRun(const APath &projectDirectory) { return true; }

};

template<typename PluginSettingsDataInstanceType, typename ProjectSettingsDataInstanceType>
class OSTemplateTargetBuilder : public OSTargetBuilder
{

    //static_assert(std::is_base_of<PluginSettingsDataInstanceType, ADataInstance>::value, "PluginSettingsDataInstanceType must be base of a ADataInstance");
    //static_assert(std::is_base_of<ProjectSettingsDataInstanceType, ADataInstance>::value, "ProjectSettingsDataInstanceType must be base of a ADataInstance");

    SharedReference<PluginSettingsDataInstanceType> pluginSettingsDataInstance;
    SharedReference<ProjectSettingsDataInstanceType> projectSettingsDataInstance;

public:

    const SharedReference<PluginSettingsDataInstanceType> &getPluginSettingsDataInstance() const
    {
        return this->pluginSettingsDataInstance;
    }

    void setPluginSettingsDataInstance(const SharedReference<PluginSettingsDataInstanceType> &pluginSettingsDataInstance)
    {
        this->pluginSettingsDataInstance = pluginSettingsDataInstance;
    }

    const SharedReference<ProjectSettingsDataInstanceType> &getProjectSettingsDataInstance() const
    {
        return projectSettingsDataInstance;
    }

    void setProjectSettingsDataInstance(const SharedReference<ProjectSettingsDataInstanceType> &projectSettingsDataInstance)
    {
        this->projectSettingsDataInstance = projectSettingsDataInstance;
    }

};
