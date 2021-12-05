#include "OSCTargetTask.h"

#include <OneStudioCLanguage>

//TODO: Move it to APath class

struct CopyDelegates
{
    ADelegate<void()> started;
    ADelegate<bool(const APath &source, const APath &destination)> shouldCopy;
    ADelegate<void(const APath &source, const APath &destination)> copied;
    ADelegate<void()> completed;
};

AError copyRecursive(const APathInfo &source, const APath &destination, CopyDelegates delegates)
{
    if(source.isFile() && source.isSymbolicLink())
    {
        if(((delegates.shouldCopy && delegates.shouldCopy(source.path(), destination)) || !delegates.shouldCopy) && source.copy(destination))
        {
            if(delegates.copied)
            {
                delegates.copied(source.path(), destination);
            }
        }
        else
        {
            return AError(1, fmt::format("Couldn't copy file \"{}\" to \"{}\"", source.path().toString(), destination.toString()));
        }
    }
    else if(source.isDirectory())
    {
        APathInfo destinationInfo(destination);
        if(destinationInfo.isExists())
        {
            if(!destinationInfo.isDirectory())
            {
                return AError(2, fmt::format("Couldn't copy directory \"{}\", because file already exist at \"{}\"", source.path().toString(), destination.toString()));
            }
        }
        else
        {
            if(!destinationInfo.make())
            {
                return AError(3, fmt::format("Couldn't create directory \"{}\", directory cannot be created", source.path().toString(), destination.toString()));
            }
        }

        Array<APath> paths = ADirectory(source).findRelativeRecursively(AFindFilter::All);
        for(auto &path : paths)
        {
            APathInfo sourcePathInfo(source.path() + path);
            APathInfo destinationPathInfo(destination + path);
            if(sourcePathInfo.isFile())
            {
                if(destinationPathInfo.isExists())
                {
                    if(!destinationPathInfo.isFile())
                    {
                        return AError(4, fmt::format("Couldn't copy file \"{}\" to \"{}\", destination path is beeing used and can't be rewritten", sourcePathInfo.path().toString(), (destination + path).toString()));
                    }

                    if(sourcePathInfo.modificationTime() <= destinationPathInfo.modificationTime())
                    {
                        continue;
                    }

                    if(!destinationPathInfo.remove())
                    {
                        ProjectContext->log(fmt::format("Remove: {}", destinationPathInfo.path().toString()));
                        return AError(5, fmt::format("Couldn't copy file \"{}\" to \"{}\", file cannot be rewritten", sourcePathInfo.path().toString(), (destination + path).toString()));
                    }
                }

                if(((delegates.shouldCopy && delegates.shouldCopy(sourcePathInfo.path(), destinationPathInfo.path())) || !delegates.shouldCopy) && sourcePathInfo.copy(destinationPathInfo.path()))
                {
                    ProjectContext->log(fmt::format("Copy: {} -> {}", sourcePathInfo.path().toString(), destinationPathInfo.path().toString()));
                    if(delegates.copied)
                    {
                        delegates.copied(sourcePathInfo.path(), destinationInfo.path());
                    }
                }
                else
                {
                    return AError(6, fmt::format("Couldn't copy file \"{}\" to \"{}\", file cannot be copied", sourcePathInfo.path().toString(), (destination + path).toString()));
                }
            }
            else if(sourcePathInfo.isDirectory())
            {
                APathInfo dir(destination + path);
                if(!dir.make())
                {
                    return AError(3, fmt::format("Couldn't create directory \"{}\", directory cannot be created", dir.path().toString(), (destination + path).toString()));
                }
            }
        }
    }
    return AError::getEmptyError();
}

class OSInstallUnixFrameworkTargetTask final : public OSTargetTask
{

public:

    String getPackage() const final override { return "com.InsaneTeam.OneStudio.InstallUnixFramework";  }
    String getVersion() const final override { return "1.0.0"; }
    Array<APair<PropertyType, String>> getProperties() const final override
    {
        return {
            {String, "Interface Directory"},
            {String, "Library Directory"},
            {String, "Header"},
            {String, "Dependencies"},
        };
    }

    void onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion) override
    {
        if(!data.values[0])
        {
            completion(AError(-1, "Interface directory is empty"));
        }

        auto buildingSettings = data.getBuildTaskSettings();

        String productName = buildingSettings->getItemValue(0, 0, 1);
        String destinationDirectory = buildingSettings->getItemValue(0, 0, 3);

        APath frameworkDirectory = ProjectContext->getDeveloperDirectory() + "Library" + productName;

        String version = "1.0.0";

        APathInfo versionDirectory(frameworkDirectory + version);
        versionDirectory.make();

        APath interfaceDirectory = versionDirectory.path() + "Interface";
        bool needUpdateHeader = false;
        CopyDelegates delegates;
        delegates.copied = [&needUpdateHeader](const APath &source, const APath &destination){
            needUpdateHeader = true;
        };
        copyRecursive(APathInfo(OSTargetTask::resolveVariables(buildingSettings, data.values[0])), interfaceDirectory, delegates);

        if(data.values[1]){
            copyRecursive(APathInfo(OSTargetTask::resolveVariables(buildingSettings, data.values[1])), versionDirectory.path() + "Library", delegates);
        }

        AJSONObject description;

        description.insert("Product", productName);
        description.insert("Version", version);

        String header = data.values[2];
        Array<String> dependencies = data.values[3].split(';');
        if(dependencies)
        {
            description.insert("Dependencies", AJSONArray(dependencies));
        }
        if(needUpdateHeader && header)
        {
            description.insert("Header", header);
            AFile file;
            if(file.open(interfaceDirectory + header, AFileOpenMode::WriteBinary))
            {
                auto writeIncludes = [&file, &interfaceDirectory](const String &extension){
                    Array<APath> includes = ADirectory(interfaceDirectory).findRelativeRecursively(extension, AFindFilter::AllFiles);
                    if(includes)
                    {
                        for(auto &include : includes)
                        {
                            file << "\r\n#include \"" << include.toUnixPathString().toUtf8().data() << "\"";
                        }
                    }
                };

                file << "#pragma once\r\n";
                if(dependencies)
                {
                    for(auto &dependency : dependencies)
                    {
                        file << "\r\n#include <" << dependency.toUtf8().data() << ">";
                    }
                }
                writeIncludes("h");
                writeIncludes("hpp");
                writeIncludes("inl");
            }
        }
        AJSON::saveToFile(description, versionDirectory.path() + "Description.json");

        completion(AError());
    }

};


class OSCTaskPlugin : public OSTemplateTaskPlugin<OSCTargetTask, OSCTaskSettings>
{
public:

    SharedReference<OSInstallUnixFrameworkTargetTask> installTask = createNew<OSInstallUnixFrameworkTargetTask>();

    void onLoad(OSProjectContext *context) override
    {
        ProjectContext = context;
        ProjectContext->registerTargetTask(installTask.data());

        /*OneStudioPlatform::ApplicationContext &instance = OneStudioPlatform::ApplicationContext::getInstance();

        instance->registerCommand("Compile", [](const Array<String> &arguments) {
            if (arguments.size() < 1)
            {
                return;
            }


        });*/
    }

};

AApplicationPluginImplementation(OSTaskPlugin, OSCTaskPlugin, 1, "1.0.0", "com.InsaneTeam.OneStudio.CLanguage")
