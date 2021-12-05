#include "OSCArchivationOperation.h"
#include "Utils.h"

AError OSCArchivationOperation::main()
{
    if(!getArchiverSettings().archiver)
    {
        ProjectContext->error(fmt::format("Archivation error: {}", "Archiver not defined"));
        return AError(1, "Archiver not defined");
    }

    if(getSourceFiles().isEmpty())
    {
        ProjectContext->error(fmt::format("Archivation error: {}", "Nothing to archive"));
        return AError(2, "Nothing to archive");
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
            arguments.push_back(flag);
            arguments.push_back(parameter);
        }
        else
        {
            arguments.push_back(flag + parameter);
        }
    };

    for(auto &flag : Str::Split(getArchiverSettings().flags, ";"))//arguments.push_back("rcsu");
    {
        arguments.push_back(flag);
    }

    insertArgument(getArchiverSettings().outputFileFlag, getDestinationPath().toString(), true);

    for(auto path : getSourceFiles())
    {
        arguments.push_back(path.toString());
    }

    ProjectContext->log(getArchiverSettings().archiver.quote() + " " + String::join(quoteStrings(arguments), " "));
    AProcess process(getArchiverSettings().archiver, arguments);
    process.addObserver(ProjectContext);
    AError error = process.execute();
    if(error)
    {
        ProjectContext->error(fmt::format("Archivation error: {}", fmt::format("Archivation failed with code = {}", error.getErrorCode())));
    }

    return error;
}
