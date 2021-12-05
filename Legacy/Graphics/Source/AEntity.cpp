#include "AEntity.h"

#include "AComponent.h"
#include "ASpace.h"
#include "ASpaceEvents.h"
#include "AWindowEvents.h"

AEntity::AEntity()
{
    ARegisterEventCallback(onAddToSpace);
    ARegisterEventCallback(onRemoveFromSpace);
    ARegisterEventCallback(onAddToWindow);
    ARegisterEventCallback(onRemoveFromWindow);
}

AEntity::~AEntity()
{
    AUnregisterEventCallback(onRemoveFromWindow);
    AUnregisterEventCallback(onAddToWindow);
    AUnregisterEventCallback(onRemoveFromSpace);
    AUnregisterEventCallback(onAddToSpace);
}

AEventChannel &AEntity::getEventChannel()
{
    return eventChannel;
}

const AEventChannel &AEntity::getEventChannel() const
{
    return eventChannel;
}

const Math::Vector &AEntity::getPosition() const
{
    return this->transform.Position;
}

void AEntity::setPosition(const Math::Vector &position)
{
    this->transform.Position = position;
    hasCachedMatrix = false;
}

const Math::Quaternion &AEntity::getRotation() const
{
    return this->transform.Rotation;
}

void AEntity::setRotation(const Math::Quaternion &rotation)
{
    this->transform.Rotation = rotation;
    hasCachedMatrix = false;
}

const Math::Transform &AEntity::getTransform() const
{
    return this->transform;
}

void AEntity::setTransform(const Math::Transform &transform)
{
    this->transform = transform;
    hasCachedMatrix = false;
}

const Math::Matrix &AEntity::getMatrix() const
{
    bool hasCachedMatrix = false;
    if(!hasCachedMatrix)
    {
        cachedMatrix = this->transform.getMatrix();
        hasCachedMatrix = true;
    }
    return cachedMatrix;
}

ASpace *AEntity::getSpace() const
{
    return space;
}

AWindow *AEntity::getWindow() const
{
    return space ? space->getWindow() : nullptr;
}

const Array<::SharedReference<AComponent>> &AEntity::getComponents() const
{
    return components;
}

void AEntity::setComponents(const Array<::SharedReference<AComponent>> &components)
{
    if (isLoaded)
    {
        unloadComponents();
        this->components = components;
        loadComponents();
    }
    else
    {
        this->components = components;
    }
}

void AEntity::addComponent(const ::SharedReference<AComponent> &component)
{
    components.push_back(component);
    if (isLoaded)
    {
        ALoadEvent e(*this);
        component->sendEvent(e);
    }
}

void AEntity::insertComponent(size_t index, const ::SharedReference<AComponent> &component)
{
    ArrayUtils::Insert(components, index, component);
    if (isLoaded)
    {
        ALoadEvent e(*this);
        component->sendEvent(e);
    }
}

void AEntity::removeComponent(const ::SharedReference<AComponent> &component)
{
    for(auto it = components.begin(); it != components.end(); ++it)
    {
        if(*it == component)
        {
            if (isLoaded)
            {
                AUnloadEvent e(*this);
                component->sendEvent(e);
            }
            components.erase(it);
            break;
        }
    }
}

void AEntity::removeComponent(size_t index)
{
    auto it = components.begin() + index;
    if (isLoaded)
    {
        AUnloadEvent e(*this);
        (*it)->sendEvent(e);
    }
    components.erase(it);
}

void AEntity::onAddToSpace(AAddToSpaceEvent &event)
{
    this->space = &event.getSpace();
    this->space->eventChannel.registerObserver(*this);
    loadComponents();
    eventChannel.sendEvent(event);
}

void AEntity::onRemoveFromSpace(ARemoveFromSpaceEvent &event)
{
    eventChannel.sendEvent(event);
    unloadComponents();
    this->space->eventChannel.unregisterObserver(*this);
    this->space = nullptr;
}

void AEntity::onAddToWindow(AAddToWindowEvent &event)
{
    loadComponents();
}

void AEntity::onRemoveFromWindow(ARemoveFromWindowEvent &event)
{
    unloadComponents();
}

void AEntity::loadComponents()
{
    if (isLoaded)
    {
        return;
    }

    if (!getWindow())
    {
        return;
    }

    for (auto &component : getComponents())
    {
        ALoadEvent e(*this);
        component->sendEvent(e);
    }
    isLoaded = true;
}

void AEntity::unloadComponents()
{
    if (!isLoaded)
    {
        return;
    }

    for (auto &component : getComponents())
    {
        AUnloadEvent e(*this);
        component->sendEvent(e);
    }
    isLoaded = false;
}
