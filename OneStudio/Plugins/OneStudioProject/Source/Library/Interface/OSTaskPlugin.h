#pragma once

#include "Main.h"
#include "OSSettings.h"

class OSTaskPlugin
{
public:

    virtual ~OSTaskPlugin() {}

    virtual Array<String> getDependencies() const { return Array<String>::EmptyArray(); }
    virtual SharedReference<OSTargetTask> getTask() const = 0;
    virtual SharedReference<OSSettings> createSettings() const = 0;

    virtual void onLoad(OSProjectContext *context) {}
    virtual void onUnload() {}

    virtual SharedReference<OneStudioProject2::SettingsInstance> createSettings2() const { return nullptr; }
};

template<typename TaskType, typename SettingsType>
class OSTemplateTaskPlugin : public OSTaskPlugin, public OSProjectObserver
{

    SharedReference<TaskType> task = createNew<TaskType>();

public:

    void onLoad(OSProjectContext *context)
    {
        context->addObserver(this);
    }

    void onUnload(OSProjectContext *context)
    {
        context->removeObserver(this);
    }

    SharedReference<OSTargetTask> getTask() const override
    {
        return task;
    }

    SharedReference<OSSettings> createSettings() const override
    {
        return new SettingsType();
    }

    SharedReference<OneStudioProject2::SettingsInstance> createSettings2() const override
    {
        return new SettingsType();
    }

};
