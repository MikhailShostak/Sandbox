#pragma once

#include <OneStudioPlatform>
#include <OneStudioProjectLibrary>

#include "OSPlatformPlugin.h"

extern const char *OSProjectPluginPackage;
extern const char *OSProjectPluginVersion;

extern Map<String, OSPlatformPlugin*> PlatformPlugins;
