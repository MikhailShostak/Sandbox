#include "AVisualComponent.h"
#include "AWindow.h"

bool AVisualComponent::shouldReceiveUpdates() const
{
    return true;
}

bool AVisualComponent::isUpdateNeeded() const
{
    return updateNeeded;
}

void AVisualComponent::update()
{
    updateNeeded = true;
}

void AVisualComponent::onUpdate(AUpdateEvent &event)
{
    if(updateNeeded)
    {
        updateNeeded = false;
        onDraw(event);
    }
}
