#include <Class.gen.hpp>

void ProcessFile(const System::Path& path)
{
    fmt::print("Compile: {}\n", path);
    ClassGen::Compile(path);
}

void ProcessPath(const System::Path &path)
{
    if (System::IsRegularFile(path))
    {
        ProcessFile(path);
    }
    else if (System::IsDirectory(path))
    {
        for (const auto& entry : System::RecursiveDirectoryIterator(path))
        {
            const auto& path = entry.path();
            if (path.extension() == ".cg")
            {
                ProcessFile(path);
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    String help = "Usage: ClassGenCompiler <files or directories>";
    System::CommandLine cmd{ argc, argv, 1, 1 };
    cmd.UnknownOptionHandler = [](const String& option) {
        fmt::print("Warning: Unknown option \"{}\"\n", option);
    };

    Array<System::Path> paths;
    cmd.AddPositionalOption(paths, "input", "Input files or directories to compile");

    auto variables = cmd.Parse();
    if (!variables.count("input"))
    {
        fmt::print("{}\n", help);
        return 1;
    }

    ClassGen::LoadExtensions();

    for (const auto &path : paths)
    {
        ProcessPath(path);
    }

    return 0;
}
