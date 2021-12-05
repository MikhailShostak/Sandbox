//CLASSGEN GENERATED REGION: Includes
#include <Experimental>
#include <AssetManager.gen.h>
#include <Graphics>
#include <Foundation>
#include <Math>
#include <OneStudioMainWindow.gen.h>
#include <MainView.gen.h>
#include <MathClasses>
#include <ExperimentalDebug>
#include <UI2>
#include <WindowManager.gen.h>
#include <WindowLayout.gen.h>
#include <FileManager.gen.h>
#include <WorkspaceData.gen.h>
#include <TaskManager.gen.h>
#include <ApplicationManager.gen.h>
#include <DeveloperLibrary.gen.h>

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Implementation
namespace OneStudio{
inline DynamicAsset<Core::Application2> OneStudioApp_Asset = DynamicAsset<Core::Application2>("OneStudio.OneStudioApp", [](auto &asset){
GraphicsComponent* item_14_0 = Create<GraphicsComponent>();
LaunchComponent* item_15_1 = Create<LaunchComponent>();
(*item_15_1).setWindows({OneStudio::OneStudioMainWindow_Asset.load(),});
UIComponent* item_18_2 = Create<UIComponent>();
OneStudio::MainView* mainView_19 = Create<OneStudio::MainView>();
(*mainView_19).setVerticalSizePolicy(UI::SizePolicy::Expanded);
(*item_18_2).setMainView(mainView_19);
UI::LegacyApplication* item_21_3 = Create<UI::LegacyApplication>();
OneStudio::FileManager* item_22_4 = Create<OneStudio::FileManager>();
OneStudio::TaskManager* item_23_5 = Create<OneStudio::TaskManager>();
OneStudio::WindowManager* item_24_6 = Create<OneStudio::WindowManager>();
OneStudio::ApplicationManager* item_25_7 = Create<OneStudio::ApplicationManager>();
asset.setComponents({item_14_0,item_15_1,item_18_2,item_21_3,item_22_4,item_23_5,item_24_6,item_25_7,});
});
}
//CLASSGEN END REGION
