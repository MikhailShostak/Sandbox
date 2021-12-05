#pragma once

#include <OneStudioPlatform>
#include <Experimental>

class CGPrivatePlugin : public OSPlugin
{
public:
    void load(const Map<String, OSPluginContext *> &dependentPlugins) override;
};
