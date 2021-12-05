//CLASSGEN GENERATED REGION: Dependencies
#pragma once
#include "Experimental"
#include "FileManager.gen.h"
#include "TaskManager.gen.h"
#include "WindowManager.gen.h"
#include "ApplicationManager.gen.h"
#include "WindowFlowState.h"
#include "Math"
#include "Foundation"
#include "MainView.gen.h"
#include "SettingsView.gen.h"
#include "NewFileView.gen.h"
#include "OpenFileView.gen.h"
#include "AboutView.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Declaration
class OneStudioFlow
{
static Array<SharedReference<FlowState>> states;
static void onMainWindowCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_126;
    backgroundColor_126.Red = 0.150000;
    backgroundColor_126.Green = 0.150000;
    backgroundColor_126.Blue = 0.150000;
    backgroundColor_126.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_126);
    (*instance).setTitle("Editor");
    Math::IntegerRectangle geometry_132;
    Math::IntegerVector position_133;
    position_133.X = 100.000000;
    position_133.Y = 100.000000;
    position_133.Z = 0.000000;
    position_133.W = 0.000000;
    geometry_132.Position = position_133;
    Math::IntegerVector size_138;
    size_138.X = 1800.000000;
    size_138.Y = 900.000000;
    size_138.Z = 0.000000;
    size_138.W = 0.000000;
    geometry_132.Size = size_138;
    (*instance).setGeometry(geometry_132);
    (*instance).setView(CreateShared<OneStudio::MainView>());
    (*instance).onClosed = [](){ UIApplication::getInstance().stop(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onMainWindowEnter()
{
    states.back()->onEnter();
}
static void onMainWindowExit()
{
    states.back()->onExit();
}
static void onMainWindowDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static void onSettingsWindowCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_145;
    backgroundColor_145.Red = 0.150000;
    backgroundColor_145.Green = 0.150000;
    backgroundColor_145.Blue = 0.150000;
    backgroundColor_145.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_145);
    (*instance).setTitle("Settings");
    Math::IntegerRectangle geometry_151;
    Math::IntegerVector position_152;
    position_152.X = 100.000000;
    position_152.Y = 100.000000;
    position_152.Z = 0.000000;
    position_152.W = 0.000000;
    geometry_151.Position = position_152;
    Math::IntegerVector size_157;
    size_157.X = 1800.000000;
    size_157.Y = 900.000000;
    size_157.Z = 0.000000;
    size_157.W = 0.000000;
    geometry_151.Size = size_157;
    (*instance).setGeometry(geometry_151);
    (*instance).setView(CreateShared<OneStudio::SettingsView>());
    (*instance).onClosed = [](){ sm.popState(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onSettingsWindowEnter()
{
    states.back()->onEnter();
}
static void onSettingsWindowExit()
{
    states.back()->onExit();
}
static void onSettingsWindowDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static void onNewFileDialogCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_164;
    backgroundColor_164.Red = 0.150000;
    backgroundColor_164.Green = 0.150000;
    backgroundColor_164.Blue = 0.150000;
    backgroundColor_164.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_164);
    (*instance).setTitle("New");
    Math::IntegerRectangle geometry_170;
    Math::IntegerVector position_171;
    position_171.X = 100.000000;
    position_171.Y = 100.000000;
    position_171.Z = 0.000000;
    position_171.W = 0.000000;
    geometry_170.Position = position_171;
    Math::IntegerVector size_176;
    size_176.X = 800.000000;
    size_176.Y = 480.000000;
    size_176.Z = 0.000000;
    size_176.W = 0.000000;
    geometry_170.Size = size_176;
    (*instance).setGeometry(geometry_170);
    (*instance).setView(CreateShared<OneStudio::NewFileView>());
    (*instance).onClosed = [](){ sm.popState(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onNewFileDialogEnter()
{
    states.back()->onEnter();
}
static void onNewFileDialogExit()
{
    states.back()->onExit();
}
static void onNewFileDialogDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static void onOpenFileDialogCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_183;
    backgroundColor_183.Red = 0.150000;
    backgroundColor_183.Green = 0.150000;
    backgroundColor_183.Blue = 0.150000;
    backgroundColor_183.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_183);
    (*instance).setTitle("Open");
    Math::IntegerRectangle geometry_189;
    Math::IntegerVector position_190;
    position_190.X = 100.000000;
    position_190.Y = 100.000000;
    position_190.Z = 0.000000;
    position_190.W = 0.000000;
    geometry_189.Position = position_190;
    Math::IntegerVector size_195;
    size_195.X = 800.000000;
    size_195.Y = 480.000000;
    size_195.Z = 0.000000;
    size_195.W = 0.000000;
    geometry_189.Size = size_195;
    (*instance).setGeometry(geometry_189);
    (*instance).setView(CreateShared<OneStudio::OpenFileView>());
    (*instance).onClosed = [](){ sm.popState(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onOpenFileDialogEnter()
{
    states.back()->onEnter();
}
static void onOpenFileDialogExit()
{
    states.back()->onExit();
}
static void onOpenFileDialogDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static void onAboutWindowCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_202;
    backgroundColor_202.Red = 0.150000;
    backgroundColor_202.Green = 0.150000;
    backgroundColor_202.Blue = 0.150000;
    backgroundColor_202.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_202);
    (*instance).setTitle("About");
    Math::IntegerRectangle geometry_208;
    Math::IntegerVector position_209;
    position_209.X = 0.000000;
    position_209.Y = 0.000000;
    position_209.Z = 0.000000;
    position_209.W = 0.000000;
    geometry_208.Position = position_209;
    Math::IntegerVector size_214;
    size_214.X = 0.000000;
    size_214.Y = 0.000000;
    size_214.Z = 0.000000;
    size_214.W = 0.000000;
    geometry_208.Size = size_214;
    (*instance).setGeometry(geometry_208);
    (*instance).setView(CreateShared<OneStudio::AboutView>());
    (*instance).onClosed = [](){ sm.popState(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onAboutWindowEnter()
{
    states.back()->onEnter();
}
static void onAboutWindowExit()
{
    states.back()->onExit();
}
static void onAboutWindowDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static void onUnsavedFilesCreate()
{
    SharedReference<UI::WindowFlowState> state = CreateShared<UI::WindowFlowState>();
    std::unique_ptr<UI::ViewWindow> instance{ Create<UI::ViewWindow>()};
    UI::Color backgroundColor_221;
    backgroundColor_221.Red = 0.150000;
    backgroundColor_221.Green = 0.150000;
    backgroundColor_221.Blue = 0.150000;
    backgroundColor_221.Alpha = 1.000000;
    (*instance).setBackgroundColor(backgroundColor_221);
    (*instance).setTitle("UnsavedFiles");
    Math::IntegerRectangle geometry_227;
    Math::IntegerVector position_228;
    position_228.X = 0.000000;
    position_228.Y = 0.000000;
    position_228.Z = 0.000000;
    position_228.W = 0.000000;
    geometry_227.Position = position_228;
    Math::IntegerVector size_233;
    size_233.X = 0.000000;
    size_233.Y = 0.000000;
    size_233.Z = 0.000000;
    size_233.W = 0.000000;
    geometry_227.Size = size_233;
    (*instance).setGeometry(geometry_227);
    (*instance).onClosed = [](){ sm.popState(); };
    state->setInstance(std::move(instance));
    state->onCreate();
    states.push_back(state);
}
static void onUnsavedFilesEnter()
{
    states.back()->onEnter();
}
static void onUnsavedFilesExit()
{
    states.back()->onExit();
}
static void onUnsavedFilesDestroy()
{
    states.back()->onDestroy();
    states.pop_back();
}
static constexpr StaticStackState StatesTable[] = { 
{ &OneStudioFlow::onMainWindowCreate, &OneStudioFlow::onMainWindowDestroy, &OneStudioFlow::onMainWindowEnter, &OneStudioFlow::onMainWindowExit },
{ &OneStudioFlow::onSettingsWindowCreate, &OneStudioFlow::onSettingsWindowDestroy, &OneStudioFlow::onSettingsWindowEnter, &OneStudioFlow::onSettingsWindowExit },
{ &OneStudioFlow::onNewFileDialogCreate, &OneStudioFlow::onNewFileDialogDestroy, &OneStudioFlow::onNewFileDialogEnter, &OneStudioFlow::onNewFileDialogExit },
{ &OneStudioFlow::onOpenFileDialogCreate, &OneStudioFlow::onOpenFileDialogDestroy, &OneStudioFlow::onOpenFileDialogEnter, &OneStudioFlow::onOpenFileDialogExit },
{ &OneStudioFlow::onAboutWindowCreate, &OneStudioFlow::onAboutWindowDestroy, &OneStudioFlow::onAboutWindowEnter, &OneStudioFlow::onAboutWindowExit },
{ &OneStudioFlow::onUnsavedFilesCreate, &OneStudioFlow::onUnsavedFilesDestroy, &OneStudioFlow::onUnsavedFilesEnter, &OneStudioFlow::onUnsavedFilesExit },
};
public:
    enum States
    {
        MainWindow,
        SettingsWindow,
        NewFileDialog,
        OpenFileDialog,
        AboutWindow,
        UnsavedFiles,
    };
    constexpr static const char *StateNames[] = { "MainWindow", "SettingsWindow", "NewFileDialog", "OpenFileDialog", "AboutWindow", "UnsavedFiles" };
    using StateMachineType = VariantStaticStackBasedStateMachine<OneStudioFlow::StatesTable, 6, OneStudioFlow::MainWindow, false>;
    static StateMachineType sm;
};
//CLASSGEN END REGION
