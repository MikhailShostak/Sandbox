#pragma once

#include <Foundation>
#include "Core/AEventLoop.h"
#include "Core/APlatformInegration.h"
#include "UI/UIComponent.h"

class UIApplication : public AApplication, public ARunnable
{
protected:
    AEventDispatcher eventDispatcher;
    AOperationDispatcher operationDispatcher;

    struct Storage : public ASingleton<Storage>
    {
        UIApplication *application = nullptr;
    };
public:
    using AApplication::AApplication;

    ADelegate<bool(const AError &error)> onClose;

    static UIApplication &getInstance()
    {
        UIApplication *instance = Storage::getInstance().application;
        AAssert(instance, "UI application isn't runned");
        return *instance;
    }

    static AEventDispatcher &getEventDispatcher() { return getInstance().eventDispatcher; }
    static AOperationDispatcher &getOperationDispatcher() { return getInstance().operationDispatcher; }

    ~UIApplication()
    {
        operationDispatcher.exit();
        operationDispatcher.join();
    }

    AError execute() override
    {
        auto &applicationInstance = Storage::getInstance().application;
        AAssert(!applicationInstance, "UI application is already runned");
        applicationInstance = this;

        //TODO: move to components
        ExecuteGlobalCalls();
        UI::Component::loadDefaultStyle();

        for (auto &c : components)
        {
            c->onApplicationStart(*this);
        }
        AError error = APlatformInstance().main(*this);
        for (auto& c : components)
        {
            c->onApplicationFinish(*this);
        }

        applicationInstance = nullptr;
        return error;
    }

    void onExecute() override
    {
        eventDispatcher.processEvents();
        operationDispatcher.executeMainThreadOperations();
    }

    void stop(const AError &error = AError::getEmptyError()) override
    {
        if (!onClose || onClose(error))
        {
            APlatformInstance().stop(error);
        }
    }
};
