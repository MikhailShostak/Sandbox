#pragma once

#include <Foundation>

class ACreateEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class ADestroyEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AUpdateEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class ASaveEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class ALoadEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AUnloadEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class ATransformEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AShowEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AHideEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class ACloseEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AFocusInEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AFocusOutEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AMinimizeEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

class AMaximizeEvent : public AEvent
{
public:
    using AEvent::AEvent;
};

template<typename Type>
class UIPropertyChangeEvent : public AEvent
{
    Type value;
public:

    UIPropertyChangeEvent(AObject &sender, const Type &value):
        AEvent(sender),
        value(value)
    {}

    UIPropertyChangeEvent(AObject &sender, Type &&value):
        AEvent(sender),
        value(std::move(value))
    {}

    const Type &getValue() const { return this->value; }
};

class UITitleChangeEvent : public UIPropertyChangeEvent<String>
{
public:
    using Super = UIPropertyChangeEvent<String>;
    using Super::Super;
};

class UIMoveEvent : public UIPropertyChangeEvent<Math::IntegerVector>
{
public:
    using Super = UIPropertyChangeEvent<Math::IntegerVector>;
    using Super::Super;
};

class UIResizeEvent : public UIPropertyChangeEvent<Math::IntegerVector>
{
public:
    using Super = UIPropertyChangeEvent<Math::IntegerVector>;
    using Super::Super;
};

class UIGeometryChangeEvent : public UIPropertyChangeEvent<Math::IntegerRectangle>
{
public:
    using Super = UIPropertyChangeEvent<Math::IntegerRectangle>;
    using Super::Super;
};
