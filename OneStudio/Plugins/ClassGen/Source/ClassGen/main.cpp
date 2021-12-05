#include <Data>

#include <ClassGenLibrary>

SharedReference<LegacyClassGen::BaseCGType> loadFile(const APath &path, const String &package = String())
{
    if (package)
    {
        ALogMessage("", "Load: [%s] %s", package, path);
    }
    else
    {
        ALogMessage("", "Load: %s", path);
    }

    SharedReference<LegacyClassGen::BaseCGType> type = LegacyClassGen::ClassManager::getInstance().load(path, package);
    if (!type || !type->root.nodes && !type->data)
    {
        ALogMessage("", "Warning: Empty or incorrect XML/JSON file\r\nNothing to do for %s", path);
        return nullptr;
    }

    return type;
}

bool processFile(const APath &path, const String &package = String())
{
    if (SharedReference<LegacyClassGen::BaseCGType> type = loadFile(path, package))
    {
        ALogMessage("", "Process: %s", path);
        type->generate();
        return true;
    }

    return false;
}

AError importFiles(const Array<APathInfo> &files, const String &package = String())
{
    for (const auto &file : files)
    {
        if (!loadFile(file.path(), package))
        {
            return AError(-1, fmt::format("Failed to load file: {}", file.path()));
        }
    }

    return AError::getEmptyError();
}

AError importPath(const APathInfo &pathInfo, const String &package = String())
{
    if (!pathInfo.isExists())
    {
        return AError(-1, fmt::format("Path doesn't exist: {}", pathInfo.path()));
    }

    if (pathInfo.isDirectory())
    {
        const auto &files = ADirectory(pathInfo).findRecursively("cg", AFindFilter::AllFiles);
        if (AError error = importFiles(files, package))
        {
            return error;
        }
    }
    else
    {
        if (!loadFile(pathInfo.path(), package))
        {
            return AError(-1, fmt::format("Failed to load file: {}", pathInfo.path()));
        }
    }

    return AError::getEmptyError();
}

int main(int argc, const char *argv[])
{
    //UI::PropertyAttributes attributes;
    CommandManager cm;
    bool wait = false;
    cm.commands.insert("-Wait", [&wait](const Array<String> &arguments) {
        wait = true;
        return AError::getEmptyError();
    });
    cm.commands.insert("-Force", [](const Array<String> &arguments) {
        LegacyClassGen::GenerationSettings::getInstance().forceGenerate = true;
        return AError::getEmptyError();
    });
    cm.commands.insert("-FilesDirectory", [](const Array<String> &arguments) {
        if (arguments.size() != 2)
        {
            return AError(-1, fmt::format("Failed to add files directory"));
        }

        LegacyClassGen::GenerationSettings::getInstance().setFilesDirectory(arguments[0], arguments[1]);
        return AError::getEmptyError();
    });
    cm.commands.insert("-Import", [&](const Array<String> &arguments) {
        String argument = arguments[0];
        {
            APath path(argument);
            return importPath(path, path.name());
        }
    });
    cm.commands.insert("-ImportAs", [&](const Array<String> &arguments) {
        String argument = arguments[0];
        {
            APath path(argument);
            return importPath(path, arguments[1]);
        }
    });
    cm.commands.insert("-Package", [&](const Array<String> &arguments) {
        if (arguments.size() != 2)
        {
            return AError(-1, fmt::format("Failed to set package"));
        }
        LegacyClassGen::GenerationSettings::getInstance().currentPackage = arguments[0];        
    });
    cm.commands.insert("-Source", [&](const Array<String> &arguments) {
        //for (const String &argument : arguments)
        String argument = arguments[0];
        {
            APathInfo pathInfo(argument);
            if (pathInfo.isDirectory())
            {
                String package = pathInfo.name();
                LegacyClassGen::GenerationSettings::getInstance().currentPackage = package;
                const auto &files = ADirectory(pathInfo).findRecursively("cg", AFindFilter::AllFiles);
                if (AError error = importFiles(files, package))
                {
                    return error;
                }

                for (const auto &file : files)
                {
                    if (!processFile(file.path(), package))
                    {
                        return AError(-1, fmt::format("Failed to generate file at {}", file.path()));
                    }
                }

                LegacyClassGen::ClassManager::getInstance().processTypes(pathInfo.path());
            }
            else
            {
                if (!processFile(pathInfo.path(), LegacyClassGen::GenerationSettings::getInstance().currentPackage))
                {
                    return AError(-1, fmt::format("Failed to generate file at {}", pathInfo.path()));
                }
            }
        }

        return AError::getEmptyError();
    });
    cm.apply(argc, argv, true);

    //ClassManager::getInstance().execute();
    if (wait)
    {
        system("pause");
    }
    return 0;
}
