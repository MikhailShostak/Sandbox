//        Author: Insane Team
//          File: _OSProjectTargetDataInstance.inl
// Creation date: 01/11/17 04:27:46
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const Map<String,size_t> &OSProjectTargetDataInstance::getSettingsMap() const
{
    return this->settingsMap;
}

inline void OSProjectTargetDataInstance::setSettingsMap(const Map<String,size_t> &settingsMap)
{
    this->settingsMap = settingsMap;
}

inline void OSProjectTargetDataInstance::setSettingsMap(Map<String,size_t> &&settingsMap)
{
    this->settingsMap = std::move(settingsMap);
}

inline const AMap<String,SharedReference<_OSSettings>> &OSProjectTargetDataInstance::getSettings() const
{
    return this->settings;
}

inline void OSProjectTargetDataInstance::setSettings(const AMap<String,SharedReference<_OSSettings>> &settings)
{
    this->settings = settings;
}

inline void OSProjectTargetDataInstance::setSettings(AMap<String,SharedReference<_OSSettings>> &&settings)
{
    this->settings = std::move(settings);
}

