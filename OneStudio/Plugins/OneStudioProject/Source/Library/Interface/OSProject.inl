#pragma once
inline const StringHashMap<SharedReference<OSSettings>> &OSProject::getSettings() const
{
    return settings;
}

inline APath OSProject::getSettingsDirectory() const
{
    return getDirectory() + "Settings/Project";
}

inline APath OSProject::getSettingsPath(const String &filename) const
{
    return (getSettingsDirectory() + filename).resolveWithExtension(OSSettingsExtension);
}

inline APath OSProject::getConfigurationsDirectory() const
{
    return getDirectory() + "Settings/Configurations";
}

inline APath OSProject::getConfigurationDirectory(const String &configurationName) const
{
    return getConfigurationsDirectory() + configurationName;
}

inline APath OSProject::getConfigurationPath(const String &configurationName, const String &filename) const
{
    return (getConfigurationDirectory(configurationName) + filename).resolveWithExtension(OSSettingsExtension);
}

inline APath OSProject::getTargetsDirectory() const
{
    return getDirectory() + "Settings/Targets";
}

inline APath OSProject::getTargetDirectory(const String &targetName) const
{
    return getTargetsDirectory() + targetName;
}

inline APath OSProject::getTargetSettingsPath(const String &targetName, const String &filename) const
{
    return (getTargetDirectory(targetName) + filename).resolveWithExtension(OSSettingsExtension);
}
