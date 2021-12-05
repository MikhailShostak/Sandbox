#pragma once

#include "Core/AInputController.h"

class AConsoleController : public AInputController
{
    bool consoleEnbaled = false;
public:
    using AInputController::AInputController;

    void onKeyPress(AWindowKeyPressEvent &event) override
    {
        if (event.getKey() == '`')
        {
            toggleConsole();
            event.accept();
            return;
        }

        if (consoleEnbaled)
        {
            ALogMessage("", "%d", event.getKey());
            event.accept();
        }
    }

    void onKeyRelease(AWindowKeyReleaseEvent &event) override
    {

    }

    void toggleConsole()
    {
        consoleEnbaled = !consoleEnbaled;
    }
};