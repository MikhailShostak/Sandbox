#pragma once

#include <OSTaskPlugin.h>

class OSCTargetTask final : public OSTargetTask
{

public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.CLanguage";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {List, "ProductType:Application,Static Library,Shared Library"}
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override;

};
