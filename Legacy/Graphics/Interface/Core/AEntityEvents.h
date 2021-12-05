#pragma once

#include "AEvent.h"

class AEntity;

class AEntityEvent : public AEvent
{
public:
    AEntityEvent(AEntity &sender);
    AEntity &getEntity() const;
};
