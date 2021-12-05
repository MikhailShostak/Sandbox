#include "WindowController.h"
#include "MetaObject.h"

AStaticRun(WindowControllerMetaObject)
{
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<WindowController>();
    object.baseObject = &manager.getMetaObject<Controller>();
    object.registerMetaProperty<WindowController, ::SharedReference<AWindow>>("Window", &WindowController::getWindow, &WindowController::setWindow);
}

WindowController::WindowController()
{
    LinkStaticRun(WindowControllerMetaObject);
}
