//CLASSGEN GENERATED REGION: Includes
#include "DropDownList.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
#include "UI/Views/UIMenu.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DropDownList::DropDownList()
{
    menu = SharedReference<UI::MenuView>(Create<UI::MenuView>());
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DropDownList::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Elements", toJSONValue(Elements));
    object.insert("CurrentIndex", toJSONValue(CurrentIndex));
}
void DropDownList::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Elements", value);
    fromJSONValue(value, Elements);
    value = AJSONValue();
    object.read("CurrentIndex", value);
    fromJSONValue(value, CurrentIndex);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<String> DropDownList::getElements() const
{
    return this->Elements;
}
void DropDownList::setElements(Array<String> const &Elements)
{
    this->Elements = Elements;
    updateMenuActions();
}
void DropDownList::setElements(Array<String> &&Elements)
{
    this->Elements = std::move(Elements);
    updateMenuActions();
}
SizeInteger DropDownList::getCurrentIndex() const
{
    return this->CurrentIndex;
}
void DropDownList::setCurrentIndex(SizeInteger const &CurrentIndex)
{
    this->CurrentIndex = CurrentIndex;
    updateCurrentItem();
}
void DropDownList::setCurrentIndex(SizeInteger &&CurrentIndex)
{
    this->CurrentIndex = std::move(CurrentIndex);
    updateCurrentItem();
}
//CLASSGEN END REGION

void DropDownList::onLoad(ALoadEvent &event)
{
    if (isLoaded())
    {
        return;
    }

    Super::onLoad(event);

    button->title->setTextAlign(Core::TextAlign::Start);
    button->setBackgroundImage(::DropDownList);
    button->background->setBorder(UIOffsets{ 2, 16, 12, 2 });

    menu->setName("menu");
    //menu->eventChannel;
    AttachMenuToView(button, menu, ATouchID::LeftMouseButton, [](UI::TapGestureEvent &event, const SharedReference<UI::View> &view, const SharedReference<UI::View> &menu) {
        Math::IntegerRectangle geometry;
        Math::IntegerVector viewBottomLeft = event.getWindowTouchEvent().getPosition() - Math::IntegerVector { event.getPoint().X, -(view->getSize().Y - event.getPoint().Y) + 1 };
        geometry.Position = event.getView().getOwner()->getWindow()->getGeometry().position + viewBottomLeft;
        geometry.Size = view->getSize();
        return geometry;
    });
}

void DropDownList::onLayout(AUpdateEvent &event)
{
    if (isNeededLayoutUpdate())
    {
        button->setSize(getSize());
    }

    Super::onLayout(event);
}

void DropDownList::updateMenuActions()
{
    menu->removeAllActions();
    size_t i = 0;
    for (const String &element : Elements)
    {
        //TODO: optimize menu callbacks
        menu->addAction({ element, [this, i, element](TapGestureEvent &event) {
            this->CurrentIndex = i;
            button->setText(element);
            CurrentIndexChangedEvent e(*this, i);
            eventChannel.sendEvent(e);
        } });
        ++i;
    }
}

void DropDownList::updateCurrentItem()
{
    if (this->CurrentIndex == size_t(-1))
    {
        button->setText("");
        CurrentIndexSetEvent e(*this, this->CurrentIndex);
        eventChannel.sendEvent(e);
        return;
    }

    button->setText(getElements()[this->CurrentIndex]);
    CurrentIndexSetEvent e(*this, this->CurrentIndex);
    eventChannel.sendEvent(e);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

