#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
#include "Includes/OSPlugin.gen.h"
#include "Includes/Outliner.gen.h"

template<typename OutlinerViewType>
class OSOutlinerPlugin : public OSPlugin
{

    SharedReference<OutlinerViewType> outlinerView;

public:

    static_assert(std::is_base_of<OSOutliner, OutlinerViewType>::value, "OutlinerViewType should be type of OSOutliner");

    void load(const Map<String, OSPluginContext *> &dependentPlugins) override
    {
        outlinerView = CreateShared<OutlinerViewType>();
        //context->registerOutliner(outlinerView);
    }

    void unload() override
    {

    }

};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
