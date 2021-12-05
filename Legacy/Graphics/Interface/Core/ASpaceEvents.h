#pragma once

#include "AEvent.h"

class ASpace;

class ASpaceEvent : public AEvent
{
public:
    ASpaceEvent(ASpace &sender);
    ASpace &getSpace() const;
};

class AAddToSpaceEvent : public ASpaceEvent
{
public:
    using ASpaceEvent::ASpaceEvent;
};

class ARemoveFromSpaceEvent : public ASpaceEvent
{
public:
    using ASpaceEvent::ASpaceEvent;
};
