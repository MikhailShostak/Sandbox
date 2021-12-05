#include "OSCTargetTask.h"

#include <OneStudioCLanguage>

void OSCTargetTask::onRun(const OSBuildingContextData &data, const ADelegate<void(AError &&error)> &completion)
{
    auto buildingSettings = data.targetData.settings.at("com.InsaneTeam.OneStudio.General").as<OSBuildTaskSettings>();
    auto unixSettings = data.targetData.settings.at("com.InsaneTeam.OneStudio.CLanguage").as<OSCTaskSettings>();
    SharedReference<OSCBuildOperation> buildOperation = createNew<OSCBuildOperation>();

	OSBuildingSettingsDataObject::Data buildingData = {};
    buildingData.productName = buildingSettings->getItemValue(0, 0, 1);
    buildingData.sourcePaths = buildingSettings->getItemValue(0, 1, 1);
    buildingData.buildingDirectory = buildingSettings->getItemValue(0, 2, 1);
    buildingData.destinationDirectory = buildingSettings->getItemValue(0, 3, 1);

    OSCCompilerSettingsDataObject::Data compilerData = unixSettings->getResolvedCompilerSettings();
    OSCCompilationSettingsDataObject::Data compilationData = unixSettings->getResolvedCompilationSettings();
    OSCFilesSettingsDataObject::Data filesData = unixSettings->getResolvedFilesSettings();
    OSCLinkageSettingsDataObject::Data linkageData = unixSettings->getResolvedLinkageSettings();

    Array<String> frameworks = linkageData.frameworks.split(';');
    for(auto &frameworkData : frameworks)
    {
        APair<String, StringHashMap<String>> data = parseAttributesFromArgument(frameworkData);
        String &frameworkName = data.first;

        String frameworkVersion;
        auto it = data.second.find("version");
        if(it != data.second.end())
        {
            frameworkVersion = it->second;
        }
        else
        {
            frameworkVersion = "CurrentVersion";
        }

        bool external = false;
        it = data.second.find("external");
        if(it != data.second.end())
        {
            external = true;
        }

        APath frameworkDirectory = ProjectContext->getDeveloperDirectory() + "Library" + frameworkName + frameworkVersion;
        if(!external)
        {
            APathInfo interfaceDirectory(frameworkDirectory + "Interface");
            if(interfaceDirectory.isExists())
            {
                compilationData.includePaths.append(";");
                compilationData.includePaths.append(interfaceDirectory.path().toString());
            }
        }

        auto addLibrary = [&linkageData](const String &name, const APathInfo &directory = APathInfo()){
            if(directory.isDirectory())
            {
                linkageData.libraryPaths.append(";");
                linkageData.libraryPaths.append(directory.path().toString());
            }
            linkageData.libraries.append(";");
            linkageData.libraries.append(name);
        };
        
        if(external)
        {
            addLibrary(frameworkName);
        }
        else
        {
            APath libraryDirectory = frameworkDirectory + "Library";
            APath library = libraryDirectory + frameworkName;
            APathInfo staticLibrary(library.resolveWithExtension(filesData.staticLibraryFileName));
            APathInfo dynamicLibrary(library.resolveWithExtension(filesData.dynamicLibraryFileName));
            if(staticLibrary.isExists() || dynamicLibrary.isExists())
            {
                addLibrary(frameworkName, libraryDirectory);
            }
        }
    }

    auto libraryList = linkageData.libraries.split(';');
    linkageData.libraries = String();
    for(auto &libraryData : libraryList)
    {
        APair<String, StringHashMap<String>> data = parseAttributesFromArgument(libraryData);
        String &libraryName = data.first;
        bool dynamic = false;
        libraryName.append(String(".") + (data.second.find("dynamic") != data.second.end() ? filesData.dynamicLibraryFileName :  filesData.staticLibraryFileName));
        if(linkageData.libraries)
        {
            linkageData.libraries.append(';');
        }
        linkageData.libraries.append(libraryName);
    }

    auto &productType = data.values[0];
    if(productType == "Static Library")
    {
        OSCArchiverSettingsDataObject::Data archiverData = unixSettings->getResolvedArchiverSettings();
        buildOperation->setArchiverSettings(archiverData);
		buildOperation->setBuildLibrary(true);
    }
    else
    {
        OSCLinkerSettingsDataObject::Data linkerData = unixSettings->getResolvedLinkerSettings();
        buildOperation->setLinkerSettings(linkerData);
        buildOperation->setLinkageSettings(linkageData);
        buildOperation->setBuildLibrary(productType == "Shared Library");
    }

    buildOperation->setCompilerSettings(compilerData);
    buildOperation->setCompilationSettings(compilationData);
    buildOperation->setFilesSettings(filesData);
    buildOperation->setBuildingSettings(buildingData);
    buildOperation->workspaceDirectory = data.project->getDirectory();
    ProjectContext->getOperationDispatcher().addOperation(buildOperation, completion);
}
