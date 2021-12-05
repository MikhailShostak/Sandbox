#pragma once

#include "Core/StateMachine.h"
#include "Core/Controllers/Controller.h"
#include "Core/Assets.h"

template<typename BundleType, size_t assetID>
class ControllerState : public AObject, public State
{
    ::SharedReference<Controller> controller = BundleType::getInstance().findObject<Controller>(assetID);
public:

    void onEnter(StateMachine &stateMachine) override
    {
        AAssert(controller, "Controller is not set");
        controller->onActivate();
    }

    void onExit(StateMachine &stateMachine) override
    {
        AAssert(controller, "Controller is not set");
        controller->onDeactivate();
    }
};
