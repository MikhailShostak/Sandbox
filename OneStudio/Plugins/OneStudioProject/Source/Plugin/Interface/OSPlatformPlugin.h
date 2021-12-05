#pragma once

#include <OneStudioPlatform>

class OSPlatformPlugin
{
public:

    virtual String getPackage() const = 0;

    virtual SharedReference<UI::View> getPluginSettingsView() const = 0;
    virtual SharedReference<UI::View> getTargetSettingsView() const = 0;

};

class OSProjectContext;

class OSProjectPluginContext : public OSPluginContext
{
public:

    virtual OSProjectContext &getProjectContext() = 0;

    virtual class OSTaskPlugin *getTask(const String &package) = 0;
    virtual void registerPlatform(OSPlatformPlugin *platformPlugin) = 0;

    virtual void addDefinition(const String &definition, const String &path) = 0;
    virtual void removeDefinition(const String &definition) = 0;

};

template<typename PluginSettingsViewType, typename TargetSettingsViewType>
class OSTemplatePlatformPlugin : public OSPlatformPlugin, public OSPlugin
{

    SharedReference<PluginSettingsViewType> pluginSettingsView = createNew<PluginSettingsViewType>();
    SharedReference<TargetSettingsViewType> targetSettingsView = createNew<TargetSettingsViewType>();

public:

    SharedReference<UI::View> getPluginSettingsView() const override { return pluginSettingsView.template as<UI::View>(); }
    SharedReference<UI::View> getTargetSettingsView() const override { return targetSettingsView.template as<UI::View>(); }

    DependenciesList getDependencies() const override { return {{"com.InsaneTeam.OneStudio.Project", "1.0.0"}}; }

    void load(const Map<String, OSPluginContext *> &dependentPlugins) override
    {
        OSProjectPluginContext *plugin = static_cast<OSProjectPluginContext *>(dependentPlugins.at("com.InsaneTeam.OneStudio.Project"));
        plugin->registerPlatform(this);
    }

};
