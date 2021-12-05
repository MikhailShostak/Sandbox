#pragma once

#include <UI>
#include <Graphics>

namespace UI
{

class LegacyApplication : public Core::ApplicationComponent2, public UIApplication
{
public:
    void onLoad() override
    {
        Storage::getInstance().application = this;
    }

    void onUpdate() override
    {
        onExecute();
    }

    void onUnload() override
    {
        Storage::getInstance().application = nullptr;
    }
};

}
