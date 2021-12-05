#include "AEntityEvents.h"
#include "AEntity.h"

AEntityEvent::AEntityEvent(AEntity &sender):
    AEvent(sender)
{

}

AEntity &AEntityEvent::getEntity() const
{
    return static_cast<AEntity &>(getSender());
}
