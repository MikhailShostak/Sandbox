#include "AGraphicsEvents.h"

#include "AGraphicsContext.h"

AGraphicsEvent::AGraphicsEvent(AGraphicsContext &sender):
    AEvent(sender)
{

}

AGraphicsContext &AGraphicsEvent::getContext() const
{
    return static_cast<AGraphicsContext &>(getSender());
}

AUpdateGraphicsEvent::AUpdateGraphicsEvent(AGraphicsContext &sender, UpdateType type):
    AGraphicsEvent(sender),
    type(type)
{

}

AUpdateGraphicsEvent::UpdateType AUpdateGraphicsEvent::getType() const
{
    return type;
}
