//CLASSGEN GENERATED REGION: Includes
#include "Task.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "TaskManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
void Task::startInternal()
{
//     co_await TaskManager::getThisInstance().getMainWorker().schedule();
//     status = TaskStatus::Started;
//     startTime = ASystemClock::now();
//     if (onUpdated)
//     {
//         onUpdated();
//     }
// 
//     co_await TaskManager::getThisInstance().getAsyncWorkers().schedule();
//     for(auto &subtask : subtasks)
//     {
//         co_await subtask->startInternal();
//         if(subtask->status != TaskStatus::Completed)
//         {
//             co_await TaskManager::getThisInstance().getMainWorker().schedule();
//             status = subtask->status;
//             endTime = ASystemClock::now();
//             if (onUpdated)
//             {
//                 onUpdated();
//             }
//             co_return;
//         }
//     }
//     
//     if(action)
//     {
//         co_await TaskManager::getThisInstance().getAsyncWorkers().schedule();
//         co_await action(*this);
//         log.append(Str::Format("Finished with code: {}", error_code));
//     }
//     
//     co_await TaskManager::getThisInstance().getMainWorker().schedule();
//     status = error_code == 0 ? TaskStatus::Completed : TaskStatus::Failed;
//     endTime = ASystemClock::now();
//     if (onUpdated)
//     {
//         onUpdated();
//     }
//     co_return;


    status = TaskStatus::Started;
    startTime = ASystemClock::now();
    if (onUpdated)
    {
        onUpdated();
    }

    for(auto &subtask : subtasks)
    {
        subtask->startInternal();
        if(subtask->status != TaskStatus::Completed)
        {
            status = subtask->status;
            endTime = ASystemClock::now();
            if (onUpdated)
            {
                onUpdated();
            }
        }
    }
    
    if(action)
    {
        action(*this);
        log.push_back(Str::Format("Finished with code: {}", error_code));
    }
    
    status = error_code == 0 ? TaskStatus::Completed : TaskStatus::Failed;
    endTime = ASystemClock::now();
    if (onUpdated)
    {
        onUpdated();
    }
}

void Task::start()
{
    startInternal();
    //TaskManager::getThisInstance().getAsyncWorkers().run_async_task(startInternal());
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
