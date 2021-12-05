#include "OSCLinkageOperation.h"
#include "Utils.h"

AError OSCLinkageOperation::main()
{
    if(!getLinkerSettings().linker)
    {
        ProjectContext->error(fmt::format("Linkage error: {}", "Linker not defined"));
        return AError(1, "Linker not defined");
    }

    if(getSourceFiles().isEmpty())
    {
        ProjectContext->error(fmt::format("Linkage error: {}", "Nothing to link"));
        return AError(2, "Nothing to link");
    }

    APathInfo destinationFile(getDestinationPath());
    if(destinationFile.isFile())
    {
        auto paths = getSourceFiles();
        bool needToRebuild = false;
        for(auto &path : paths)
        {
            APathInfo sourceFile(path);
            if(sourceFile.modificationTime() > destinationFile.modificationTime())
            {
                ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", sourceFile.path().toString(), destinationFile.path().toString()));
                needToRebuild = true;
                break;
            }
        }

        if(!needToRebuild)
        {
            auto libraries = getLinkageSettings().libraries.split(';');
            auto librariePaths = getLinkageSettings().libraryPaths.split(';');
            for(auto &library : libraries)
            {
                for(auto &libraryPath : librariePaths)
                {
                    APathInfo libraryFile(libraryPath + library);
                    if(libraryFile.isExists())
                    {
                        if(libraryFile.modificationTime() > destinationFile.modificationTime())
                        {
                            ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", libraryFile.path().toString(), destinationFile.path().toString()));
                            needToRebuild = true;
                        }
                        break;
                    }
                    /*APathInfo staticLibraryFile(libraryPath + (library + getFilesSettings().staticLibraryFileName));
                    if(staticLibraryFile.isExists())
                    {
                        if(staticLibraryFile.modificationTime() > destinationFile.modificationTime())
                        {
                            ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", staticLibraryFile.path().toString(), destinationFile.path().toString()));
                            needToRebuild = true;
                        }
                        break;
                    }

                    APathInfo dynamicLibraryFile(libraryPath + (library + getFilesSettings().dynamicLibraryFileName));
                    if(dynamicLibraryFile.isExists())
                    {
                        if(dynamicLibraryFile.modificationTime() > destinationFile.modificationTime())
                        {
                            ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", dynamicLibraryFile.path().toString(), destinationFile.path().toString()));
                            needToRebuild = true;
                        }
                        break;
                    }*/
                }
                if(needToRebuild)
                {
                    break;
                }
            }
        }
        if(!needToRebuild)
        {
            return AError::getEmptyError();
        }
    }

    APathInfo(getDestinationPath().directory()).make();
    Array<String> arguments;

    auto insertArgument = [this, &arguments](const String &flag, const String &parameter, bool force = false)
    {
        if(!flag && !force)
        {
            return;
        }

        if(flag.last() == ' ')
        {
            arguments.append(flag);
            arguments.append(parameter);
        }
        else
        {
            arguments.append(flag + parameter);
        }
    };

    auto insertArguments = [this, &arguments](const String &flag, const String &parameters, bool force = false)
    {
        if(!flag && !force)
        {
            return;
        }

        if(flag.last() == ' ')
        {
            for(auto &parameter : parameters.split(';'))
            {
                arguments.append(flag);
                arguments.append(parameter);
            }
        }
        else
        {
            for(auto &parameter : parameters.split(';'))
            {
                arguments.append(flag + parameter);
            }
        }
    };

    auto &specificFlags = getBuildLibrary() ? getLinkerSettings().libraryFlags : getLinkerSettings().applicationFlags;
    for(auto &flag : specificFlags.split(';'))
    {
        arguments.append(flag);
    }

    for(auto &flag : getLinkerSettings().flags.split(';'))
    {
        arguments.append(flag);
    }

    insertArgument(getLinkerSettings().outputFileFlag, getDestinationPath().toString(), true);

    for(auto path : getSourceFiles())
    {
        arguments.append(path.toString());
    }

    for(auto &libraryPath : getLinkageSettings().libraryPaths.split(';'))
    {
        auto insertLibraryPath = [this, &arguments](const APath &path){
            arguments.append(getLinkerSettings().libraryPathFlag + path.toString());
        };

        APair<String, StringHashMap<String>> data = parseAttributesFromArgument(libraryPath);
        insertLibraryPath(data.first);
        if(data.second.find("recursive") != data.second.end())
        {
            APathInfo info(data.first);
            if(info.isDirectory())
            {
                ADirectory dir(std::move(info));
                Array<APathInfo> subdirs = dir.findRecursively(AFindFilter::AllDirectories);
                for(const APathInfo &subdir : subdirs)
                {
                    insertLibraryPath(subdir.path());
                }
            }
        }
    }

    insertArguments(getLinkerSettings().libraryFlag, getLinkageSettings().libraries, true);

    ProjectContext->log(getLinkerSettings().linker.quote() + " " + String::join(quoteStrings(arguments), " "));
    AProcess process(getLinkerSettings().linker, arguments);
    process.addObserver(ProjectContext);
    AError error = process.execute();
    if(error)
    {
        ProjectContext->error(fmt::format("Linkage error: {}", fmt::format("Linkage failed with code = {}", error.getErrorCode())));
    }

    return error;
}
