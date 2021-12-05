#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include <Foundation>
#include "Includes/AbstractSingleton.gen.h"
#include "Includes/Task.gen.h"

class AEventDispatcher;
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class TaskContext : public AbstractSingleton<TaskContext>
{
public:
    virtual AEventDispatcher &getEventDispatcher() const = 0;
    virtual AOperationDispatcher *getOperationDispatcher() const = 0;

    virtual SharedReference<OneStudioPlatform::Task> startTask() = 0;
    virtual void finishTask(const SharedReference<OneStudioPlatform::Task> &task) = 0;
    virtual void clearTasks() = 0;

    //virtual ServiceScheduler& getMainWorker() = 0;
    //virtual ThreadPoolScheduler& getAsyncWorkers() = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
