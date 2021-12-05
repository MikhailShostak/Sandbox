#pragma once

#include "OSPTask.h"
#include "OSBuildTask.h"

class OSProject;
class OSProjectTargetDataInstance;
class OSSettings;

#include "ProjectData/Target.gen.h"

struct OSBuildingContextData
{
    OSProject *project = nullptr;
    OneStudioProject2::Target targetData;
    OSProjectTargetDataInstance *target = nullptr;
    StringHashMap<SharedReference<OSSettings>> settings;
    Array<String> values;

    SharedReference<OSBuildTaskSettings> getBuildTaskSettings() const
    {
        return settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>();
    }
};

class OSTargetTask : public OneStudioProject::Task
{

public:

    enum PropertyType
    {
        Boolean,
        String,
        Text,
        Path,
        List,
    };

    static String resolveVariables(const SharedReference<OSBuildTaskSettings> &buildingSettings, const String &text, const StringsHashMap &additionalValues = StringsHashMap::EmptyHashMap())
    {
        StringsHashMap values = {
            {"ProductName", buildingSettings->getItemValue(0, 0, 1)},
            //"SourcePaths", buildingSettings->getItemValue(0, 1, 1),
            {"BuildingDirectory", buildingSettings->getItemValue(0, 2, 1)},
            {"DestinationDirectory", buildingSettings->getItemValue(0, 3, 1)},
        };

        for(auto &pair : additionalValues)
        {
            values.insert(pair.first, pair.second);
        }

        return OSSettings::processWithEnvironment(text, values);
    }

    virtual Array<APair<PropertyType, String>> getProperties() const { return Array<APair<PropertyType, String>>::EmptyArray(); }

    AError execute(const OSBuildingContextData &data)
    {
        ASemaphore semaphore(1);
        AError resultError;
        semaphore.lock();
        onRun(data, [&semaphore, &resultError](const AError &error){
            resultError = error;
            semaphore.unlock();
        });
        semaphore.lock();
        semaphore.unlock();
        return resultError;
    }

    void run(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion)
    {
        onRun(data, completion);
    }

protected:

    virtual void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) = 0;

};
