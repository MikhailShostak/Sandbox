#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "EnvironmentVariablesGroupView.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class EnvironmentVariablesView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EnvironmentVariablesView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    EnvironmentVariablesView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<OneStudio::EnvironmentVariablesGroupView> systemVariables;
    void onHierarchyCreate();
//CLASSGEN END REGION

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        LPVOID lpvEnv = GetEnvironmentStrings();
        LPTSTR lpszVariable;
        for (lpszVariable = (LPTSTR)lpvEnv; *lpszVariable; ++lpszVariable)
        {

            String str((char *)lpszVariable);
            ALogMessage("", "%s", str);
            Array<String> data;
            boost::split(data, str, boost::is_any_of("="));
            systemVariables->variables.push_back({ data[0], data[1] });

            while (*(++lpszVariable));
        }

        FreeEnvironmentStrings((LPTSTR)lpvEnv);

        systemVariables->list->notifyUpdateAllItems();
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
