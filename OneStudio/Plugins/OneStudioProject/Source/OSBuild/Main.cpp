
#include <Network.h>
#include <OneStudioProjectLibrary>

class OSBuildProjectContext : public OSProjectContext
{

    AOperationDispatcher runLoop;

public:

    AOperationDispatcher &getOperationDispatcher() override
    {
        return runLoop;
    }

    void log(const String &text, const String &file = String(), const String &indication = String()) override
    {
        ALogMessage("Info", "%s%s%s", file, indication, text);
        std::cout.flush();
    }

    void error(const String &text, const String &file = String(), const String &indication = String()) override
    {
        ALogMessage("Error", "%s%s%s", file, indication, text);
        std::cout.flush();
    }

};

Map<String, String> commands;

void applyCommand(const String &command, const String &value)
{
    commands[command] = value;
}

Map<String, ADelegate<String(const String &)>> API;

class OSBuildParser : public Network::TCP::CommandParser
{
public:
    String HandleCommand(const String &command)
    {
        String result;

        auto it = API.find(command);
        if (it != API.end())
        {
            result = it->second(command);
        }
        else
        {
            result = "Undefined";
        }

        return result;
    }
};

void registerAPI()
{
    API["commands"] = [](const String &) {
        String result;

        for (const APair<String, String> &p : commands)
        {
            result += p.first;
            result += "=";
            result += p.second;
            result += "\n";
        }

        return result;
    };

    API["help"] = [](const String &name) {
        String result;

        for (const APair<String, ADelegate<String(const String &)>> &p : API)
        {
            result += p.first;
            result += "\n";
        }

        return result;
    };
}

int main(int argc, char *argv[])
{
    setbuf(stdout, nullptr);
    setbuf(stderr, nullptr);

    APath workingDirectory = APath::workingDirectory();
    commands.insert("--root", APath::applicationDirectory() + "..");
    commands.insert("--project", workingDirectory + APath(workingDirectory.baseName() + ".osproject"));
    commands.insert("--target", String());
    commands.insert("--configuration", String());
    commands.insert("--action", "Build");
    commands.insert("--port", String());

    for(int i = 1; i < argc; ++i)
    {
        auto argument = String(argv[i]);
        auto commandData = argument.split('=');

        switch(commandData.size())
        {
        case 1:
            applyCommand(commandData[0], String());
            break;
        case 2:
            applyCommand(commandData[0], commandData[1]);
            break;
        default:
            return -1;
        }
    }

    if (commands["--port"])
    {
        registerAPI();

        Network::TCP::Server<OSBuildParser> server(commands["--port"].toInt());

        Network::Manager::getInstance().Start([](auto &Context) {
            println("Server started");
        });

        ConsoleApplication app;
        app.execute();

        Network::Manager::getInstance().Stop([]() {
            println("Server stopped");
        });

        return 0;
    }
    
    SharedReference<OSProjectContext> projectContext = createNew<OSBuildProjectContext>();
    ProjectContext = projectContext.data();
    ProjectContext->load(commands.at("--root"));

    /*bool verbose = commands.has("--verbose");

    if (verbose)
    {
        ALogMessage("Info", "\r\nArguments:");
        for ()
        {
            ALogMessage("Info", "    %s = %s", command, value);
        }
        ALogMessage("Info", "");
    }*/

    SharedReference<OSProject> project = ProjectContext->loadProject(commands.at("--project"));
    if(!project)
    {
        ProjectContext->error(fmt::format("Couldn't load project at \"{}\"", commands.at("--project")));
        ProjectContext->getOperationDispatcher().exit();
        ProjectContext->getOperationDispatcher().join();
        return -2;
    }
    /*else
    {
        ProjectContext->log(fmt::format("[{}]\r\n", project->getName()));
    }*/

    AError resultError;
    auto completion = [&projectContext, &resultError](const AError &error){
        resultError = error;
        projectContext->getOperationDispatcher().exit();
    };

    auto &configurationName = commands.at("--configuration");
    StringHashMap<SharedReference<OSSettings>> configurationSettings;
    if (configurationName)
    {
        for (size_t i = 0; i < project->getCountConfigurations(); ++i)
        {
            if (project->getConfigurationName(i) == configurationName)
            {
                configurationSettings = project->getConfigurationSettings(i);
                break;
            }
        }
    }

    auto &targetName = commands.at("--target");
    auto &targetsData = project->getTargetData();
    if(commands.hasKey("--print") && targetsData.size() > 0)
    {
        ProjectContext->log("Targets:");
        for(auto &t : targetsData)
        {
            ProjectContext->log(fmt::format("**** {} ****", t.Name));
            SharedReference<OSProjectTargetDataInstance> target = project->findTarget(t.Name);
            static Array<String> steps{"Build", "Clean", "Install", "Uninstall", "Run"};
            for (auto &step : steps)
            {
                auto tasks = target->findTasks(step);
                if (tasks)
                {
                    ProjectContext->log(fmt::format("    {}", step));
                    std::sort(tasks.begin(), tasks.end(), [](auto &l, auto &r) { return l->getIndex() < r->getIndex(); });
                    for (const SharedReference<OSTaskDataObject> &taskInfo : tasks)
                    {
                        ProjectContext->log(fmt::format("        {} ({})", taskInfo->getDescription(), taskInfo->getPackage()));
                    }
                }
            }
        }
        ProjectContext->getOperationDispatcher().exit();
        ProjectContext->getOperationDispatcher().join();
        system("pause");
        return 0;
    }

    for(auto &targetData : targetsData)
    {
        if(targetName == targetData.Name)
        {
            auto &action = commands.at("--action");
            if(action == "build")
            {
                ProjectContext->build(TaskData{ project, targetData, { configurationName, configurationSettings } }, completion);
            }
            else if(action == "clean")
            {
                ProjectContext->clean(TaskData{ project, targetData, { configurationName, configurationSettings } }, completion);
            }
            else if(action == "install")
            {
                ProjectContext->install(TaskData{ project, targetData, { configurationName, configurationSettings } }, completion);
            }
            else if(action == "uninstall")
            {
                ProjectContext->uninstall(TaskData{ project, targetData, { configurationName, configurationSettings } }, completion);
            }
            else if(action == "run")
            {
                ProjectContext->run(TaskData{ project, targetData, { configurationName, configurationSettings } }, completion);
            }
        }
    }

    if(resultError)
    {
        ProjectContext->error(fmt::format("OSBuild completed with error: {}", resultError.getMessage()));
    }

    //TODO: Can we assert similar issues in the future?
    //The issue is in OSSettings which is loaded from plugins and stay locked by application after unloading
    configurationSettings.clear();

    ProjectContext->getOperationDispatcher().setExitAfterLastOperation(true);
    ProjectContext->getOperationDispatcher().join();
    project = nullptr;
    projectContext = nullptr;
    return resultError.getErrorCode();
}
