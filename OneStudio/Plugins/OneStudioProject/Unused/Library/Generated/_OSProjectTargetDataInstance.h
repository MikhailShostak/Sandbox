//        Author: Insane Team
//          File: _OSProjectTargetDataInstance.h
// Creation date: 01/11/17 04:27:45
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <AData>
#include <AFoundation>
#include <AJSON>
#include <cstdint>

#include "_OSSettings.h"

//       Class: OSProjectTargetDataInstance
//        Base: AFileDataInstance<AJSONDataStorage>
//        Link: 
// Description: 

class OSProjectTargetDataInstance : public AFileDataInstance<AJSONDataStorage>
{
    typedef OSProjectTargetDataInstance This;
    typedef AFileDataInstance<AJSONDataStorage> Super;

    Map<String,size_t> settingsMap;
    AMap<String,SharedReference<_OSSettings>> settings;

public:
    virtual ~OSProjectTargetDataInstance() {}

public:
    virtual const Map<String,size_t> &getSettingsMap() const;
    virtual void setSettingsMap(const Map<String,size_t> &settingsMap);
    virtual void setSettingsMap(Map<String,size_t> &&settingsMap);

public:
    virtual const AMap<String,SharedReference<_OSSettings>> &getSettings() const;
    virtual void setSettings(const AMap<String,SharedReference<_OSSettings>> &settings);
    virtual void setSettings(AMap<String,SharedReference<_OSSettings>> &&settings);
};


