#include "AComponent.h"

#include "AEntity.h"
#include "AEntityEvents.h"
#include "ACommonEvents.h"
#include "ASpace.h"

//HACK
extern AOperationDispatcher &getOperationDispatcher();

AComponent::AComponent(AEntity &owner):
    owner(owner)
{
    ARegisterEventCallback(onLoad);
    ARegisterEventCallback(onUnload);
}

AComponent::~AComponent()
{
    AUnregisterEventCallback(onUnload);
    AUnregisterEventCallback(onLoad);
}

AEntity &AComponent::getOwner() const
{
    return owner;
}

ASpace *AComponent::getSpace() const
{
    return getOwner().getSpace();
}

AWindow *AComponent::getWindow() const
{
    return getOwner().getWindow();
}

void AComponent::onLoad(ALoadEvent &event)
{
    registerForUpdates();
}

void AComponent::onUnload(AUnloadEvent &event)
{
    unregisterForUpdates();
}

void AComponent::registerForUpdates()
{
    if (shouldReceiveUpdates())
    {
        getOperationDispatcher().addDelegate([this]() {
            ARegisterEventCallback(onUpdate);
            getSpace()->eventChannel.registerObserver(*this);
            return AError::getEmptyError();
        }, true);
    }
}

void AComponent::unregisterForUpdates()
{
    if (shouldReceiveUpdates())
    {
        getOperationDispatcher().addDelegate([this]() {
            getSpace()->eventChannel.unregisterObserver(*this);
            AUnregisterEventCallback(onUpdate);
            return AError::getEmptyError();
        }, true);
    }
}

bool AComponent::shouldReceiveUpdates() const
{
    return false;
}

void AComponent::onUpdate(AUpdateEvent &event)
{

}
