#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
#include <Experimental>

class OSPluginContext
{
public:

};

class OSPlugin
{

public:

    typedef OSPlugin This;

    virtual ~OSPlugin() {}

    using DependenciesList = Array<APair<String, String>>; // {package, version}

    virtual OSPluginContext *getContext() { return nullptr; }
    virtual DependenciesList getDependencies() const { return DependenciesList(); }

    virtual SharedReference<UI::View> getPluginSettingsView() const { return nullptr; }

    virtual void load(const Map<String, OSPluginContext *> &dependentPlugins) {}
    virtual void unload() {}

};

template<typename PluginSettingsViewType>
class OSTemplatePlugin : public OSPlugin
{

    SharedReference<PluginSettingsViewType> pluginSettingsView = createNew<PluginSettingsViewType>();

public:

    SharedReference<UI::View> getPluginSettingsView() const override { return pluginSettingsView.template as<UI::View>(); }

};

//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
