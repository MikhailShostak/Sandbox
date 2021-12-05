#pragma once

#include "Core/AComponent.h"
#include "Graphics/AGraphicsContext.h"

namespace Legacy::Graphics
{
class ARenderer; //TODO: remove
}

class AVisualComponent : public AComponent
{
    bool updateNeeded = true;
public:
    using This = AVisualComponent;
    using Super = AComponent;
    using AComponent::AComponent;
    bool shouldReceiveUpdates() const final override;
    bool isUpdateNeeded() const;
    void update();
protected:

    void onUpdate(AUpdateEvent &event) override;
    virtual void onDraw(AUpdateEvent &event) = 0;
};
