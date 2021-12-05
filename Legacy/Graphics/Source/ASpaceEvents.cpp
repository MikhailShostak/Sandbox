#include "ASpaceEvents.h"
#include "ASpace.h"

ASpaceEvent::ASpaceEvent(ASpace &sender):
    AEvent(sender)
{

}

ASpace &ASpaceEvent::getSpace() const
{
    return static_cast<ASpace &>(getSender());
}
