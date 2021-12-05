#include "OSCBuildOperation.h"
#include "OSCCompilationOperation.h"
#include "OSCArchivationOperation.h"
#include "OSCLinkageOperation.h"

#include "Main.h"

AError OSCBuildOperation::main()
{
    findFilesWithExtension({"c", "cpp", "c++", "cp", "cc", "cxx", "m", "mm"}, ADelegate<void(const APath &)>(this, &OSCBuildOperation::addSourceFile));

    auto compileError = compile();

    if(compileError) {
        ProjectContext->log("Compilation failed");
        return compileError;
    }

    APath destinationDirectory = APath(getBuildingSettings().destinationDirectory).resolveWithDirectory(workspaceDirectory);

    APath productPath;
    SharedReference<OSLinkageOperation> linkageOperation;
    if(getBuildLibrary() && archiverSettings.archiver)
    {
        productPath = destinationDirectory + (getBuildingSettings().productName + "." + filesSettings.staticLibraryFileName);
        auto archivationOperation = createNew<OSCArchivationOperation>();
        archivationOperation->setArchiverSettings(getArchiverSettings());
        archivationOperation->setFilesSettings(getFilesSettings());
        linkageOperation = archivationOperation;
    }
    else
    {
        productPath = destinationDirectory + (getBuildingSettings().productName + "." + (getBuildLibrary() ? filesSettings.dynamicLibraryFileName : filesSettings.applicationFileName));
        auto clinkageOperation = createNew<OSCLinkageOperation>();
        clinkageOperation->setBuildLibrary(getBuildLibrary());
        clinkageOperation->setLinkerSettings(getLinkerSettings());
        clinkageOperation->setLinkageSettings(getLinkageSettings());
        clinkageOperation->setFilesSettings(getFilesSettings());
        linkageOperation = clinkageOperation;
    }
    linkageOperation->setSourceFiles(objectFiles);
    linkageOperation->setDestinationPath(productPath);

    APathInfo(destinationDirectory).make();
    AError linkageError = ProjectContext->getOperationDispatcher().performOperation(linkageOperation);
    if(linkageError)
    {
        ProjectContext->log("Linkage failed");
        return linkageError;
    }

    ProjectContext->log("Build successful");
    return AError::getEmptyError();
}

void OSCBuildOperation::addSourceFile(const APath &path)
{
    auto operation = createNew<OSCCompilationOperation>();
    operation->setCompilerSettings(getCompilerSettings());
    operation->setCompilationSettings(getCompilationSettings());
    operation->setFilesSettings(getFilesSettings());
    operation->setSourceFile(path);

    operation->setDestinationDirectory(APath(getBuildingSettings().buildingDirectory).resolveWithDirectory(workspaceDirectory));
    APathInfo(operation->getDestinationDirectory().directory()).make();
    compilationOperations.append(operation);
}

AError OSCBuildOperation::compile()
{
    if(!compilationOperations)
    {
        return AError::getEmptyError();
    }

    auto error = ProjectContext->getOperationDispatcher().performOperations(compilationOperations);

    if(error) {
        return error;
    }

    for(auto operation : compilationOperations)
    {
        objectFiles.append(operation.as<OSCCompilationOperation>()->getDestinationPath());
    }
    return error;
}
