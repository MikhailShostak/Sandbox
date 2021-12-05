//CLASSGEN GENERATED REGION: Includes
#include "TaskStatus.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Implementation
AStaticRun(TaskStatus)
{
    MetaObjectInformation::getInstance().enums.insert({ AMeta::getStaticTypeHash<TaskStatus>(), { "TaskStatus", { "Scheduled", "Started", "Paused", "Canceled", "Failed", "Completed" } } });
}
TaskStatus::TaskStatus()
{
    LinkStaticRun(TaskStatus);
}
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
