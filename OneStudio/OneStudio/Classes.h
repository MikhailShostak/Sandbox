#pragma once"
#include "MetaObject.h"
#include "MetaObjectSerializationHelper.h"
#include "EnvironmentVariablesGroupView.gen.h"
#include "AboutView.gen.h"
#include "EnvironmentVariablesView.gen.h"
#include "ExtensionsView.gen.h"
#include "MainView.gen.h"
#include "CreateFileDialog.gen.h"
#include "NewFileView.gen.h"
#include "OpenFileView.gen.h"
#include "RenameFileDialog.gen.h"
#include "FindFilePopup.gen.h"
#include "FindSymbolPopup.gen.h"
#include "DeveloperLibraryView.gen.h"
#include "SettingsView.gen.h"
#include "ToolbarSettingsView.gen.h"
#include "TasksProgressEntryView.gen.h"
#include "TasksProgressView.gen.h"
#include "TypesView.gen.h"
#include "RecentFilesView.gen.h"
inline void RegisterMetaClasses()
{

MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    MetaObject & object = manager.getMetaObject<OneStudio::EnvironmentVariablesGroupView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::EnvironmentVariablesGroupView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::EnvironmentVariablesGroupView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    object.registerMetaProperty<OneStudio::EnvironmentVariablesGroupView, Text, Text(OneStudio::EnvironmentVariablesGroupView::*)() const, void(OneStudio::EnvironmentVariablesGroupView::*)(const Text &)>("Title", &OneStudio::EnvironmentVariablesGroupView::getTitle, &OneStudio::EnvironmentVariablesGroupView::setTitle, true);
    manager.registerMetaObject("OneStudio.EnvironmentVariablesGroupView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::AboutView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::AboutView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::AboutView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("OneStudio.AboutView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::EnvironmentVariablesView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::EnvironmentVariablesView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::EnvironmentVariablesView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.EnvironmentVariablesView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::ExtensionsView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::ExtensionsView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::ExtensionsView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::ListView>();
    manager.registerMetaObject("OneStudio.ExtensionsView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::MainView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::MainView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::MainView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.MainView", object);
}
{
    MetaObject & object = manager.getMetaObject<CreateFileDialog>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const CreateFileDialog&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<CreateFileDialog&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::View>();
    manager.registerMetaObject("CreateFileDialog", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::NewFileView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::NewFileView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::NewFileView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.NewFileView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::OpenFileView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::OpenFileView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::OpenFileView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.OpenFileView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::RenameFileDialog>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::RenameFileDialog&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::RenameFileDialog&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::View>();
    manager.registerMetaObject("UI.RenameFileDialog", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::FindFilePopup>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::FindFilePopup&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::FindFilePopup&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::PopupView>();
    manager.registerMetaObject("UI.FindFilePopup", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::FindSymbolPopup>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::FindSymbolPopup&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::FindSymbolPopup&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::PopupView>();
    manager.registerMetaObject("UI.FindSymbolPopup", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::DeveloperLibraryView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::DeveloperLibraryView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::DeveloperLibraryView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.DeveloperLibraryView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::SettingsView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::SettingsView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::SettingsView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.SettingsView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::ToolbarSettingsView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::ToolbarSettingsView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::ToolbarSettingsView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.ToolbarSettingsView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::TasksProgressEntryView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::TasksProgressEntryView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::TasksProgressEntryView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.TasksProgressEntryView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::TasksProgressView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::TasksProgressView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::TasksProgressView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.TasksProgressView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::TypesView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::TypesView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::TypesView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("OneStudio.TypesView", object);
}
{
    MetaObject & object = manager.getMetaObject<OneStudio::RecentFilesView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const OneStudio::RecentFilesView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<OneStudio::RecentFilesView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    object.registerMetaProperty<OneStudio::RecentFilesView, Text, Text(OneStudio::RecentFilesView::*)() const, void(OneStudio::RecentFilesView::*)(const Text &)>("Title", &OneStudio::RecentFilesView::getTitle, &OneStudio::RecentFilesView::setTitle, true);
    manager.registerMetaObject("OneStudio.RecentFilesView", object);
}

}
