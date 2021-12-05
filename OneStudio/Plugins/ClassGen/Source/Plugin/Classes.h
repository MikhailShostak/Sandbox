#pragma once
#include "MetaObject.h"
#include "MetaObjectSerializationHelper.h"
#include "EditorView.gen.h"
#include "ExtensionEditor.gen.h"
inline void RegisterMetaClasses2()
{

MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    MetaObject & object = manager.getMetaObject<UI::EditorView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::EditorView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::EditorView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("UI.EditorView", object);
}
{
    MetaObject & object = manager.getMetaObject<LegacyClassGen::ExtensionEditor>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const LegacyClassGen::ExtensionEditor&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<LegacyClassGen::ExtensionEditor&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("ClassGen.ExtensionEditor", object);
}

}
