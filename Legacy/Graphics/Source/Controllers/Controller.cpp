#include "Controller.h"
#include "MetaObject.h"

AStaticRun(ControllerMetaObject)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<Controller>();
    object.baseObject = &manager.getMetaObject<AObject>();
}
