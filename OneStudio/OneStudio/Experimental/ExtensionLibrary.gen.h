#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include <Foundation>

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
template<typename PluginInterface>
class PluginLibrary
{
public:
    using PluginType = AApplicationPlugin<PluginInterface>;
private:
    APath directory;
    Array<SharedReference<PluginType>> plugins;
    PluginInterface *currentPlugin = nullptr;
    size_t countPlugins = 0;
    Map<PluginType *, Array<PluginType *>> dependencies;
public:

    const Array<SharedReference<PluginType>> &getPlugins() const { return plugins; }

    const APath & getDirectory() const
    {
        return directory;
    }
    void setDirectory(const APath &directory)
    {
        this->directory = directory;
    }
    AError load();
    void reload();
    void unload();
};

#include <OneStudioPlatform>

template<typename PluginInterface>
inline AError PluginLibrary<PluginInterface>::load()
{
    Map<String, Map<String, OSPluginContext *>> allContexts;
    Map<PluginType*, Array<PluginType*>> unsortedPlugins;
    for (auto &plugin : plugins)
    {
        auto &contexts = allContexts[plugin->getPackage()];
        auto &unsortedPlugin = unsortedPlugins[plugin.get()];
        for (auto &dependence : plugin->getInstance()->getDependencies())
        {
            auto dependentPlugin = ranges::find_if(plugins, [&dependence](const SharedReference<PluginType> &item) {
                return item->getPackage() == dependence.first;
            });

            static const char *FormatString = "Couldn't load plugin with package = \"{}\", because dependent plugin with package = \"{}\" {}";
            static const char *NotFoundReson = "not found";
            static const char *NoContextReson = "has no public context";

            if (dependentPlugin == plugins.end())
            {
                return AError(1, fmt::format(FormatString, plugin->getPackage(), dependence.first, NotFoundReson));
            }

            auto context = (*dependentPlugin)->getInstance()->getContext();
            if (!context)
            {
                return AError(2, fmt::format(FormatString, plugin->getPackage(), dependence.first, NoContextReson));
            }

            unsortedPlugin.push_back(dependentPlugin->get());
            contexts.insert({ dependence.first, context });
            dependencies[dependentPlugin->get()].push_back(plugin.get());
        }
    }

    Array<PluginType *> sortedPlugins;
    ADelegate<void(PluginType *plugin)> sortPluginsByDependencyRecursive = [&sortPluginsByDependencyRecursive, this, &unsortedPlugins, &sortedPlugins](PluginType *plugin) {
        auto dependencies = unsortedPlugins[plugin];
        for (auto &dependency : dependencies)
        {
            sortPluginsByDependencyRecursive(dependency);
        }
        ArrayUtils::AddUnique(sortedPlugins, plugin);
    };

    for (auto &plugin : plugins)
    {
        sortPluginsByDependencyRecursive(plugin.get());
    }

    /*for (auto &plugin : sortedPlugins)
    {
    log("Load plugin: " + plugin->getPackage());
    }*/

    for (auto &plugin : sortedPlugins)
    {
        auto &contexts = allContexts[plugin->getPackage()];
        currentPlugin = plugin->getInstance().get();
        currentPlugin->load(contexts);
        currentPlugin = nullptr;
    }

    return AError::getEmptyError();
}

template<typename PluginInterface>
inline void PluginLibrary<PluginInterface>::reload()
{
    ADirectory dir(directory);
    if (dir)
    {
        auto result = dir.find(ADefaultPluginExtension, AFindFilter::AllFiles);
        for (auto &info : result)
        {
            SharedReference<PluginType> plugin = CreateShared<PluginType>();
            plugin->setPath(info.path());
            //log(fmt::format("Load file: {}", plugin->getPath().toUnixPathString()));
            if (plugin->load() && plugin->getInstance())
            {
                //log("Plugin is loaded: " + info.path().name() + " (" + plugin->getPackage() + ")");
                plugins.push_back(plugin);
                countPlugins = plugins.size();
            }
        }
    }

    load();
    //loadPluginsSettings();
}

template<typename PluginInterface>
inline void PluginLibrary<PluginInterface>::unload()
{
    if (plugins.empty())
    {
        return;
    }

    //savePluginsSettings();

    /*editors.clear();

    for (auto &outliner : outliners)
    {
    outliner.second->clear();
    }
    outliners.clear();

    controlVersionSystems.clear();
    toolBarItems.clear();
    windows.clear();
    menus.clear();
    fileSystemItems.clear();
    fileTemplates.clear();

    if (propertiesDelegate)
    {
    propertiesDelegate(nullptr);
    propertiesDelegate = nullptr;
    }*/

    Map<PluginType*, Array<PluginType*>> unsortedPlugins;
    for (auto &plugin : plugins)
    {
        auto &unsortedPlugin = unsortedPlugins[plugin.get()];
        for (auto &dependence : plugin->getInstance()->getDependencies())
        {
            auto dependentPlugin = ranges::find_if(plugins, [&dependence](const SharedReference<PluginType> &item) {
                return item->getPackage() == dependence.first;
            });

            static const char *FormatString = "Couldn't load plugin with package = \"%s\", because dependent plugin with package = \"%s\" %s";
            static const char *NotFoundReson = "is not found";
            static const char *NoContextReson = "has no public context";

            if (dependentPlugin == plugins.end())
            {
                //error(fmt::format(FormatString, plugin->getPackage(), dependence.first, NotFoundReson));
                return;
            }

            auto context = (*dependentPlugin)->getInstance()->getContext();
            if (!context)
            {
                //error(fmt::format(FormatString, plugin->getPackage(), dependence.first, NoContextReson));
                return;
            }

            unsortedPlugin.push_back(dependentPlugin->get());
            dependencies[dependentPlugin->get()].push_back(plugin.get());
        }
    }

    Array<PluginType *> sortedPlugins;
    ADelegate<void(PluginType *plugin)> sortPluginsByDependencyRecursive = [&sortPluginsByDependencyRecursive, this, &unsortedPlugins, &sortedPlugins](PluginType *plugin) {
        auto dependencies = unsortedPlugins[plugin];
        for (auto &dependency : dependencies)
        {
            sortPluginsByDependencyRecursive(dependency);
        }
        if (!ArrayUtils::Contains(sortedPlugins, plugin))
        {
            sortedPlugins.push_back(plugin);
        }
    };

    for (auto &plugin : plugins)
    {
        sortPluginsByDependencyRecursive(plugin.get());
    }

    for (auto it = sortedPlugins.rbegin(); it != sortedPlugins.rend(); ++it)
    {
        //log("Unload plugin: " + (*it)->getPackage());
        currentPlugin = (*it)->getInstance().get();
        (*it)->getInstance()->unload();
        currentPlugin = nullptr;
        (*it)->unload();
    }
    plugins.clear();
    countPlugins = 0;
    dependencies.clear();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
