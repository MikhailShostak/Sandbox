//CLASSGEN GENERATED REGION: Includes
#include "ApplicationManager.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "FileManager.gen.h"
#include "SettingsEntry.gen.h"
#include "ExtensionsView.gen.h"
#include "DeveloperLibraryView.gen.h"
#include "ToolbarSettingsView.gen.h"
#include "TypesView.gen.h"
#include "EditableFile.gen.h"

#include "TasksProgressView.gen.h"

#include "OneStudioFlow.gen.h"

#include "EnvironmentVariablesView.gen.h"

Math::IntegerVector getDesktopSize()
{
    return Math::IntegerVector{ 1920, 1080 };
}

#include "Task.gen.h"
#include "TasksWidget.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationManager::ApplicationManager()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationManager::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationManager::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<OneStudio::SettingsEntry> ApplicationManager::getEntries() const
{
    return this->Entries;
}
void ApplicationManager::setEntries(Array<OneStudio::SettingsEntry> const &Entries)
{
    this->Entries = Entries;
}
void ApplicationManager::setEntries(Array<OneStudio::SettingsEntry> &&Entries)
{
    this->Entries = std::move(Entries);
}
OneStudio::DeveloperLibrary ApplicationManager::getDeveloperLibrary() const
{
    return this->DeveloperLibrary;
}
void ApplicationManager::setDeveloperLibrary(OneStudio::DeveloperLibrary const &DeveloperLibrary)
{
    this->DeveloperLibrary = DeveloperLibrary;
}
void ApplicationManager::setDeveloperLibrary(OneStudio::DeveloperLibrary &&DeveloperLibrary)
{
    this->DeveloperLibrary = std::move(DeveloperLibrary);
}
//CLASSGEN END REGION

void ApplicationManager::loadDeveloperLibrary()
{
    if(!this->DeveloperLibrary.getLibraryPath().size())
    {
#if ADebugBuild
        this->DeveloperLibrary.setLibraryPath(APath::getUserDirectory() + "DeveloperDebug/Library");
#else
        this->DeveloperLibrary.setLibraryPath(APath::getUserDirectory() + "Developer/Library");
#endif
    }
    
    this->DeveloperLibrary.load();
}

void ApplicationManager::load()
{
    FileManager::getThisInstance().loadWorkspace();
    WindowManager::getThisInstance().loadWindowLayout();
    WindowManager::getThisInstance().loadShortcuts();
}

void ApplicationManager::save()
{
    WindowManager::getThisInstance().saveShortcuts();
    WindowManager::getThisInstance().saveWindowLayout();
    FileManager::getThisInstance().saveWorkspace();
}

static Map<String, Array<SharedReference<OSFileSystemItem>>> libraryFileItems;


void ApplicationManager::loadConsole(OneStudio::Task &task)
{
    Console::getInstance().addCommand("ShowApplication", [this](const Array<String>& arguments) {
        system(String("explorer /select," + APath::applicationPath().toString()).data()); //TODO: do not use system
    });
    Console::getInstance().addCommand("ShowUserDirectory", [this](const Array<String>& arguments) {
        system(String("explorer " + APath::getUserDirectory().toString()).data()); //TODO: do not use system
    });
    Console::getInstance().addCommand("ShowWorkingDirectory", [this](const Array<String>& arguments) {
        system(String("explorer " + APath::workingDirectory().toString()).data()); //TODO: do not use system
    });
    Console::getInstance().addCommand("ShowLibrary", [this](const Array<String> &arguments) {
        system(String("explorer " + OneStudio::ApplicationManager::getThisInstance().getDeveloperLibrary().getLibraryPath().toString()).data()); //TODO: do not use system
    });
    Console::getInstance().addCommand("LoadExtension", [this](const Array<String> &arguments) {
        loadExtension(arguments[0]);
    });
    Console::getInstance().addCommand("UnloadExtension", [this](const Array<String> &arguments) {
        unloadExtension(arguments[0]);
    });
    /*Console::getInstance().addCommand("ToggleTasksProgress", [this](const Array<String>& arguments) {
        OneStudio::TaskManager::getInstance().window->setVisible(!OneStudio::TaskManager::getInstance().window->getVisible());
    });*/
    
    Console::getInstance().addCommand("SaveSettings", [](const Array<String>& arguments) {
        OneStudio::ApplicationManager::getThisInstance().save();
    });
    //co_return;
}

void ApplicationManager::loadSettings(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    OneStudio::ApplicationManager::getThisInstance().setEntries({
        OneStudio::SettingsEntry{ "Developer Library", CreateShared<OneStudio::DeveloperLibraryView>() },
        OneStudio::SettingsEntry{ "Extensions", CreateShared<OneStudio::ExtensionsView>() },
        OneStudio::SettingsEntry{ "Toolbar", CreateShared<OneStudio::ToolbarSettingsView>() },
        OneStudio::SettingsEntry{ "Types", CreateShared<OneStudio::TypesView>() },
        OneStudio::SettingsEntry{ "Environment Variables", CreateShared<OneStudio::EnvironmentVariablesView>() },
    });
    return;
}

void ApplicationManager::loadToolbar(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    SharedReference<UI::TextButton> newFileButton = CreateShared<UI::TextButton>();
    newFileButton->setText("New File");
    newFileButton->eventChannel.registerDelegate([this](UI::TapGestureEvent& event) {
        OneStudioFlow::sm.pushState(OneStudioFlow::NewFileDialog);
    });

    SharedReference<UI::TextButton> openFileButton = CreateShared<UI::TextButton>();
    openFileButton->setText("Open File");
    openFileButton->eventChannel.registerDelegate([this](UI::TapGestureEvent& event) {
        OneStudioFlow::sm.pushState(OneStudioFlow::OpenFileDialog);
    });

    SharedReference<UI::TextButton> settingsButton = CreateShared<UI::TextButton>();
    settingsButton->setText("Settings");
    settingsButton->eventChannel.registerDelegate([this](UI::TapGestureEvent& event) {
        OneStudioFlow::sm.pushState(OneStudioFlow::SettingsWindow);
    });

    SharedReference<UI::TextButton> aboutButton = CreateShared<UI::TextButton>();
    aboutButton->setText("About");
    aboutButton->eventChannel.registerDelegate([this](UI::TapGestureEvent& event) {
        OneStudioFlow::sm.pushState(OneStudioFlow::AboutWindow);
    });

   // co_await TaskManager::getThisInstance().getMainWorker().schedule();
    //Task::taskmanager.AsyncWorkers.schedule();
    OneStudio::WindowManager::getThisInstance().setAvailableToolbarCommands({
        OneStudio::ToolbarItem{ "NewFile", newFileButton },
        OneStudio::ToolbarItem{ "OpenFile", openFileButton },
        OneStudio::ToolbarItem{ "Settings", settingsButton },
        OneStudio::ToolbarItem{ "About", aboutButton },
    });

    //registerToolBarItem("ToggleTasksProgress", nullptr);
    //co_return;
}

void ApplicationManager::loadExtensions(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    ;
    this->DeveloperLibrary.pluginLibrary.setDirectory(APath::workingDirectory() + "LegacyExtensions");
    //this->DeveloperLibrary.pluginLibrary.setDirectory("D:/Projects/Toolchain/Extensions");
    loadDeveloperLibrary();
    //co_return;
}
void ApplicationManager::loadMIMETypes(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    OneStudio::FileManager::getThisInstance().setTypes({
        OneStudio::TypeData{ "application/octet-stream", {}, "BinaryEditor" },
        OneStudio::TypeData{ "image/gif", { "gif" }, "ImageEditor" },
        OneStudio::TypeData{ "image/jpeg", { "jpeg", "jpg" }, "ImageEditor" },
        OneStudio::TypeData{ "image/pjpeg", { "pjpeg", "pjpg" }, "ImageEditor" },
        OneStudio::TypeData{ "image/png", { "png" }, "ImageEditor" },
        OneStudio::TypeData{ "text/plain", { "txt", "log" }, "TextEditor" },
        OneStudio::TypeData{ "text/x-c++hdr", { "h", "hpp", "inl" }, "TextEditor" },
        OneStudio::TypeData{ "text/x-c++src", { "cpp", "c" }, "TextEditor" },
        OneStudio::TypeData{ "text/java", { "java" }, "TextEditor" },
        OneStudio::TypeData{ "text/csharp", { "cs" }, "TextEditor" },
        OneStudio::TypeData{ "text/make", { "makefile" }, "TextEditor" },
        OneStudio::TypeData{ "text/cmake", { "cmake" }, "TextEditor" },
        OneStudio::TypeData{ "text/qt", { "pro", "pri" }, "TextEditor" },
        OneStudio::TypeData{ "text/python", { "py", "pyw" }, "TextEditor" },
        OneStudio::TypeData{ "text/ruby", { "rb" }, "TextEditor" },
        OneStudio::TypeData{ "text/bash", { "sh" }, "TextEditor" },
        OneStudio::TypeData{ "text/batch", { "bat" }, "TextEditor" },
        OneStudio::TypeData{ "text/plist", { "plist" }, "TextEditor" },
        OneStudio::TypeData{ "text/shader", { "vsh", "fsh", "gsh", "csh" }, "TextEditor" },
        OneStudio::TypeData{ "text/xml", { "xml" }, "XMLEditor" },
        OneStudio::TypeData{ "application/xml", { "xml" }, "XMLEditor" },
        OneStudio::TypeData{ "application/json", { "json" }, "JSONEditor" },
        OneStudio::TypeData{ "application/vnd.one-studio.project", { "osproject" }, "Editor" },
        OneStudio::TypeData{ "application/vnd.one-studio.class", { "cg" }, "ClassEditor" }
    });
    //OneStudio::ApplicationManager::getThisInstance().onTypesUpdated();
    //co_return;
}

void ApplicationManager::loadWorkspace(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    OneStudio::ApplicationManager::getThisInstance().load();
    //co_return;
}

void ApplicationManager::indexLibrary(OneStudio::Task &task)
{
    task.log.push_back(getLibraryDirectory().toUnixPathString());
    //co_await TaskManager::getThisInstance().getAsyncWorkers().schedule();
    ADirectory libraryDirectory(getLibraryDirectory());
    if (libraryDirectory.isExists())
    {
        auto entries = libraryDirectory.find(AFindFilter::AllDirectories);
        for (const APathInfo& libraryEntry : entries)
        {
            APathInfo libraryRoot(libraryEntry.path() + "CurrentVersion/Content");
            task.log.push_back(Str::Format("Indexing library {}", libraryEntry.name()));
            if (!libraryRoot.isExists())
            {
                task.log.push_back(Str::Format("    Warning: Library {} doesn't have a current version or content", libraryEntry.name()));
                continue;
            }

            auto libraryFiles = ADirectory(libraryRoot).findRecursively(AFindFilter::AllFiles);
            Array<SharedReference<OSFileSystemItem>> items;
            for (const APathInfo& libraryFile : libraryFiles)
            {
                task.log.push_back(Str::Format("    {}", libraryFile.path()));
                SharedReference<OSFileSystemItem> item = CreateShared<OSFileSystemItem>();
                item->setPath(libraryFile.path());
                FileManager::getThisInstance().indexFileInEditor(item);
                items.push_back(item);
            }
            libraryFileItems[libraryEntry.name()] = items;
        }
    }
    //co_return;
}

void ApplicationManager::printConsoleCommands(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    task.log.push_back("Registered commands");
    auto commands = Console::getInstance().getCommands();
    for (const auto& command : commands)
    {
        task.log.push_back(command.first);
    }
    //co_return;
}

void ApplicationManager::applyConsoleCommands(OneStudio::Task &task)
{
    //co_await TaskManager::getThisInstance().getMainWorker().schedule();
    AFile file;
    if (file.open(APath::applicationDirectory() + "Commands.txt", AFileOpenMode::ReadBinary))
    {
        while (!file.atEnd())
        {
            auto l = file.readLine();
            String line(l.begin(), l.end());
            if (line.empty() || line[0] == '#')
            {
                continue;
            }
            //TODO: remove
            boost::replace_all(line, "\r", "");
            boost::replace_all(line, "\n", "");
            task.log.push_back(line);
            Console::getInstance().applyCommand(line);
        }
    }
    //co_return;
}

void ApplicationManager::onApplicationStart(AApplication const& application)
{
    onLoad();
}

void ApplicationManager::onLoad()
{
    static bool run = false;
    if(!run)
    {
        run = true;
        static std::function<AError()> eventloop = [](){
            //TaskManager::getThisInstance().getMainWorker().service.process_pending_events();
            UIApplication::getInstance().getOperationDispatcher().addDelegate([](){
                UIApplication::getInstance().getOperationDispatcher().addDelegate(eventloop, true);
                return AError();
            });
            return AError();
        };
        UIApplication::getInstance().getOperationDispatcher().addDelegate(eventloop, true);
    }

    static SharedReference<OneStudio::Task> task = StaticCast<OneStudio::Task>(OneStudio::TaskManager::getInstance().startTask());
    task->setTitle("One Studio Initialization");
    task->action = [](OneStudio::Task &task) -> void { task.log.push_back(Str::Format("Init!")); };

    using P = std::pair<String, void(ApplicationManager::*)(OneStudio::Task &)>;
    std::vector<P> tasks = {
        P{ "Load Console", &ApplicationManager::loadConsole },
        P{ "Load Settings", &ApplicationManager::loadSettings },
        P{ "Load Toolbar", &ApplicationManager::loadToolbar },
        P{ "Load Extensions", &ApplicationManager::loadExtensions },
        P{ "Load MIME-Types", &ApplicationManager::loadMIMETypes },
        P{ "Load Workspace", &ApplicationManager::loadWorkspace },
        P{ "Index Library", &ApplicationManager::indexLibrary },
        P{ "Print All Console Commands", &ApplicationManager::printConsoleCommands },
        P{ "Apply Console Commands From File", &ApplicationManager::applyConsoleCommands },
    };
    for(auto &p : tasks)
    {
        SharedReference<OneStudio::Task> subtask = StaticCast<OneStudio::Task>(task->createSubTask());
        subtask->setTitle(p.first);
        subtask->action = [this, p](OneStudio::Task &task)
        {
            (this->*p.second)(task);
        };
    }

    task->start();
}

void ApplicationManager::onApplicationFinish(AApplication const &application)
{
    onUnload();
}

void ApplicationManager::onUnload()
{
    FileManager::getThisInstance().saveWorkspace();

    FileManager::getThisInstance().closeFiles();
    FileManager::getThisInstance().unregisterEditors();

    WindowManager::getThisInstance().unregisterToolbarCommands();
    WindowManager::getThisInstance().unregisterWindows();

    Console::getInstance().removeCommands();

    for (auto &plugin : plugins)
    {
        plugin->unload();
    }
    plugins.clear();

    getDeveloperLibrary().unload();
}

void ApplicationManager::loadExtension(const Path &path)
{
    /*SharedReference<AApplicationPlugin<OSPlugin>> p = createNew<AApplicationPlugin<OSPlugin>>();
    p->setPath(path);
    if (p->load())
    {
        auto instance = p->getInstance();
        for (auto &dependence : instance->getDependencies())
        {
            auto &systemPlugins = getDeveloperLibrary().pluginLibrary.getPlugins();
            auto dependentPlugin = systemPlugins.find([&dependence](const SharedReference<PluginType> &item) {
                return item->getPackage() == dependence.first;
            });

            static const char *FormatString = "Couldn't load plugin with package = \"{}\", because dependent plugin with package = \"{}\" {}";
            static const char *NotFoundReson = "not found";
            static const char *NoContextReson = "has no public context";

            if (dependentPlugin == plugins.end())
            {
                return;// AError(1, fmt::format(FormatString, plugin->getPackage(), dependence.first, NotFoundReson));
            }

            auto context = (*dependentPlugin)->getInstance()->getContext();
            if (!context)
            {
                return;// AError(2, fmt::format(FormatString, plugin->getPackage(), dependence.first, NoContextReson));
            }
        }
        instance->load({});
        plugins.append(p);
    }*/
}

void ApplicationManager::unloadExtension(const String &package)
{

}

bool ApplicationManager::registerCommand(const String& command, const std::function<void(const Array<String> & arguments)>& callback)
{
    Console::getInstance().addCommand(command, callback);
    return true;
}

bool ApplicationManager::registerOutliner(const SharedReference<OSOutliner>& outliner) { return true; }
bool ApplicationManager::registerControlVersionSystem(const SharedReference<OSControlVersionSystem>& cvs) { return true; }
bool ApplicationManager::registerToolBarItem(const String& identifier, SharedReference<UI::View> const& view)
{
    if (view == nullptr)
    {
        SharedReference<UI::TextButton> button = CreateShared<UI::TextButton>();
        button->setText(identifier);
        button->eventChannel.registerDelegate([identifier](const UI::TapGestureEvent& event) { Console::getInstance().applyCommand(identifier); });
        OneStudio::WindowManager::getThisInstance().registerToolbarCommand(OneStudio::ToolbarItem{ identifier, button });
    }
    else
    {
        OneStudio::WindowManager::getThisInstance().registerToolbarCommand(OneStudio::ToolbarItem{ identifier, view });
    }
    return true;
}
bool ApplicationManager::registerWindow(const String& identifier, SharedReference<UI::View> const& view)
{
    OneStudio::WindowManager::getThisInstance().registerWindow(identifier, view);
    return true;
}

void ApplicationManager::showProperties(UI::View* view) {}

void ApplicationManager::print(const String& text) {}
void ApplicationManager::log(const String& text, const String& file, const String& indication) {}
void ApplicationManager::warning(const String& text, const String& file, const String& indication) {}
void ApplicationManager::error(const String& text, const String& file, const String& indication) {}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
