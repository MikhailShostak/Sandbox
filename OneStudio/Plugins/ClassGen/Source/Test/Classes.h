#pragma once"
#include "MetaObject.h"
#include "MetaObjectSerializationHelper.h"
#include "TestView.gen.h"
inline void RegisterMetaClasses()
{

MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    MetaObject & object = manager.getMetaObject<UI::TestView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::TestView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::TestView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    object.registerMetaProperty<UI::TestView, Boolean, Boolean(UI::TestView::*)() const, void(UI::TestView::*)(const Boolean &)>("Test1", &UI::TestView::getTest1, &UI::TestView::setTest1, true);
    object.registerMetaProperty<UI::TestView, Boolean, Boolean(UI::TestView::*)() const, void(UI::TestView::*)(const Boolean &)>("Test2", &UI::TestView::getTest2, &UI::TestView::setTest2, true);
    manager.registerMetaObject("UI.TestView", object);
}

}
