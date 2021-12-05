//CLASSGEN GENERATED REGION: Includes
#include "Switch.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "UIComponent.h"
#include <Graphics>
#include <UIDarkTheme>
#include "UITouchGestureRecognizer.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Switch::Switch()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Switch::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("On", toJSONValue(On));
}
void Switch::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("On", value);
    fromJSONValue(value, On);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Boolean Switch::getOn() const
{
    return this->On;
}
void Switch::setOn(Boolean const &On)
{
    this->On = On;
    SendSwitchEvent();
}
void Switch::setOn(Boolean &&On)
{
    this->On = std::move(On);
    SendSwitchEvent();
}
//CLASSGEN END REGION

void Switch::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if(!button)
    {
        button = CreateShared<Button>();
        button->setName("Button");
        button->eventChannel.registerDelegate([this](TapGestureEvent &event) {
            setOn(!isOn());
            UserSwitchEvent e(*this, this->On);
            eventChannel.sendEvent(e);
            getOwner()->getWindow()->setFocus(*this);
            if(OnSwitch)
            {
                OnSwitch();
            }
        });
        UpdateIcon();
        addView(button);
    }
}

void Switch::onLayout(AUpdateEvent &event)
{
    if (isNeededLayoutUpdate())
    {
        button->setSize(getSize());
    }
    Super::onLayout(event);
}

void Switch::onUnload(AUnloadEvent &event)
{
    getOwner()->getWindow()->removeFocus(*this);
    Super::onUnload(event);
}

void Switch::UpdateIcon()
{
    if (!this->button)
    {
        return;
    }

    if (On)
    {
        this->button->setBackgroundImage(::CheckButtonSmall);
    }
    else
    {
        this->button->setBackgroundImage(::ButtonBackground);
    }
}

void Switch::SendSwitchEvent()
{
    UpdateIcon();
    if(OnChange)
    {
        OnChange();
    }
    SwitchEvent e(*this, this->On);
    eventChannel.sendEvent(e);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
