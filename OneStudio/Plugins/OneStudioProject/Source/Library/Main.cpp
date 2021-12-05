#include <Foundation>

#include <iomanip>

#include "OSTargetTask.h"
#include "OSTaskPlugin.h"
#include "Main.h"

#include "OSBuildingOperation.h"

#include "OSProjectTargetInfoDataObject.inl"

#include "Classes.h"

const char *OSProjectPluginPackage = "com.InsaneTeam.OneStudio.Project";
const char *OSProjectPluginVersion = "1.0.0";

OSProjectContext *ProjectContext = nullptr;

Array<APair<OSTargetTask::PropertyType, String>> FilterVariables = {
    {OSTargetTask::String, "FilterDirectory"},
    {OSTargetTask::String, "FilterExtension"},
    {OSTargetTask::String, "OutputFile"},
};

enum FilterVariable
{
    FilterDirectory,
    FilterExtension,
    OutputFile,
};

AError copy(const APath &source, const APath &destination)
{
    APathInfo sourceInfo(source);
    if (sourceInfo.isFile() || sourceInfo.isSymbolicLink())
    {
        ProjectContext->log(fmt::format("Copy: {} to {}", source, destination));
        return sourceInfo.copy(destination) ? AError() : AError(2, fmt::format("Couldn't copy {} to {}. Check access to the destination path", source, destination));
    }
    else if (sourceInfo.isDirectory())
    {
        APathInfo destinationInfo(destination);
        if (destinationInfo.isExists() && !destinationInfo.isDirectory())
        {
            return AError(1, fmt::format("Couldn't copy {} to {}. Destination path already exists and it's no a directory", source, destination));
        }

        if (!destinationInfo.isExists())
        {
            ProjectContext->log(fmt::format("Create directory: {}", destinationInfo.path()));
            if (!destinationInfo.make())
            {
                return AError(1, fmt::format("Couldn't copy {} to {}. Check access to the destination path", source, destination));
            }
        }

        Array<APath> paths = ADirectory(sourceInfo).findRelativeRecursively(AFindFilter::All);
        for (auto &path : paths)
        {
            APathInfo sourcePathInfo(source + path);
            if (sourcePathInfo.isFile())
            {
                ProjectContext->log(fmt::format("Copy: {} to {}", sourcePathInfo.path(), destination + path));
                if (!sourcePathInfo.copy(destination + path))
                {
                    return AError(1, fmt::format("Couldn't copy {} to {}. Check access to the destination path", source, destination));
                }
            }
            else if (sourcePathInfo.isDirectory())
            {
                ProjectContext->log(fmt::format("Create directory: {}", destination + path));
                if (!APathInfo(destination + path).make())
                {
                    return AError(1, fmt::format("Couldn't copy {} to {}. Couldn't create directory {}. Check access to the destination path", source, destination, destination + path));
                }
            }
        }
    }

    return AError::getEmptyError();
}

AError removeOrMoveToTemp(APathInfo &sourceInfo)
{
    if (sourceInfo.isExists())
    {
        ProjectContext->log(fmt::format("Remove: {}", sourceInfo.path()));
        auto error = sourceInfo.remove() ? AError() : AError(2, "Couldn't remove");
        if (error)
        {
            APathInfo tempFile = APath("C:\\Temp\\") + sourceInfo.path().name();
            if (tempFile.isExists())
            {
                if (!tempFile.remove())
                {
                    return AError(2, fmt::format("Couldn't remove {}. Temporary file {} already exists and can't be removed for using deferred removing", sourceInfo.path()));
                }
            }

            ProjectContext->log(fmt::format("Moved: {} to {} because it can't be removed. Temporary file will be removed later", sourceInfo.path(), tempFile.path()));
            sourceInfo.rename(tempFile.path());
        }
    }

    return AError();
}

AError remove(const APath &source)
{
    APathInfo sourceInfo(source);
    if (sourceInfo.isDirectory())
    {
        Array<APath> paths = ADirectory(sourceInfo).findRelativeRecursively(AFindFilter::All);
        for (auto it = paths.rbegin(); it != paths.rend(); ++it)
        {
            APathInfo sourcePathInfo(source + *it);
            ProjectContext->log(fmt::format("Remove: {}", sourcePathInfo.path()));
            if (!sourcePathInfo.remove())
            {
                return AError(1, fmt::format("Couldn't remove {}", sourcePathInfo.path()));
            }
        }
    }

    return removeOrMoveToTemp(sourceInfo);
}

template<typename Predicate>
AError executeWithFilter(const OSBuildingContextData &data, const ADelegate<AError(const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values)> &callback, Predicate predicate)
{
    auto buildingSettings = data.getBuildTaskSettings();

    if(!(data.values.size() >= FilterVariables.size() && data.values[FilterDirectory] && data.values[FilterExtension]))
    {
        return callback(buildingSettings, StringsHashMap::EmptyHashMap());
    }

    APathInfo filterDirectory(OSTargetTask::resolveVariables(buildingSettings, data.values[FilterDirectory]));
    String filterExtension = OSTargetTask::resolveVariables(buildingSettings, data.values[FilterExtension]);

    if(filterDirectory.isDirectory())
    {
        Array<APathInfo> pathInfos = ADirectory(filterDirectory).findRecursively(filterExtension, AFindFilter::AllFiles);
        for(const APathInfo &pathInfo : pathInfos)
        {
            StringsHashMap values = {
                {"FileBaseName", pathInfo.path().baseName()},
                {"FileName", pathInfo.path().name()},
                {"FileExtension", pathInfo.path().extension()},
                {"FilePath", pathInfo.path()},
            };
            bool needToBuild = true;
            if(data.values[OutputFile])
            {
                String outputFile = OSTargetTask::resolveVariables(buildingSettings, data.values[OutputFile], values);
                values.insert({ "OutputFile", outputFile });
                APathInfo outputFilePathInfo(outputFile);
                APathInfo directory(outputFilePathInfo.path().directory());
                if(directory.isDirectory())
                {
                    needToBuild = predicate(buildingSettings, values, pathInfo, outputFilePathInfo);
                    if (!needToBuild)
                    {
                        ProjectContext->log(fmt::format("Skip: {}", outputFilePathInfo.path()));
                    }
                }
                else if(!directory.isExists())
                {
                    ProjectContext->log(fmt::format("Create: {}", directory.path()));
                    if (directory.make())
                    {
                        return AError(1, fmt::format("Couldn't create directory: {}", directory.path()));
                    }
                }
            }

            if(needToBuild)
            {
                AError error = callback(buildingSettings, values);
                if(error)
                {
                    return error;
                }
            }
        }
    }

    return AError::getEmptyError();
}

AError executeWithFilter(const OSBuildingContextData &data, const ADelegate<AError(const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values)> &callback)
{
    return executeWithFilter(data, callback, [](const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values, const APathInfo &inputFilePathInfo, const APathInfo &outputFilePathInfo) {
        return inputFilePathInfo.modificationTime() > outputFilePathInfo.modificationTime();
    });
}

class OSRemoveBuildDirectoryTask final : public OSTargetTask
{
public:

    String getPackage() const override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.RemoveBuildingDirectory";  }
    String getVersion() const override { return "1.0.0"; }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        /*auto error = remove(data.targetData->getIntermediateDirectory());
        if (error)
        {
            ProjectContext->log(fmt::format("Warning: {}", error.getMessage()));
        }*/
        completion(AError());
    }

};

class OSRemoveProductDirectoryTask final : public OSTargetTask
{
public:

    String getPackage() const override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.RemoveProductDirectory";  }
    String getVersion() const override { return "1.0.0"; }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        /*auto error = remove(data.targetInfo->getProductDirectory());
        if (error)
        {
            ProjectContext->log(fmt::format("Warning: {}", error.getMessage()));
        }*/
        completion(AError());
    }

};

class OSRemoveTargetTask final : public OSTargetTask
{
public:

    String getPackage() const override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.Remove";  }
    String getVersion() const override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const override
    {
        return {
            {Path, "Path"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto error = remove(data.values[0]);
        if (error)
        {
            ProjectContext->log(fmt::format("Warning: {}", error.getMessage()));
        }
        completion(AError());
    }

};

class OSMoveTargetTask final : public OSTargetTask
{
public:

    String getPackage() const override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.Move";  }
    String getVersion() const override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const override
    {
        return {
            {Path, "Source path"},
            {Path, "Destination path"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty() || data.values[1].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto buildingSettings = data.getBuildTaskSettings();
        APath sourcePath = data.values[0];
        APath destinationPath = data.values[1];

        ProjectContext->log(fmt::format("Move: {} {}", sourcePath.toString(), destinationPath.toString()));
        auto error = APathInfo(sourcePath).rename(destinationPath) ? AError::getEmptyError() : AError(2, "Couldn't rename");
        if (error)
        {
            ProjectContext->log(fmt::format("Warning: {}", error.getMessage()));
        }
        completion(AError());
    }

};

class OSCopyTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.Copy";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {Path, "Source path"},
            {Path, "Destination path"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty() || data.values[1].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto buildingSettings = data.getBuildTaskSettings();
        
        APath destinationPath = data.values[1];
        APathInfo destinationDirectory(destinationPath.directory());
        if (!destinationDirectory.isExists())
        {
            ProjectContext->log(fmt::format("Create: {}", destinationDirectory.path().toString()));
            if (!destinationDirectory.make())
            {
                completion(AError(2, fmt::format("Couldn't create a directory {}", destinationDirectory.path())));
                return;
            }
        }

        if (APathInfo(destinationPath).isExists())
        {
            remove(destinationPath);
        }

        auto error = copy(data.values[0], destinationPath);
        if (error)
        {
            ProjectContext->log(fmt::format("Warning: {}", error.getMessage()));
        }
        completion(AError());
    }

};

class OSMakePathTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.MakePath";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {Path, "Path"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        APathInfo path(data.values[0]);
        ProjectContext->log(fmt::format("Create: {}", data.values[0]));
        if(path.isExists())
        {
            completion(AError());
        }
        else
        {
            completion(path.make() ? AError() : AError(2, fmt::format("Couldn't create directory {}", path.path())));
        }
    }

};

class OSExecuteTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.Extecute";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {String, "FilterDirectory"},
            {String, "FilterExtension"},
            {String, "OutputFile"},
            {String, "Application"},
            {String, "Arguments"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[3].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        completion(executeWithFilter(data, [&](const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values){
            APath application = APath(resolveVariables(buildingSettings, data.values[3], values));//.resolveWithDirectory(data.targetInfo->getIntermediateDirectory());

            Array<String> arguments = data.values[4].split(' ');
            for(auto &argument : arguments)
            {
                argument = resolveVariables(buildingSettings, argument, values);
            }
            ProjectContext->log(fmt::format("Run: {} {}", application.toString().toUtf8().data(), String::join(arguments, " ")));
            return AProcess(application, arguments).execute();
        }, [&](const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values, const APathInfo &inputFilePathInfo, const APathInfo &outputFilePathInfo) {
            APathInfo application = APathInfo::getFromRelativePath(resolveVariables(buildingSettings, data.values[3], values));
            return inputFilePathInfo.modificationTime() > outputFilePathInfo.modificationTime() || application.modificationTime() > outputFilePathInfo.modificationTime();
        }));
    }

};

class OSGenerateVisualStudioProjectTargetTask : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.GenerateVisualStudioProject"; }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            { Path, "InputPath" },
            { Path, "OutputPath" },
        };
    }

    APath convertToRelativePath(const APath &path, const APath &directory) {
        APath p = ".";
        size_t i = 0;
        for (i; i < path.size(); ++i)
        {
            if (i >= directory.size() || path.source()[i] != directory.source()[i])
            {
                break;
            }
        }
        for (size_t j = i; j < directory.size(); ++j)
        {
            p.up();
        }
        for (i; i < path.size(); ++i)
        {
            p.append(path.source()[i]);
        }
        return p;
    };

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        getnerate(data.values[0], data.values[1]);
        completion(AError());
    }

    static String generateRandomGUID()
    {
        std::stringstream ss;
        auto addRandomByte = [&ss]() { ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (rand() % 255); };
        addRandomByte();
        addRandomByte();
        addRandomByte();
        addRandomByte();
        ss << '-';
        addRandomByte();
        addRandomByte();
        ss << '-';
        addRandomByte();
        addRandomByte();
        ss << '-';
        addRandomByte();
        addRandomByte();
        ss << '-';
        addRandomByte();
        addRandomByte();
        addRandomByte();
        addRandomByte();
        addRandomByte();
        addRandomByte();
        return ss.str();
    }

    static String generateRandomWrappedGUID()
    {
        return "{" + generateRandomGUID() + "}";
    }

    void getnerate(const APath &inputProject, const APath &outputProjectDirectory)
    {
        APath projectPath = outputProjectDirectory + (outputProjectDirectory.name() + ".vcxproj");

        SharedReference<OSProject> project = new OSProject();
        project->load(inputProject);

        APathInfo(outputProjectDirectory).make();

        generateSolution(outputProjectDirectory + (outputProjectDirectory.name() + ".sln"), project);
    }

    AError generateSolution(const APath &solutionPath, const SharedReference<OSProject> &project)
    {
        auto solutionGUID = generateRandomWrappedGUID();

        //APathInfo solutionPathInfo(solutionPath);
        AFile file(solutionPath, AFileOpenMode::WriteBinary);
        ProjectContext->log(fmt::format("Create Visual Studio solution file: {}", solutionPath));
        if (!file.isOpen())
        {
            return AError(1, fmt::format("Couldn't create Visual Studio solution file {}", solutionPath));
        }
        file <<
            "Microsoft Visual Studio Solution File, Format Version 12.00\r\n"
            "# Visual Studio 15\r\n"
            "VisualStudioVersion = 15.0.27703.2000\r\n"
            "MinimumVisualStudioVersion = 10.0.40219.1\r\n";

        ASet<String> solutionConfigurations;

        Array<APair<String, String>> projectsConfigurations;

        const Array<OneStudioProject2::Target> &targetsData = project->getTargetData();
        for (const OneStudioProject2::Target &targetData : targetsData)
        {
            auto projectFileGUID = generateRandomWrappedGUID();
            String projectName = targetData.Name + ".vcxproj";
            file <<
                "Project(\"" << solutionGUID << "\") = \"" << targetData.Name << "\", \"" << projectName << "\", \"" << projectFileGUID << "\"\r\n"
                "EndProject\r\n";

            generateProject(solutionPath.directory() + projectName, projectFileGUID, TaskData{ project, targetData }, solutionConfigurations, projectsConfigurations);
        }

        file << "Global\r\n"
            "	GlobalSection(SolutionConfigurationPlatforms) = preSolution\r\n";
        for (const String &configuration : solutionConfigurations)
        {
            file << "		" << configuration << " = " << configuration << "\r\n";
        }
        file << "	EndGlobalSection\r\n"
            "	GlobalSection(ProjectConfigurationPlatforms) = postSolution\r\n";
        for (const APair<String, String> &configuration : projectsConfigurations)
        {
            file << "		" << configuration.first << "." << configuration.second << ".ActiveCfg = " << configuration.second << "\r\n";
            file << "		" << configuration.first << "." << configuration.second << ".Build.0 = " << configuration.second << "\r\n";
        }
        file << "	EndGlobalSection\r\n"
            "	GlobalSection(SolutionProperties) = preSolution\r\n"
            "		HideSolutionNode = FALSE\r\n"
            "	EndGlobalSection\r\n"
            "	GlobalSection(ExtensibilityGlobals) = postSolution\r\n"
            "		SolutionGuid = " << generateRandomWrappedGUID() << "\r\n"
            "	EndGlobalSection\r\n"
            "EndGlobal\r\n";

        return AError::getEmptyError();
    }

    void generateProject(const APath &projectPath, const String &projectGUID, const TaskData &data, ASet<String> &solutionConfigurations, Array<APair<String, String>> &projectsConfigurations)
    {
        auto &project = data.project;
        auto &targetData = data.targetData;
        auto &target = project->findTarget(targetData.Name);
        auto buildTaskSettings = target->settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>();
        const APath &rootDirectory = project->getDirectory();

        static String OSBuildPath = APath::applicationPath().toString().quote();

        //TODO: implement different configurations for different targets
        Array<APair<String, StringHashMap<SharedReference<OSSettings>>>> targetConfigurations;
        for (size_t i = 0; i < project->getCountConfigurations(); ++i)
        {
            targetConfigurations.append({ project->getConfigurationName(i), project->getConfigurationSettings(i) });
        }

        if (!targetConfigurations)
        {
            targetConfigurations.append({ "Default", {} });
        }

        Array<XMLNode> configurationProperties;
        Array<XMLNode> configurations;
        Array<XMLNode> commands;

        Array<String> uniqueSourcePaths;

        for (const APair<String, StringHashMap<SharedReference<OSSettings>>> &configuration : targetConfigurations)
        {
            const String &configurationName = configuration.first;
            ProjectContext->pushEnvironment(TaskData{ data.project, data.targetData, configuration }, *target);
            const Array<String> &sourcePaths = buildTaskSettings->getItemValue(0, 1, 1).split(';');
            for (const String &source : sourcePaths)
            {
                if (!uniqueSourcePaths.has(source))
                {
                    uniqueSourcePaths.append(source);
                }
            }
            const String &productName = buildTaskSettings->getItemValue(0, 0, 1);
            const APath &destinationDirectory = buildTaskSettings->getItemValue(0, 3, 1);

            String includePaths;
            auto it = target->settings.find("com.InsaneTeam.OneStudio.CLanguage");
            if (it != target->settings.end())
            {
                auto includeDirs = it->second->getItemValue(1, 2, 1).split(';');
                for (auto &includeDir : includeDirs)
                {
                    processRecursive(includeDir, [&includePaths](const APath &path) {
                        includePaths += path.toString();
                        includePaths += ";";
                    });
                }

                //HACK: this code copied from CLanguage plugin
                auto frameworks = it->second->getItemValue(4, 2, 1).split(';');
                for (auto &framework : frameworks)
                {
                    APair<String, StringHashMap<String>> data = parseAttributesFromArgument(framework);
                    String &frameworkName = data.first;

                    String frameworkVersion;
                    auto it = data.second.find("version");
                    if (it != data.second.end())
                    {
                        frameworkVersion = it->second;
                    }
                    else
                    {
                        frameworkVersion = "CurrentVersion";
                    }

                    bool external = false;
                    it = data.second.find("external");
                    if (it != data.second.end())
                    {
                        external = true;
                    }

                    APath frameworkDirectory = ProjectContext->getLibraryDirectory() + frameworkName + frameworkVersion;
                    if (!external)
                    {
                        APathInfo interfaceDirectory(frameworkDirectory + "Interface");
                        if (interfaceDirectory.isExists())
                        {
                            includePaths.append(interfaceDirectory.path().toString());
                            includePaths.append(";");
                        }
                    }
                }
                //HACK

                if (includePaths)
                {
                    includePaths += "$(IncludePath)";
                }
            }

            for (auto i = 0; i < 2; ++i)
            {
                const String &configuration = (i == 0 ? "Build " : "Install ") + configurationName;
                static const String arch = "x64";
                String confarch = configuration + "|" + arch;
                configurations.append(XMLNode{
                    "ProjectConfiguration",
                    { { "Include", confarch } },
                    String(),
                    {
                        XMLNode{ "configuration", {}, configuration, {} },
                        XMLNode{ "Platform", {}, arch, {} },
                    }
                    });
                solutionConfigurations.insert(confarch);
                projectsConfigurations.append({ projectGUID, confarch });

                configurationProperties.append(XMLNode{
                    "PropertyGroup",
                    { { "Condition", "'$(Configuration)|$(Platform)'=='" + confarch + "'" } },
                    String(),
                    {
                        XMLNode{ "NMakeBuildCommandLine", {}, OSBuildPath + " --project=\"" + project->getPath().toString() + "\" --target=\"" + targetData.Name + "\" --action=" + (i == 0 ? "build" : "install") + (configurationName != "Default" ? " --configuration=\"" + configurationName + "\"": ""), {} },
                        XMLNode{ "NMakeCleanCommandLine", {}, OSBuildPath + " --project=\"" + project->getPath().toString() + "\" --target=\"" + targetData.Name + "\" --action=" + (i == 0 ? "clean" : "uninstall") + (configurationName != "Default" ? " --configuration=\"" + configurationName + "\"" : ""), {} },
                        XMLNode{ "NMakeOutput", {}, destinationDirectory + productName, {} },
                        XMLNode{ "IncludePath", {}, includePaths, {} },
                    }
                });

                Array<String> arguments = resolveVariables(buildTaskSettings, String::join(targetData.Run.Arguments, ';')).split(';'); //TODO: optimize
                for (String &argument : arguments)
                {
                    argument = argument.replace("\"", "\"").quote();
                }

                commands.append(XMLNode{
                    "PropertyGroup",
                    { { "Condition", "'$(Configuration)|$(Platform)'=='" + confarch + "'" } },
                    String(),
                    {
                        XMLNode{ "LocalDebuggerCommand", {}, resolveVariables(buildTaskSettings, targetData.Run.Command), {} },
                        XMLNode{ "LocalDebuggerCommandArguments", {}, String::join(arguments, " "), {} },
                        XMLNode{ "DebuggerFlavor", {}, "WindowsLocalDebugger", {} },
                    }
                    });
            }
            ProjectContext->popEnvironment();
        }

        XMLNode xmlProjectRoot{
            "Project",
            { { "ToolsVersion", "15.0" }, { "DefaultTargets", "Build" }, { "xmlns", "http://schemas.microsoft.com/developer/msbuild/2003" } },
            String(),
            { XMLNode {
                "PropertyGroup",
                { { "Label", "Globals" } },
                String(),
                {
                    XMLNode{ "VCProjectVersion", {}, "15.0", {} },
                    XMLNode{ "ProjectGuid", {}, projectGUID, {} },
                    XMLNode{ "Keyword", {}, "MakeFileProj", {} },
                    XMLNode{ "WindowsTargetPlatformVersion", {}, "8.1", {} },
                }
            }, XMLNode {
                "ItemGroup", { { "Label", "ProjectConfigurations" } }, "", configurations
            }, XMLNode {
                "Import", { { "Project", "$(VCTargetsPath)\\Microsoft.Cpp.Default.props" } }, String(), {}
            }, XMLNode {
                "PropertyGroup",
                {},
                String(),
                {
                    XMLNode{ "PlatformToolset", {}, "v141", {} },
                    XMLNode{ "ConfigurationType", {}, "Makefile", {} },
                }
            }, XMLNode {
                "Import", { { "Project", "$(VCTargetsPath)\\Microsoft.Cpp.props" } }, String(), {}
            } }
        };

        for (auto &c : configurationProperties)
        {
            xmlProjectRoot.nodes.append(std::move(c));
        }
        xmlProjectRoot.nodes.append(XMLNode{ "Import", { { "Project", "$(VCTargetsPath)\\Microsoft.Cpp.targets" } }, String(), {} });

        //GENERATE PROJECT PATHS
        //XMLNode xmlProjectRoot = XML::loadFromFile(projectPath);
        XMLNode *projectClCompileItemGroup = nullptr;
        XMLNode *projectClIncludeItemGroup = nullptr;
        XMLNode *projectNoneItemGroup = nullptr;
        /*for (XMLNode &node : xmlProjectRoot.nodes)
        {
            if (node.name == "ItemGroup" && node.nodes.size() > 0 && node.nodes.first().name == "ClCompile")
            {
                projectClCompileItemGroup = &node;
            }
        }
        for (XMLNode &node : xmlProjectRoot.nodes)
        {
            if (node.name == "ItemGroup" && node.nodes.size() > 0 && node.nodes.first().name == "ClInclude")
            {
                projectClIncludeItemGroup = &node;
            }
        }
        for (XMLNode &node : xmlProjectRoot.nodes)
        {
            if (node.name == "ItemGroup" && node.nodes.size() > 0 && node.nodes.first().name == "None")
            {
                projectNoneItemGroup = &node;
            }
        }*/
        size_t projectClCompileItemGroupIndex = -1;
        size_t projectClIncludeItemGroupIndex = -1;
        size_t projectNoneItemGroupIndex = -1;

        if (!projectClCompileItemGroup)
        {
            xmlProjectRoot.nodes.append({ "ItemGroup", {}, String::EmptyString(), {} });
            projectClCompileItemGroupIndex = xmlProjectRoot.nodes.size() - 1;
        }
        else
        {
            projectClCompileItemGroup->nodes.clear();
        }
        if (!projectClIncludeItemGroup)
        {
            xmlProjectRoot.nodes.append({ "ItemGroup", {}, String::EmptyString(), {} });
            projectClIncludeItemGroupIndex = xmlProjectRoot.nodes.size() - 1;
        }
        else
        {
            projectClIncludeItemGroup->nodes.clear();
        }
        if (!projectNoneItemGroup)
        {
            xmlProjectRoot.nodes.append({ "ItemGroup", {}, String::EmptyString(), {} });
            projectNoneItemGroupIndex = xmlProjectRoot.nodes.size() - 1;
        }
        else
        {
            projectNoneItemGroup->nodes.clear();
        }

        generateProjectFilters(projectPath.resolveWithExtension("vcxproj.filters"), rootDirectory, uniqueSourcePaths,
            &xmlProjectRoot.nodes[projectClCompileItemGroupIndex],
            &xmlProjectRoot.nodes[projectClIncludeItemGroupIndex],
            &xmlProjectRoot.nodes[projectNoneItemGroupIndex]);

        generateProjectUser(projectPath.resolveWithExtension("vcxproj.user"), rootDirectory, commands);

        //TODO: remove empty nodes
        /*if (projectClIncludeItemGroup->nodes.isEmpty())
        {
            auto it = xmlProjectRoot.nodes.find([&](const XMLNode &node) {
                return projectClIncludeItemGroup == &node;
            });
            if (it != xmlProjectRoot.nodes.end())
            {
                xmlProjectRoot.nodes.erase(it);
            }
        }

        if (projectClCompileItemGroup->nodes.isEmpty())
        {
            auto it = xmlProjectRoot.nodes.find([&](const XMLNode &node) {
                return projectClCompileItemGroup == &node;
            });
            if (it != xmlProjectRoot.nodes.end())
            {
                xmlProjectRoot.nodes.erase(it);
            }
        }

        if (projectNoneItemGroup->nodes.isEmpty())
        {
            auto it = xmlProjectRoot.nodes.find([&](const XMLNode &node) {
                return projectNoneItemGroup == &node;
            });
            if (it != xmlProjectRoot.nodes.end())
            {
                xmlProjectRoot.nodes.erase(it);
            }
        }*/

        ProjectContext->log(fmt::format("Create Visual Studio project file: {}", projectPath));
        if (XML::saveToFile(xmlProjectRoot, projectPath, "  "))
        {
            ProjectContext->log(fmt::format("Couldn't create Visual Studio project file: {}", projectPath));
        }
    }

    void generateProjectFilters(const APath &projectFiltersPath, const APath &rootDirectory, const Array<String> &sourcePaths, XMLNode *projectClCompileItemGroup, XMLNode *projectClIncludeItemGroup, XMLNode *projectNoneItemGroup)
    {
        XMLNode xmlFiltersRoot = { "Project", { { "ToolsVersion", "4.0" }, { "xmlns", "http://schemas.microsoft.com/developer/msbuild/2003" } } };
        xmlFiltersRoot.nodes.clear();
        APath outputProjectDirectory = projectFiltersPath.directory();
        for (const String &fullPath : sourcePaths)
        {
            APath relativeProjectEntryPath = convertToRelativePath(fullPath, rootDirectory);
            APath relativeVSProjectEntryPath = convertToRelativePath(fullPath, outputProjectDirectory);

            XMLNode ItemGroupFilters{ "ItemGroup", {}, String::EmptyString(), {} };

            String dir;
            for (const String &segment : relativeProjectEntryPath.source())
            {
                if (segment == "..")
                {
                    continue;
                }

                ItemGroupFilters.nodes.append(XMLNode{ "Filter", { { "Include", dir + segment } }, String::EmptyString(), {
                    //XMLNode{ "UniqueIdentifier", {}, AStaticInteger64(std::hash<String>()(path.toString())).toHexString(), {}}
                    } });

                dir.append(segment + "\\");
            }
            APath entryPath = APath(fullPath).resolveWithDirectory(projectFiltersPath.directory());
            
            if (!APathInfo(entryPath).isExists())
            {
                continue;
            }

            Array<APath> directories = ADirectory(entryPath).findRelativeRecursively(AFindFilter::AllDirectories);
            for (const APath &path : directories)
            {
                ItemGroupFilters.nodes.append(XMLNode{ "Filter", { { "Include", (relativeProjectEntryPath + path).toString() } }, String::EmptyString(), {
                    //XMLNode{ "UniqueIdentifier", {}, AStaticInteger64(std::hash<String>()(path.toString())).toHexString(), {}}
                    } });
            }
            xmlFiltersRoot.nodes.append(ItemGroupFilters);

            XMLNode ItemGroupNone{ "ItemGroup", {}, String::EmptyString(), {} };
            Array<APath> files = ADirectory(entryPath).findRelativeRecursively(AFindFilter::AllFiles);
            for (const APath &path : files)
            {
                static StringsHashMap ext1 = {
                    { "inl", "ClInclude" },
                    { "h", "ClInclude" },
                    { "hpp", "ClInclude" },
                    { "hxx", "ClInclude" },
                    { "h++", "ClInclude" },
                };
                static StringsHashMap ext2 = {
                    { "c", "ClCompile" },
                    { "cc", "ClCompile" },
                    { "cpp", "ClCompile" },
                    { "cxx", "ClCompile" },
                    { "c++", "ClCompile" },
                    { "m", "ClCompile" },
                    { "mm", "ClCompile" },
                };
                if (ext1.hasKey(path.extension()))
                {
                    ItemGroupNone.nodes.append(XMLNode{ "ClInclude", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {
                        XMLNode{ "Filter", {}, (dir + path).directory().toString(), {} }
                        } });
                    projectClIncludeItemGroup->nodes.append(XMLNode{ "ClInclude", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {} });
                }
                else if (ext2.hasKey(path.extension()))
                {
                    ItemGroupNone.nodes.append(XMLNode{ "ClCompile", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {
                        XMLNode{ "Filter", {}, (dir + path).directory().toString(), {} }
                        } });
                    projectClCompileItemGroup->nodes.append(XMLNode{ "ClCompile", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {} });
                }
                else
                {
                    ItemGroupNone.nodes.append(XMLNode{ "None", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {
                        XMLNode{ "Filter", {}, (dir + path).directory().toString(), {} }
                        } });
                    projectNoneItemGroup->nodes.append(XMLNode{ "None", { { "Include", (relativeVSProjectEntryPath + path).toString() } }, String::EmptyString(), {} });
                }
            }
            xmlFiltersRoot.nodes.append(ItemGroupNone);
        }
        ProjectContext->log(fmt::format("Create Visual Studio filters file: {}", projectFiltersPath));
        if (XML::saveToFile(xmlFiltersRoot, projectFiltersPath, "  "))
        {
            ProjectContext->log(fmt::format("Couldn't create Visual Studio filters file: {}", projectFiltersPath));
        }
    }

    void generateProjectUser(const APath &projectUserPath, const APath &rootDirectory, const Array<XMLNode> &commands)
    {
        XMLNode xmlUserRoot = { "Project", { { "ToolsVersion", "15.0" }, { "xmlns", "http://schemas.microsoft.com/developer/msbuild/2003" } }, String(), commands };

        ProjectContext->log(fmt::format("Create Visual Studio user file: {}", projectUserPath));
        if (XML::saveToFile(xmlUserRoot, projectUserPath, "  "))
        {
            ProjectContext->log(fmt::format("Couldn't create Visual Studio user file: {}", projectUserPath));
        }
    }
};

class OSDependencyTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.DependencyTarget";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            { String, "Action" },
            { String, "Path" },
            { String, "Target" },
            { String, "Configuration" },
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[0].isEmpty() || data.values[2].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto buildingSettings = data.getBuildTaskSettings();
        //APath application = ProjectContext->getDeveloperDirectory() + "Tools/OSBuild.exe";
        //APath path = APath(data.values[1]).resolveWithDirectory(data.project->getDirectory());
        /*Array<String> arguments = {
            String("--project=") + APath(path + (path.baseName() + ".osproject")).toString(),
            String("--target=") + data.values[2],
            String("--action=") + data.values[0],
        };*/

        /*ProjectContext->log(fmt::format("Build dependency: {} {}", application.toString().toUtf8().data(), String::join(arguments, " ")));
        completion(AProcess(application, arguments).execute());*/

        static StringHashMap<ADelegate<void(const TaskData &data, const ADelegate<void(AError &&error)> &completion)>> AvailableMethods = {
            {"Build", [](const TaskData &data, const ADelegate<void(AError &&erro)> &completion){ ProjectContext->build(data, completion); }},
            {"Clean", [](const TaskData &data, const ADelegate<void(AError &&erro)> &completion){ ProjectContext->clean(data, completion); }},
            {"Install", [](const TaskData &data, const ADelegate<void(AError &&erro)> &completion){ ProjectContext->install(data, completion); }},
            {"Uninstall", [](const TaskData &data, const ADelegate<void(AError &&erro)> &completion){ ProjectContext->uninstall(data, completion); }},
        };

        if (!AvailableMethods.hasKey(data.values[0]))
        {
            completion(AError(1, fmt::format("Invalid action: {}\r\n", data.values[0])));
            return;
        }

        APath path;
        if (data.values[1])
        {
            path = APath(data.values[1]).resolveWithDirectory(data.project->getDirectory());
            path + (path.baseName() + ".osproject");
        }
        else
        {
            path = data.project->getPath();
        }
        SharedReference<OSProject> dependencyProject = ProjectContext->loadProject(path);
        if(!dependencyProject)
        {
            completion(AError(2, fmt::format("Couldn't load project: {}\r\n", dependencyProject->getPath().toString())));
        }

        TaskData taskData{ dependencyProject };

        const auto &configurationName = resolveVariables(buildingSettings, data.values[3]);
        if (configurationName)
        {
            for (size_t i = 0; i < dependencyProject->getCountConfigurations(); ++i)
            {
                if (dependencyProject->getConfigurationName(i) == configurationName)
                {
                    taskData.configuration = { configurationName, dependencyProject->getConfigurationSettings(i) };
                    break;
                }
            }
        }

        const auto &targetName = resolveVariables(buildingSettings, data.values[2]);
        for(auto &targetData : dependencyProject->getTargetData())
        {
            //ProjectContext->log(fmt::format("\tTarget: name = \"{}\"\r\n", targetData.Name));
            if(targetName == targetData.Name)
            {
                auto lambda = [&taskData, &completion](const ADelegate<void(const TaskData &data, const ADelegate<void(AError &&error)> &completion)> &value) {
                    value(taskData, completion);
                };

                taskData.targetData = targetData;
                AvailableMethods.applyForValue(data.values[0], lambda);
                return;
            }
        }

        completion(AError(3, fmt::format("Target not found: {}\r\n", targetName)));
    }

};

class OSSystemScriptTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.SystemScript";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {String, "FilterDirectory"},
            {String, "FilterExtension"},
            {String, "OutputFile"},
            {Text, "Code"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[3].isEmpty()) {
            completion(AError(1, "Invalid values"));
            return;
        }

        completion(executeWithFilter(data, [&](const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values){
            String sourceCode = resolveVariables(buildingSettings, data.values[3], values);
            ProjectContext->log(fmt::format("Run script:\r\n{}", sourceCode));
            return system(sourceCode.toUtf8().data()) == 0 ? AError() : AError(2, "Invalid system call");
        }));
    }

};

APath createTemporaryPath()
{
    Array<uint8_t> array(sizeof(WCHAR) * (MAX_PATH + 1));
    GetTempPathW(array.size(), LPWSTR(array.data()));
    return String(array, StringEncoding::Utf16);
}

class OSExternalScriptTargetTask final : public OSTargetTask
{
public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.ExternalScript";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {String, "FilterDirectory"},
            {String, "FilterExtension"},
            {String, "OutputFile"},
            {Path, "Interpretator"},
            {String, "Arguments"},
            {Text, "Code"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(data.values[3].isEmpty() || data.values[5].isEmpty()) {
            completion(AError(1, "Invalid values"));
            return;
        }

        completion(executeWithFilter(data, [&](const SharedReference<OSBuildTaskSettings> &buildingSettings, const StringsHashMap &values){
            String interpretator = resolveVariables(buildingSettings, data.values[3], values);
            String arguments = resolveVariables(buildingSettings, data.values[4], values);
            String sourceCode = resolveVariables(buildingSettings, data.values[5], values);

            if(interpretator.isEmpty() || sourceCode.isEmpty()) {
                return AError(2, "Invalid values");
            }

            APath path = createTemporaryPath();
            ProjectContext->log(fmt::format("Run script:\r\n{} {} {}", interpretator, arguments, path.toString()));
            //return AProcess::execute(interpretator, arguments.split(':') + ) == 0;
            return AError(3, "Not implemented");
        }));
    }
};

class OSInstallLibrary final : public OSTargetTask
{
    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.InstallLibrary"; }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            { Path, "Source path" },
            { String, "Name" },
            { String, "Version" },
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if (data.values[0].isEmpty() || data.values[1].isEmpty() || data.values[2].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto buildingSettings = data.getBuildTaskSettings();
        const auto &name = resolveVariables(buildingSettings, data.values[1]);
        const auto &version = resolveVariables(buildingSettings, data.values[2]);

        APath destinationPath = ProjectContext->getLibraryDirectory() + name + version;
        completion(copy(data.values[0], destinationPath));
    }
};

class OSUninstallLibrary final : public OSTargetTask
{
    String getPackage() const final override { return "com.InsaneTeam.OneStudio.Project.TargetTasks.UninstallLibrary"; }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            { String, "Name" },
            { String, "Version" },
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if (data.values[0].isEmpty() || data.values[1].isEmpty())
        {
            completion(AError(1, "Invalid values"));
            return;
        }

        auto buildingSettings = data.getBuildTaskSettings();
        const auto &name = resolveVariables(buildingSettings, data.values[0]);
        const auto &version = resolveVariables(buildingSettings, data.values[1]);

        APath path = ProjectContext->getLibraryDirectory() + name + version;
        completion(remove(path));
    }
};

OSProjectContext::OSProjectContext()
{
    environment.resize(1);

    /*RegisterMetaClasses();

    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject *object = manager.findMetaObject("OneStudioProject2.GeneralSettingsData");
    StringHashMap<MetaObject::Property> properties = object->getAllProperties();
    for (auto &p : properties)
    {
        ALogMessage("", "PROPERTY: %s", p.first);
    }*/
    
    registerInternalTargetTask<OSCopyTargetTask>();
    registerInternalTargetTask<OSMakePathTargetTask>();
    registerInternalTargetTask<OSMoveTargetTask>();
    registerInternalTargetTask<OSRemoveTargetTask>();
    registerInternalTargetTask<OSRemoveBuildDirectoryTask>();
    registerInternalTargetTask<OSRemoveProductDirectoryTask>();
    registerInternalTargetTask<OSExecuteTargetTask>();
    registerInternalTargetTask<OSSystemScriptTargetTask>();
    registerInternalTargetTask<OSExternalScriptTargetTask>();
    registerInternalTargetTask<OSDependencyTargetTask>();
    registerInternalTargetTask<OSGenerateVisualStudioProjectTargetTask>();
    registerInternalTargetTask<OSInstallLibrary>();
    registerInternalTargetTask<OSUninstallLibrary>();

    settings.insert("com.InsaneTeam.OneStudio.General", new OSBuildTaskSettings());
}

OSProjectContext::~OSProjectContext()
{
    unload();
}

void updateEnvironmentFromProject(StringsHashMap &env, const TaskData &data, const OSProjectTargetDataInstance &target)
{
    env["ProjectName"] = data.project->getBaseName();
    env["ProjectExtension"] = data.project->getExtension();
    env["ProjectHash"] = fmt::format("{0:X}", std::hash<String>()(data.project->getPath().toString()));
    env["ProjectPath"] = data.project->getPath();
    env["ProjectDirectory"] = data.project->getDirectory();
    env["TargetName"] = data.targetData.Name;
    env["TargetPath"] = target.getPath();
    env["TargetDirectory"] = target.getDirectory();
    env["BuildingDirectory"] = target.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>()->getItemValue(0, 2, 1);
    env["DestinationDirectory"] = target.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>()->getItemValue(0, 3, 1);
    env["Configuration"] = data.configuration.first ? data.configuration.first : "Default";
    env["Temp"] = "C:\\Temp";
    if (data.configuration.first)
    {
        env[fmt::format("{}Configuration", data.configuration.first).toUtf8().data()] = data.configuration.first;
    }
}

void updateEnvironmentFromProject(StringsHashMap &env, const TaskData &data, const OneStudioProject2::Target &target)
{
    env["ProjectName"] = data.project->getBaseName();
    env["ProjectExtension"] = data.project->getExtension();
    env["ProjectHash"] = fmt::format("{0:X}", std::hash<String>()(data.project->getPath().toString()));
    env["ProjectPath"] = data.project->getPath();
    env["ProjectDirectory"] = data.project->getDirectory();
    env["TargetName"] = data.targetData.Name;
    //env["TargetPath"] = target.getPath();
    //env["TargetDirectory"] = target.getDirectory();
    env["BuildingDirectory"] = target.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>()->getItemValue(0, 2, 1);
    env["DestinationDirectory"] = target.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>()->getItemValue(0, 3, 1);
    env["Configuration"] = data.configuration.first ? data.configuration.first : "Default";
    env["Temp"] = "C:\\Temp";
    if (data.configuration.first)
    {
        env[fmt::format("{}Configuration", data.configuration.first).toUtf8().data()] = data.configuration.first;
    }
}

void OSProjectContext::updateRootEnvironment(const TaskData &data)
{
    updateRootEnvironment(data, *data.project->findTarget(data.targetData.Name));
}

void OSProjectContext::updateRootEnvironment(const TaskData &data, const OSProjectTargetDataInstance &target)
{
    updateEnvironmentFromProject(environment.first(), data, target);
}

void OSProjectContext::updateRootEnvironment(const TaskData &data, const OneStudioProject2::Target &target)
{
    updateEnvironmentFromProject(environment.first(), data, target);
}

void OSProjectContext::pushEnvironment(const TaskData &data)
{
    pushEnvironment(data, *data.project->findTarget(data.targetData.Name));
}

void OSProjectContext::pushEnvironment(const TaskData &data, const OSProjectTargetDataInstance &target)
{
    environment.resize(environment.size() + 1);
    auto &env = environment.last();
    env["DeveloperDirectory"] = getDeveloperDirectory();
    env["LibraryDirectory"] = getLibraryDirectory();
    env["SettingsDirectory"] = getSettingsDirectory();
    env["TasksDirectory"] = getTasksDirectory();
    env["ToolsDirectory"] = getToolsDirectory();

    updateEnvironmentFromProject(env, data, target);
}

void OSProjectContext::pushEnvironment(const TaskData &data, const OneStudioProject2::Target &target)
{
    environment.resize(environment.size() + 1);
    auto &env = environment.last();
    env["DeveloperDirectory"] = getDeveloperDirectory();
    env["LibraryDirectory"] = getLibraryDirectory();
    env["SettingsDirectory"] = getSettingsDirectory();
    env["TasksDirectory"] = getTasksDirectory();
    env["ToolsDirectory"] = getToolsDirectory();

    updateEnvironmentFromProject(env, data, target);
}

void OSProjectContext::popEnvironment()
{
    environment.resize(environment.size() - 1);
}

void OSProjectContext::runTargetTasks(const TaskData &taskData, const String &stepName, const ADelegate<void(AError &&error)> &completion)
{
    auto &project = taskData.project;
    auto &targetData = taskData.targetData;
    auto &configuration = taskData.configuration;
    auto &target = project->findTarget(targetData.Name);

    OSBuildingContextData data;
    data.project = project.data();
    data.targetData = targetData;
    data.target = target.data();

    pushEnvironment(taskData, *target);

    auto it = std::find_if(targetData.Actions.begin(), targetData.Actions.end(), [&](const auto &action) { return action.Name == stepName; });
    if (it == targetData.Actions.end())
    {
        ALogMessage("", "Warning: Action %s is not found", stepName);
    }
    else
    {
        const OneStudioProject2::Action& action = *it;

        for (const OneStudioProject2::Task &task : action.Tasks)
        {
            if (taskObserver)
            {
                if (stepName == "Build") { taskObserver->onBuildStart(targetData, task); }
                else if (stepName == "Clean") { taskObserver->onCleanStart(targetData, task); }
                else if (stepName == "Install") { taskObserver->onInstallStart(targetData, task); }
                else if (stepName == "Uninstall") { taskObserver->onUninstallStart(targetData, task); }
                else if (stepName == "Run") { taskObserver->onRunStart(targetData, task); }
            }

            log(task.Title ? task.Title : fmt::format("Task \"{}\":", task.Type));
            
            auto it = std::find_if(targetTasks.begin(), targetTasks.end(), [&](const auto &instance) { return instance->getPackage() == task.Type; });
            if (it == targetTasks.end())
            {
                AError error(-1, fmt::format("Implementation for {} is not found", task.Type));
                this->error(fmt::format("Building error. Task failed. (package = \"{}\"). Reason: {}", task.Type, error.getMessage()));
                completion(std::move(error));
                environment.removeLast();
                return;
            }
            
            auto taskInstance = *it;
            auto propertyNames = taskInstance->getProperties();

            data.values.clear();
            data.values.reserve(propertyNames.size());
            data.settings.clear();
            data.settings = target->settings;
            for (auto &pair : configuration.second)
            {
                auto it = target->settings.find(pair.first);
                if (it != target->settings.end())
                {
                    pair.second->setParent(it->second.data());
                    data.settings[pair.first] = pair.second;
                }
            }
            for (auto &name : propertyNames)
            {
                auto it = task.Values.find(name.second.split(':').first());

                String value;
                if (it != task.Values.end())
                {
                    auto &property = *it;

                    switch (name.first)
                    {
                    case OSTargetTask::Path:
                        value = APath(OSTargetTask::resolveVariables(data.getBuildTaskSettings(), property.second)).resolveWithDirectory(project->getDirectory());
                        break;
                    default:
                        value = property.second;
                        break;
                    }
                }
                data.values.append(value);
            }
            if (AError error = taskInstance->execute(data))
            {
                if (taskObserver)
                {
                    if (stepName == "Build") { taskObserver->onBuildFinish(targetData, task, error); }
                    else if (stepName == "Clean") { taskObserver->onCleanFinish(targetData, task, error); }
                    else if (stepName == "Install") { taskObserver->onInstallFinish(targetData, task, error); }
                    else if (stepName == "Uninstall") { taskObserver->onUninstallFinish(targetData, task, error); }
                    else if (stepName == "Run") { taskObserver->onRunFinish(targetData, task, error); }
                }
                this->error(fmt::format("Building error. Task failed. (package = \"{}\"). Reason: {}", task.Type, error.getMessage()));
                completion(std::move(error));
                environment.removeLast();
                return;
            }
            if (taskObserver)
            {
                if (stepName == "Build") { taskObserver->onBuildFinish(targetData, task, AError()); }
                else if (stepName == "Clean") { taskObserver->onCleanFinish(targetData, task, AError()); }
                else if (stepName == "Install") { taskObserver->onInstallFinish(targetData, task, AError()); }
                else if (stepName == "Uninstall") { taskObserver->onUninstallFinish(targetData, task, AError()); }
                else if (stepName == "Run") { taskObserver->onRunFinish(targetData, task, AError()); }
            }
        }
    }
    completion(AError());
    popEnvironment();
}

void OSProjectContext::build(const TaskData &data, const ADelegate<void(AError &&error)> &completion)
{
    if(data.project && data.targetData.Name)
    {
        if (taskObserver)
        {
            taskObserver->onBuildStart(*data.project, data.targetData);
            runTargetTasks(data, "Build", [this, &completion, data](AError &&error) {
                taskObserver->onBuildFinish(*data.project, data.targetData, error);
                completion(std::move(error));
            });
        }
        else
        {
            ProjectContext->log(fmt::format("****** Build project: {} Target: {} ******", data.project->getBaseName(), data.targetData.Name));
            runTargetTasks(data, "Build", completion);
        }
    }
}

void OSProjectContext::clean(const TaskData &data, const ADelegate<void(AError &&error)> &completion)
{
    if (data.project && data.targetData.Name)
    {
        if (taskObserver)
        {
            taskObserver->onCleanStart(*data.project, data.targetData);
            runTargetTasks(data, "Clean", [this, &completion, data](AError &&error) {
                taskObserver->onCleanFinish(*data.project, data.targetData, error);
                completion(std::move(error));
            });
        }
        else
        {
            ProjectContext->log(fmt::format("****** Clean project: {} Target: {} ******", data.project->getBaseName(), data.targetData.Name));
            runTargetTasks(data, "Clean", completion);
        }
    }
}

void OSProjectContext::install(const TaskData &data, const ADelegate<void(AError &&error)> &completion)
{
    auto callback = [this, data, completion](AError &&error){
        if(error)
        {
            completion(std::move(error));
        }
        if (data.project && data.targetData.Name)
        {
            if (taskObserver)
            {
                taskObserver->onInstallStart(*data.project, data.targetData);
                runTargetTasks(data, "Install", [this, &completion, data](AError &&error) {
                    taskObserver->onInstallFinish(*data.project, data.targetData, error);
                    completion(std::move(error));
                });
            }
            else
            {
                ProjectContext->log(fmt::format("****** Install project: {} Target: {} ******", data.project->getBaseName(), data.targetData.Name));
                runTargetTasks(data, "Install", completion);
            }
        }
    };

    build(data, callback);
}

void OSProjectContext::uninstall(const TaskData &data, const ADelegate<void(AError &&error)> &completion)
{
    if (data.project && data.targetData.Name)
    {
        if (taskObserver)
        {
            taskObserver->onUninstallStart(*data.project, data.targetData);
            runTargetTasks(data, "Uninstall", [this, &completion, data](AError &&error) {
                taskObserver->onUninstallFinish(*data.project, data.targetData, error);
                completion(std::move(error));
            });
        }
        else
        {
            ProjectContext->log(fmt::format("****** Uninstall project: {} Target: {} ******", data.project->getBaseName(), data.targetData.Name));
            runTargetTasks(data, "Uninstall", completion);
        }
    }
}

void OSProjectContext::run(const TaskData &data, const ADelegate<void(AError &&error)> &completion)
{
    if(data.project && data.targetData.Name)
    {
        ProjectContext->log(fmt::format("****** Run project: {} Target: {} ******", data.project->getBaseName(), data.targetData.Name));
        
        auto &project = data.project;
        auto &targetData = data.targetData;
        auto &configuration = data.configuration;
        auto &target = project->findTarget(targetData.Name);

        pushEnvironment(data, *target);

        OSBuildingContextData contextData;
        contextData.project = project.data();
        contextData.targetData = targetData;
        contextData.target = target.data();
        contextData.settings.clear();
        contextData.settings = target->settings;

        APath applicationPath = APath(OSTargetTask::resolveVariables(contextData.getBuildTaskSettings(), data.targetData.Run.Command)).resolveWithDirectory(project->getDirectory());
        Array<String> arguments = data.targetData.Run.Arguments;
        ProjectContext->log(!arguments ? applicationPath : applicationPath + " " + String::join(arguments, " "));
        AProcess process(applicationPath, arguments);
        process.addObserver(ProjectContext);
        ProjectContext->log("App return: " + String::number(process.execute().getErrorCode()));
        popEnvironment();
    }
}

void OSProjectContext::load(const APath &developerDirectory)
{
    this->developerDirectory = developerDirectory;
    this->libraryDirectory = developerDirectory + "Library";
    this->settingsDirectory = developerDirectory + "Settings";
    this->tasksDirectory = developerDirectory + "Tasks";
    this->toolsDirectory = developerDirectory + "Tools";

    loadTasks(getTasksDirectory());
    loadSettings(getSettingsDirectory());
}

void OSProjectContext::unload()
{
    unloadSettings();
    unloadTasks();
}

void resaveSettings(Array<OneStudioProject2::Settings> &settingsContainer, OSSettingsDataInstance *instance, const SharedReference<OSSettings> settings);

void OSProjectContext::loadSettings(APathInfo settingsDirectory)
{
    settingsDirectory.make();

    for(auto &pair : settings)
    {
        auto data = pair.second->getFileData().cast<OSSettingsDataInstance>();
        if(data)
        {
            data->setPath(settingsDirectory.path() + (pair.first + ".settings"));
            data->setRootSettings(true);
            if(!data->load(false))
            {
                AAssert(data->create(), "Couldn't create settings file: %s", data->getPath().toString().toUtf8().data());
            }
            resaveSettings(s, data.data(), pair.second);
        }
        else
        {
            //ProjectContext->log(fmt::format("Couldn't load settings for plugin: {}", pair.first));
        }
    }
}

void OSProjectContext::unloadSettings()
{
    settings.clear();
}

void OSProjectContext::loadTasks(APathInfo tasksDirectory, const String &pluginExtension)
{
    tasksDirectory.make();

    ADirectory directory(tasksDirectory);
    if(directory)
    {
        auto entries = directory.find(pluginExtension, AFindFilter::AllFiles);
        for(auto &pathInfo : entries)
        {
            SharedReference<TaskPluginType> plugin = createNew<TaskPluginType>();
            plugin->setPath(pathInfo.path());
            log(fmt::format("### Load task plugin: {}", plugin->getPath().toUnixPathString()));
            if(plugin->load() && plugin->getInstance().cast<OSTaskPlugin>())
            {
                log(fmt::format("### Task plugin is loaded: {} ({})", pathInfo.path().name(), plugin->getPackage()));
                const SharedReference<OSTaskPlugin> &taskPluginInstance = plugin->getInstance();
                registerTargetTask(taskPluginInstance->getTask().data());
                taskPluginInstance->onLoad(this);
                SharedReference<OSSettings> taskSettings = taskPluginInstance->createSettings();
                //resaveSettings(s, data.data(), pair.second);
                settings.insert(plugin->getPackage(), taskSettings);
                tasks.insert(plugin->getPackage(), plugin);
            }
        }
    }
}

void OSProjectContext::unloadTasks()
{
    for(auto &pluginPair : tasks)
    {
        pluginPair.second->getInstance().cast<OSTaskPlugin>()->onUnload();
        pluginPair.second->unload();
    }
    tasks.clear();
}
