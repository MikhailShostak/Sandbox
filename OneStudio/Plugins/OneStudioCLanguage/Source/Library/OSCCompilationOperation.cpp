#include "OSCCompilationOperation.h"
#include "Utils.h"

bool skipFile(const APath &sourcePath, const APath &destinationPath)
{
    APathInfo sourceInfo(sourcePath);
    APathInfo objectInfo(destinationPath);
    if(objectInfo.modificationTime() == 0)
    {
        return false;
    }

    if (sourceInfo.modificationTime() > objectInfo.modificationTime())
    {
        ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", sourceInfo.path().toString(), objectInfo.path().toString()));
        return false;
    }

    AFile file;
    Array<String> dependenciesList;
    APath dependenciesPath = destinationPath.resolveWithExtension("d");
    if(file.open(dependenciesPath, AFileOpenMode::Read))
    {
		dependenciesList = String(file.readAll()).replace("\\ ", " ").replace("  ", "").replace(" \\\n", ";").split(';');
        dependenciesList.removeFirst();
    }
    for(String &dependence : dependenciesList)
    {
        APath dependencePath(dependence);
        if(dependencePath.isRelative())
        {
            dependencePath = sourcePath.directory() + dependencePath;
        }
        APathInfo dependenceFile(std::move(dependencePath));
        if(dependenceFile.modificationTime() > objectInfo.modificationTime())
        {
            ProjectContext->log(fmt::format("{} is newer, need to rebuild {}", dependenceFile.path().toString(), objectInfo.path().toString()));
            return false;
        }
    }
    return true;
}

AError OSCCompilationOperation::main()
{
    if(!getCompilerSettings().compiler)
    {
        ProjectContext->error(fmt::format("Compilation error: {}", "Compiler not defined"));
        return AError(1, "Compiler not defined");
    }

    APathInfo(getDestinationDirectory()).make();
    destinationPath = getDestinationDirectory() + (getSourceFile().baseName() + "." + getFilesSettings().objectFileName);
    if(skipFile(getSourceFile(), destinationPath))
    {
        return AError::getEmptyError();
    }

    Array<String> arguments;

    auto insertArgument = [&arguments](const String &flag, const String &parameter, bool force = false)
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

    auto insertArguments = [&arguments](const String &flag, const String &parameters, bool force = false)
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

    insertArguments(getCompilerSettings().defineFlag, getCompilationSettings().defines);
    insertArguments(getCompilerSettings().includeFlag, getCompilationSettings().includes);

    if(getCompilerSettings().includePathFlag)
    {
        for(auto &includePath : getCompilationSettings().includePaths.split(';'))
        {
            processRecursive(includePath, [this, &arguments](const APath &path) {
                arguments.append(getCompilerSettings().includePathFlag + path.toString());
            });
        }
    }

    for(auto &flag : getCompilerSettings().flags.split(';'))
    {
        arguments.append(flag);
    }

    insertArgument(getCompilerSettings().compilationFlag, getSourceFile().toString(), true);
    insertArgument(getCompilerSettings().outputFileFlag, destinationPath, true);

    class : public AProcessObserver
    {
    public:

        String log;
        String error;

        void onOutputMessage(uint8_t *buffer, size_t size)
        {
            String s(Array<uint8_t>(buffer, buffer + size));
            s.replace("\r", "");
            log.append(s);
        }

        void onErrorMessage(uint8_t *buffer, size_t size)
        {
            String s(Array<uint8_t>(buffer, buffer + size));
            s.replace("\r", "");
            error.append(s);
        }

    } compilerOutput;

    ProjectContext->log(getCompilerSettings().compiler.quote() + " " + String::join(quoteStrings(arguments), " "));
    AProcess process(getCompilerSettings().compiler, arguments);
    process.addObserver(&compilerOutput);
    auto error = process.execute();

    static AMutex mutex;
    mutex.lock();
    if(compilerOutput.log)
    {
        ProjectContext->log(compilerOutput.log);
    }

    if(compilerOutput.error)
    {
        /*auto errors = compilerOutput.error.split('\n');
        for(auto &error : errors)
        {
            auto data = error.split(':');
            if(data.size() == 6)
            {
                ProjectContext->error(data[4] + ":" + data[5], data[0] + ":" + data[1], data[2] + ", " + data[3]);
            }
        }*/
        ProjectContext->error(compilerOutput.error);
    }
    mutex.unlock();

    /*if(code != 0)
    {
        ProjectContext->error(fmt::format("Compilation error: {}", fmt::format("Compilation failed with code = {}", code)));
    }*/

    return error;
}
