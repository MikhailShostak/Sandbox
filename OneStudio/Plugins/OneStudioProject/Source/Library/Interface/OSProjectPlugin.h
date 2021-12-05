#pragma once

#include <OneStudioPlatform>

class OSProjectPlugin
{

public:

    virtual SharedReference<UI::View> getProjectSettingsView() const { return nullptr; }

};

template<typename PluginSettingsViewType, typename ProjectSettingsViewType>
class OSTemplateProjectPlugin : public OSTemplatePlugin<PluginSettingsViewType>, public OSProjectPlugin
{

    SharedReference<ProjectSettingsViewType> projectSettingsView = createNew<ProjectSettingsViewType>();

public:

    SharedReference<UI::View> getProjectSettingsView() const override { return projectSettingsView.template as<UI::View>(); }

};
