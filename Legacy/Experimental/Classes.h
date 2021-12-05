#pragma once

#include "MetaObject.h"
#include "MetaObjectSerializationHelper.h"
#include "GridView.gen.h"
#include "DefaultTextItemView.gen.h"
#include "GroupHeader.gen.h"
#include "Button.gen.h"
#include "ApplicationHeader.gen.h"
#include "ColorPicker.gen.h"
#include "DockView.gen.h"
#include "Pin.gen.h"
#include "TabItem.gen.h"
#include "TabView.gen.h"
#include "KeyBindingView.gen.h"
#include "PathField.gen.h"
#include "ProgressBar.gen.h"
#include "ToolTipView.gen.h"
#include "DefaultExpandableItemView.gen.h"
#include "DefaultIconItemView.gen.h"
#include "DefaultTabItemView.gen.h"
#include "DropDown.gen.h"
#include "InvertedPanel.gen.h"
#include "Panel.gen.h"
#include "NamedNodeView.gen.h"
#include "NodeView.gen.h"
#include "PinNodeView.gen.h"
#include "PinNodeViewWithPreview.gen.h"
#include "PopupView.gen.h"
#include "ScrollView.gen.h"
#include "Slider.gen.h"
#include "TextButton.gen.h"
#include "UIDraggingGestureRecognizer.h"

inline void RegisterMetaClasses()
{
/*
MetaObjectManager &manager = MetaObjectManager::getInstance();
{
    MetaObject & object = manager.getMetaObject<UI::GridView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::GridView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::GridView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Panel>();
    manager.registerMetaObject("UI.GridView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DefaultTextItemView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DefaultTextItemView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DefaultTextItemView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("UI.DefaultTextItemView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::GroupHeader>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::GroupHeader&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::GroupHeader&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.GroupHeader", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::Button>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::Button&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::Button&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    object.registerMetaProperty<UI::Button, SharedReference<Graphics::Texture>, SharedReference<Graphics::Texture>(UI::Button::*)() const, void(UI::Button::*)(const SharedReference<Graphics::Texture> &)>("BackgroundImage", &UI::Button::getBackgroundImage, &UI::Button::setBackgroundImage, true);
    manager.registerMetaObject("UI.Button", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::ApplicationHeader>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::ApplicationHeader&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::ApplicationHeader&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("UI.ApplicationHeader", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::ColorPicker>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::ColorPicker&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::ColorPicker&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("UI.ColorPicker", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DockView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DockView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DockView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::SplitView>();
    object.registerMetaProperty<UI::DockView, Array<UI::DockViewArea>, Array<UI::DockViewArea>(UI::DockView::*)() const, void(UI::DockView::*)(const Array<UI::DockViewArea> &)>("Areas", &UI::DockView::getAreas, &UI::DockView::setAreas, true);
    manager.registerMetaObject("UI.DockView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::Pin>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::Pin&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::Pin&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    object.registerMetaProperty<UI::Pin, UI::PinType, UI::PinType(UI::Pin::*)() const, void(UI::Pin::*)(const UI::PinType &)>("Type", &UI::Pin::getType, &UI::Pin::setType, true);
    object.registerMetaProperty<UI::Pin, Boolean, Boolean(UI::Pin::*)() const, void(UI::Pin::*)(const Boolean &)>("ConnectionSource", &UI::Pin::getConnectionSource, &UI::Pin::setConnectionSource, true);
    manager.registerMetaObject("UI.Pin", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::TabItem>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::TabItem&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::TabItem&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.TabItem", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::TabView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::TabView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::TabView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    object.registerMetaProperty<UI::TabView, Array<Text>, Array<Text>(UI::TabView::*)() const, void(UI::TabView::*)(const Array<Text> &)>("Tabs", &UI::TabView::getTabs, &UI::TabView::setTabs, true);
    manager.registerMetaObject("UI.TabView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::KeyBindingView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::KeyBindingView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::KeyBindingView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::TextField>();
    object.registerMetaProperty<UI::KeyBindingView, Core::Shortcut, Core::Shortcut(UI::KeyBindingView::*)() const, void(UI::KeyBindingView::*)(const Core::Shortcut &)>("Shortcut", &UI::KeyBindingView::getShortcut, &UI::KeyBindingView::setShortcut, true);
    manager.registerMetaObject("UI.KeyBindingView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::PathField>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::PathField&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::PathField&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::FlexBox>();
    manager.registerMetaObject("UI.PathField", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::ToolTipView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::ToolTipView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::ToolTipView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.ToolTipView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DefaultExpandableItemView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DefaultExpandableItemView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DefaultExpandableItemView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::DefaultIconItemView>();
    manager.registerMetaObject("UI.DefaultExpandableItemView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DefaultIconItemView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DefaultIconItemView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DefaultIconItemView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::DefaultTextItemView>();
    manager.registerMetaObject("UI.DefaultIconItemView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DefaultTabItemView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DefaultTabItemView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DefaultTabItemView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::DefaultTextItemView>();
    manager.registerMetaObject("UI.DefaultTabItemView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::DropDown>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::DropDown&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::DropDown&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.DropDown", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::InvertedPanel>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::InvertedPanel&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::InvertedPanel&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Panel>();
    manager.registerMetaObject("UI.InvertedPanel", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::Panel>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::Panel&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::Panel&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.Panel", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::NamedNodeView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::NamedNodeView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::NamedNodeView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::NodeView>();
    manager.registerMetaObject("UI.NamedNodeView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::NodeView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::NodeView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::NodeView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Panel>();
    manager.registerMetaObject("UI.NodeView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::PinNodeView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::PinNodeView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::PinNodeView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::NamedNodeView>();
    manager.registerMetaObject("UI.PinNodeView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::PinNodeViewWithPreview>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::PinNodeViewWithPreview&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::PinNodeViewWithPreview&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::PinNodeView>();
    manager.registerMetaObject("UI.PinNodeViewWithPreview", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::PopupView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::PopupView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::PopupView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    manager.registerMetaObject("UI.PopupView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::ScrollView>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::ScrollView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::ScrollView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Overlay>();
    object.registerMetaProperty<UI::ScrollView, Math::IntegerVector, Math::IntegerVector(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const Math::IntegerVector &)>("InternalSize", &UI::ScrollView::getInternalSize, &UI::ScrollView::setInternalSize, true);
    object.registerMetaProperty<UI::ScrollView, Boolean, Boolean(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const Boolean &)>("AlwaysShowVerticalShadow", &UI::ScrollView::getAlwaysShowVerticalShadow, &UI::ScrollView::setAlwaysShowVerticalShadow, true);
    object.registerMetaProperty<UI::ScrollView, Boolean, Boolean(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const Boolean &)>("AlwaysShowHorizontalShadow", &UI::ScrollView::getAlwaysShowHorizontalShadow, &UI::ScrollView::setAlwaysShowHorizontalShadow, true);
    object.registerMetaProperty<UI::ScrollView, UI::ContentFit, UI::ContentFit(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const UI::ContentFit &)>("ContentFit", &UI::ScrollView::getContentFit, &UI::ScrollView::setContentFit, true);
    object.registerMetaProperty<UI::ScrollView, Math::Offsets, Math::Offsets(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const Math::Offsets &)>("ContentPaddings", &UI::ScrollView::getContentPaddings, &UI::ScrollView::setContentPaddings, true);
    object.registerMetaProperty<UI::ScrollView, UI::ScrollBarVisibility, UI::ScrollBarVisibility(UI::ScrollView::*)() const, void(UI::ScrollView::*)(const UI::ScrollBarVisibility &)>("SliderVisibility", &UI::ScrollView::getSliderVisibility, &UI::ScrollView::setSliderVisibility, true);
    manager.registerMetaObject("UI.ScrollView", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::Slider>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::Slider&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::Slider&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::View>();
    object.registerMetaProperty<UI::Slider, SignedInteger, SignedInteger(UI::Slider::*)() const, void(UI::Slider::*)(const SignedInteger &)>("HandlePosition", &UI::Slider::getHandlePosition, &UI::Slider::setHandlePosition, true);
    object.registerMetaProperty<UI::Slider, SizeInteger, SizeInteger(UI::Slider::*)() const, void(UI::Slider::*)(const SizeInteger &)>("HandleSize", &UI::Slider::getHandleSize, &UI::Slider::setHandleSize, true);
    object.registerMetaProperty<UI::Slider, SizeInteger, SizeInteger(UI::Slider::*)() const, void(UI::Slider::*)(const SizeInteger &)>("SliderSize", &UI::Slider::getSliderSize, &UI::Slider::setSliderSize, true);
    object.registerMetaProperty<UI::Slider, Math::Offsets, Math::Offsets(UI::Slider::*)() const, void(UI::Slider::*)(const Math::Offsets &)>("SliderBorder", &UI::Slider::getSliderBorder, &UI::Slider::setSliderBorder, true);
    object.registerMetaProperty<UI::Slider, SharedReference<DraggingGestureRecognizer>, SharedReference<DraggingGestureRecognizer>(UI::Slider::*)() const, void(UI::Slider::*)(const SharedReference<DraggingGestureRecognizer> &)>("DraggingComponent", &UI::Slider::getDraggingComponent, &UI::Slider::setDraggingComponent, true);
    manager.registerMetaObject("UI.Slider", object);
}
{
    MetaObject & object = manager.getMetaObject<UI::TextButton>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const UI::TextButton&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<UI::TextButton&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<UI::Button>();
    object.registerMetaProperty<UI::TextButton, String, String(UI::TextButton::*)() const, void(UI::TextButton::*)(const String &)>("Text", &UI::TextButton::getText, &UI::TextButton::setText, true);
    manager.registerMetaObject("UI.TextButton", object);
}*/

}
