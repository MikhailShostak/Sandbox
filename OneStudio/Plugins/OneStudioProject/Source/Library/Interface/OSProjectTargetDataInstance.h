#pragma once

#include <Data>

#include "OSTaskDataObject.h"
#include "OSTaskDataObject.inl"

#include "OSTaskPropertyDataObject.h"
#include "OSTaskPropertyDataObject.inl"

#include "OSBuildingSettingsDataObject.h"
#include "OSBuildingSettingsDataObject.inl"

#include "OSSettings.h"

class OSProjectTargetDataInstance : public AFileDataInstance<AJSONDataStorage>
{

public:

    StringHashMap<size_t> settingsMap;
    StringHashMap<SharedReference<OSSettings>> settings;

    Array<SharedReference<OSTaskDataObject>> findTasks(const String &stepType)
    {
        return getDataContext()->find<OSTaskDataObjectEntity::StepTypeField>(stepType);
    }

    SharedReference<OSTaskPropertyDataObject> createTaskProperty(const SharedReference<OSTaskDataObject> &task)
    {
        auto property = getDataContext()->create<OSTaskPropertyDataObject>();
        property->setTask(task);
        return property;
    }

    Array<SharedReference<OSTaskPropertyDataObject>> findTaskProperties(const SharedReference<OSTaskDataObject> &task)
    {
        return getDataContext()->find<OSTaskPropertyDataObjectEntity::TaskField>(task);
    }

    Array<SharedReference<OSTaskDataObject>> fetchTasks()
    {
        return getDataContext()->fetchAll<OSTaskDataObject>();
    }

    SharedReference<OSTaskDataObject> createTask()
    {
        return getDataContext()->create<OSTaskDataObject>();
    }

    void removeTask(const SharedReference<OSTaskDataObject> &task)
    {
        auto properties = findTaskProperties(task);
        getDataContext()->remove(properties);
        getDataContext()->remove(task);
    }

};
