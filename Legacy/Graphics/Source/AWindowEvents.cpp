#include "AWindowEvents.h"
#include "AWindow.h"

AWindowEvent::AWindowEvent(AWindow &sender):
    AEvent(sender)
{

}

AWindow &AWindowEvent::getWindow() const
{
    return static_cast<AWindow &>(getSender());
}
