#pragma once

#include <Foundation>

class AGraphicsContext;

class AGraphicsEvent : public AEvent
{
public:
    AGraphicsEvent(AGraphicsContext &sender);
    AGraphicsContext &getContext() const;
};

class AUpdateGraphicsEvent : public AGraphicsEvent
{
public:

    enum UpdateType
    {
        UpdateColor,
        UpdateViewort,
        UpdateCamera,
        UpdateBlending,
        UpdateCulling,
        UpdateWritingDepth,
        UpdateUsingDepth,
        UpdateDepthFunction,
    };

private:
    UpdateType type;

public:
    AUpdateGraphicsEvent(AGraphicsContext &sender, UpdateType type);
    UpdateType getType() const;
};

class AClearGraphicsEvent : public AGraphicsEvent
{
public:
    using AGraphicsEvent::AGraphicsEvent;
};

class ADrawGraphicsEvent : public AGraphicsEvent
{
public:
    using AGraphicsEvent::AGraphicsEvent;
};

class AFlushGraphicsEvent : public AGraphicsEvent
{
public:
    using AGraphicsEvent::AGraphicsEvent;
};
