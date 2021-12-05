//CLASSGEN GENERATED REGION: Dependencies
#include "OneStudioFlow.gen.h"
#include "FileManager.gen.h"
#include "TaskManager.gen.h"
#include "WindowManager.gen.h"
#include "ApplicationManager.gen.h"

//CLASSGEN END REGION
#if 0
Array<SharedReference<FlowState>> OneStudioFlow::states;
OneStudioFlow::StateMachineType OneStudioFlow::sm;
#include "OneStudioApp.gen.h"
int main(int argv, const char *argc[])
{
    return OneStudio::OneStudioApp_Asset.load()->execute();
}
#else
//CLASSGEN GENERATED REGION: Implementation
Array<SharedReference<FlowState>> OneStudioFlow::states;
OneStudioFlow::StateMachineType OneStudioFlow::sm;
int main(int argv, const char *argc[])
{
    UIApplication application;
    application.components = {
        CreateShared<FlowApplicationComponent<OneStudioFlow>>(),
        CreateShared<OneStudio::FileManager>(),
        CreateShared<OneStudio::TaskManager>(),
        CreateShared<OneStudio::WindowManager>(),
        CreateShared<OneStudio::ApplicationManager>(),
    };
    return application.execute().getErrorCode();
}
//CLASSGEN END REGION
#endif
