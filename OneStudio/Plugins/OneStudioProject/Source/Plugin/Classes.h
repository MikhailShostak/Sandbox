#pragma once"
#include "MetaObject.h"
#include "MetaObjectSerializationHelper.h"
#include "TaskView.gen.h"
#include "ProjectSettingsView.gen.h"
#include "ProjectToolBarView.gen.h"
inline void RegisterMetaClasses()
{

MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    MetaObject & object = manager.getMetaObject<OneStudioProject::TaskView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudioProject::TaskView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudioProject::TaskView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudioProject.TaskView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudioProject::ProjectSettingsView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudioProject::ProjectSettingsView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudioProject::ProjectSettingsView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::SplitView>();
    manager.registerMetaObject("OneStudioProject.ProjectSettingsView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudioProject::ProjectToolBarView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudioProject::ProjectToolBarView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudioProject::ProjectToolBarView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudioProject.ProjectToolBarView", object);
}

}
