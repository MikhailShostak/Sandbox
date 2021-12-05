#pragma once

#include <Data>
#include <System>

#include <LanguageFunctions.h>
/*
template<class CharT>
struct std::formatter<std::filesystem::path, CharT> : std::formatter<String, CharT>
{
    template<class FormatContext>
    auto format(const std::filesystem::path &path, FormatContext& context) {
        return std::formatter<String, CharT>::format(path.generic_string(), context);
    }
};

template<class CharT>
struct std::formatter<String, CharT> : std::formatter<String, CharT>
{
    template<class FormatContext>
    auto format(const String &str, FormatContext& context) {
        return std::formatter<String, CharT>::format(str, context);
    }
};

template<class T, class CharT>
struct std::formatter<Array<T>, CharT> : std::formatter<T, CharT>
{
    template<class FormatContext>
    auto format(const Array<T> &v, FormatContext& context) {
        String f;
        for(auto &i : v)
        {
            std::formatter<String, CharT>::format(str, context);
        }
        return f;
    }
};*/

enum ActionStatus
{
	Scheduled,
	Canceled,
	Started,
	Succeeded,
	Failed,
};

class CppToolchainOperation
{
public:

    inline auto Run(const String &command)
    {
        Log::Print(command);
        return OS::Process::Open(command);
    }

    TaskManager tm;

    template<typename T>
    static T &&registerTask(const String &title, T &&awaitable)
    {
        Log::Print(title);
        return std::forward<T>(awaitable);
    }
    ActionStatus Status = ActionStatus::Scheduled;

    auto IsStopped() { return Status == ActionStatus::Canceled || Status == ActionStatus::Failed; }
    auto IsFinished() { return IsStopped() || Status == ActionStatus::Succeeded; }

    BuildSystem::BuildingSettings Settings;

    OS::FS::Path FrameworkDirectory;

    OS::FS::Path CreatePCH;

    Array<OS::FS::Path> PCHEntries;
    Array<OS::FS::Path> PCHObjectFiles;

    Array<OS::FS::Path> Includes;

    Array<OS::FS::Path> SourceEntries;

    Array<OS::FS::Path> ObjectFiles;
    OS::FS::Path HeaderDirectory;
    OS::FS::Path BuildDirectory;
    OS::FS::Path ProductDirectory;
    String ProductName;

    bool UsePCH = false;

    auto RunWithFileArgs(const String &app, const String &args, const OS::FS::Path &outputFile)
    {
        String argsFile = outputFile.generic_string() + ".args";
        std::ofstream f(argsFile);
        if(!f)
        {
            Status = ActionStatus::Failed;
        }
        f << args;
        f.close();

        return Run(Str::Format("{} @{}", app, argsFile));
    }
    
    OS::FS::Path CompileFile(OS::FS::Path file, OS::FS::Path outputFile)
    {
        //TODO: do not start task at all
        if(IsStopped())
        {
            return outputFile;
        }
        
        Log::Print("[CompileFile] {} to {}", file, outputFile);
        //fmt::print("File: {}", content);
        //auto s1 = ranges::istream_view<char>(f);
        //std::istringstream sep{"\\\n"};
        //auto s2 = ranges::subrange<std::istreambuf_iterator<char>>(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
        //auto v1 = rngv::split(s2, '\n');
        //auto v2 = rngv::split(ranges::subrange<std::istreambuf_iterator<char>>(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()), "\\\n");
        //v1 | rngv::transform([](auto &rng) { return StringView(&*rng.begin(), ranges::distance(rng)); })
        /*for (const auto &i : content)
        {
            fmt::print("{}\r\n", i);
        }*/
        if (OS::FS::is_regular_file(outputFile))
        {
            auto OutputFileModificationTime = OS::FS::last_write_time(outputFile);
            Log::Print("[CompileFile] Dates: {} > {} {}", outputFile, file, NewerThanFile(OutputFileModificationTime, file));
            auto dep_file = OS::FS::Path(outputFile).replace_extension(".d");
            Log::Print("[CompileFile] Dependencies: {}", dep_file);
            //Log::Print("{}", NewerThanDependencies(OutputFileModificationTime, BuildDirectory / file.stem().replace_extension(".d")));
            if (NewerThanFile(OutputFileModificationTime, file) && NewerThanDependencies(OutputFileModificationTime, dep_file))
            {
                return outputFile;
            }
        }

        Array<OS::FS::Path> local_includes = Includes;

        for (const OS::FS::Path& src : SourceEntries)
        {
            local_includes.push_back(src);
            const auto &directories = ADirectory(src.generic_string().data()).findRecursively(String(), AFindFilter::AllDirectories);
            for(const auto &d : directories)
            {
                local_includes.push_back(d.path().toUnixPathString());
            }
        }

        String frameworks = join_paths_from_string(Settings.LinkageSettings.Frameworks, "-I" + FrameworkDirectory.generic_string() + "/", "/Interface");
        
        Array<String> frameworkList;
        boost::split(frameworkList, Settings.LinkageSettings.Frameworks, boost::is_any_of(";"));
        for(const auto &f : frameworkList)
        {
            OS::FS::Path pch_file = FrameworkDirectory / f / ("PCH/" + f + ".pch.hpp.gch");
            if(OS::FS::is_regular_file(pch_file))
            {
                frameworks.append(" -include-pch " + pch_file.generic_string());
            }
        }


        auto args = Str::Format("@{} {} {} {} -c {} -o {}",
            Settings.CompilationSettings.ArgumentFiles,
            join_paths(local_includes, "-I"),
            join_paths(PCHObjectFiles, "-include-pch "),
            frameworks,
            file,
            outputFile);

        auto process = RunWithFileArgs(Settings.CompilerSettings.Compiler, args, outputFile);
        process.wait();
        if(process.exit_code() != 0)
        {
            Status = ActionStatus::Failed;
        }

        return outputFile;
    }

    template<typename T>
    bool NewerThanFile(const T &time, const OS::FS::Path &file)
    {
        return time >= OS::FS::last_write_time(file);
    }

    template<typename T>
    bool NewerThanDependencies(const T &time, const OS::FS::Path &dependencyFile)
    {
        std::ifstream file(dependencyFile);
        String str = String(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        auto content = rngv::split(str, Str::CharRange(" \\\n  "));
        auto str_content = content | rngv::transform([](auto &&rng){ return String(&*rng.begin(), ranges::distance(rng)); }) | rngv::drop(1);
        for (const auto &s : str_content)
        {
            OS::FS::Path dependency = boost::replace_all_copy<String>(s | rngv::trim([](char c){ return std::isspace(c); }) | ranges::to<String>(), "\\ ", " ");
            if(!OS::FS::is_regular_file(dependency) || time < OS::FS::last_write_time(dependency))
            {
                return false;
            }
        }
        return true;
    }
    
    void CompileEntires(const Array<OS::FS::Path> &entries, Array<OS::FS::Path> &out, const String &extension, const String &outextension)
    {
        //TODO: do not start task at all
        if(IsStopped())
        {
            return;
        }

        if(!entries.size())
        {
            Log::Print("No source entires, nothing to compile...");
            Status = Failed;
            return;
        }

        //TODO: FIX ME
        /*Array<async<OS::FS::Path>> tasks;
        for (const OS::FS::Path &p : entries)
        {
            for(const auto &entry : OS::FS::RecursiveIterator(p))
            {
                const auto &path = entry.path();
                //Log::Print("{} {} {} {} {}", path, path.filename().generic_string(), extension, path.filename().generic_string().ends_with(extension), outextension);
                if(path.filename().generic_string().ends_with(extension))
                {
                    auto outputFile = BuildDirectory / path.filename().replace_extension(outextension);

                    OS::FS::Path dir = outputFile.parent_path();
                    Log::Print("Create Directory: {}", dir);
                    OS::FS::create_directories(dir);

                    tasks.emplace_back(registerTask(Str::Format("Compile: {}", path.filename()), CompileFile(path, outputFile)));
                }
            }
        }
        if(!tasks.size())
        {
            Log::Print("No source files found, nothing to compile...");
            //Status = Failed;
            return;
        }

        out = await tm.AsyncWorkers.dispatch(std::move(tasks));*/
    }

    void CopyHeaders()
    {
        if(HeaderDirectory.empty())
        {
            return;
        }

        Log::Print("Entries {}", Includes);
        for (const OS::FS::Path &p : Includes)
        {
            for(const auto &entry : OS::FS::RecursiveIterator(p))
            {
                const auto &path = entry.path();
                auto filename = path.filename().generic_string();
                if(rng::ends_with(filename, ".h") || rng::ends_with(filename, ".hpp") || rng::ends_with(filename, ".inl") || rng::ends_with(filename, ".gch"))
                {
                    OS::FS::path relative_path = OS::FS::relative(path, p);
                    
                    Log::Print("Header {} {}", HeaderDirectory, relative_path);
                    OS::FS::path destination = HeaderDirectory / relative_path;
                    if(OS::FS::is_regular_file(destination) && !NewerThanFile(OS::FS::last_write_time(path), destination))
                    {
                        continue;
                    }
                    
                    OS::FS::Path dir = destination.parent_path();
                    OS::FS::create_directories(dir);

                    Log::Print("Copy: {} {}", path, destination);
                    OS::FS::copy(path, destination, OS::FS::copy_options::update_existing | OS::FS::copy_options::recursive);
                }
            }
        }
        return;
    }

    bool check_files_equal(const OS::FS::path& p1, const OS::FS::path& p2)
    {
        std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
        std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

        if (f1.fail() || f2.fail()) {
            return false; //file problem
        }

        if (f1.tellg() != f2.tellg()) {
            return false; //size mismatch
        }

        //seek back to beginning and use std::equal to compare contents
        f1.seekg(0, std::ifstream::beg);
        f2.seekg(0, std::ifstream::beg);
        return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                            std::istreambuf_iterator<char>(),
                            std::istreambuf_iterator<char>(f2.rdbuf()));
    }

    void CreatePCHTask()
    {
        #define PCH_EXTENSION ".pch.hpp"
        OS::FS::path pch = HeaderDirectory / (ProductName + PCH_EXTENSION);
        OS::FS::path pch_temp = HeaderDirectory / (ProductName + ".pch.hpp.temp");

        std::ofstream f(pch_temp);
        if (!f)
        {
            Status = ActionStatus::Failed;
            return;
        }

        f << "#pragma once\n\n";

        Array<String> frameworkList;
        boost::split(frameworkList, Settings.LinkageSettings.Frameworks, boost::is_any_of(";"));
        for(const auto &framework : frameworkList)
        {
            f << "#include <" << (framework + PCH_EXTENSION) << ">\n";
        }
        f << "\n";

        for(const auto &entry : OS::FS::RecursiveIterator(HeaderDirectory))
        {
            const auto &path = entry.path();
            auto filename = path.filename().generic_string();
            if((rng::ends_with(filename, ".h") || rng::ends_with(filename, ".hpp")) && !rng::ends_with(filename, PCH_EXTENSION))
            {
                OS::FS::path relative_path = OS::FS::relative(path, HeaderDirectory);

                f << "#include \"" << relative_path.generic_string() << "\"\n";
            }
        }
        f.close();

        if(check_files_equal(pch_temp, pch))
        {
            OS::FS::remove(pch_temp);
        }
        else
        {
            OS::FS::remove(pch);
            OS::FS::rename(pch_temp, pch);
        }

        return;
        #undef PCH_EXTENSION
    }

    OS::FS::Path GetObjectFilesWildcard() const { return BuildDirectory / ("*." + Settings.FilesSettings.ObjectFileName); }
    OS::FS::Path GetApplicationOutputFile() const { return ProductDirectory / (ProductName + "." + Settings.FilesSettings.ApplicationFileName); }
    OS::FS::Path GetDynamicLibraryOutputFile() const { return ProductDirectory / (ProductName + "." + Settings.FilesSettings.DynamicLibraryFileName); }
    OS::FS::Path GetStaticLibraryOutputFile() const { return ProductDirectory / (ProductName + "." + Settings.FilesSettings.StaticLibraryFileName); }

    String IsOutdated(const OS::FS::path &outputFile, const Array<OS::FS::path> &additionalDependencies)
    {
        if (!OS::FS::is_regular_file(outputFile))
        {
            return Str::Format("{} doesn't exist", outputFile);
        }

        auto OutputFileModificationTime = OS::FS::last_write_time(outputFile);
        for(const auto &f : additionalDependencies)
        {
            if(OS::FS::last_write_time(f) > OutputFileModificationTime)
            {
                return Str::Format("{} is newer", f);
            }
        }
        for(const auto &f : ObjectFiles)
        {
            if(OS::FS::last_write_time(f) > OutputFileModificationTime)
            {
                return Str::Format("{} is newer", f);
            }
        }
        return String();
    }

    template<typename Functor>
    void Finalize(const OS::FS::path &outputFile, const Array<OS::FS::path> &additionalDependencies, Functor &&f)
    {
        //TODO: do not start task at all
        if(IsStopped())
        {
            return;
        }

        Log::Print("{}", ObjectFiles);
        

        if(!ObjectFiles.size())
        {
            Log::Print("No object files, nothing to do...");
            return;
        }

        String outdated = IsOutdated(outputFile, additionalDependencies);
        if (!outdated.empty())
        {
            OS::FS::create_directories(outputFile.parent_path());
            Log::Print(outdated);
            f();
        }
    }

    template<typename T>
    String join_paths(const T &paths, const String &arg = String())
    {
        Array<String> v = rngv::transform(paths, [&](const auto &v){ return !arg.empty() ? arg + v.generic_string() : v.generic_string(); }) | rng::to_vector;
        return rngv::join(v, ' ') | rng::to<String>;
    };

    template<typename T>
    String join_paths_from_string(const T &paths, const String &prefix = String(), const String &sufix = String())
    {
        Array<String> data;
        Array<String> p;
        boost::split(p, paths, boost::is_any_of(";"));
        for(const auto &v : p)
        {
            data.push_back(prefix + v + sufix);
        }
        
        return rngv::join(data, ' ') | rng::to<String>;
    };

    String GetFrameworks() const
    {
        Array<String> frameworkList;
        boost::split(frameworkList, Settings.LinkageSettings.Frameworks, boost::is_any_of(";"));
        String frameworks;
        for(const auto &f : frameworkList)
        {
            OS::FS::Path library_file = FrameworkDirectory / f / ("Library/" + f + ".lib");
            if(OS::FS::is_regular_file(library_file))
            {
                frameworks.append("-L" + library_file.parent_path().generic_string() + " -l" + f + " ");
            }
        }
        return frameworks;
    }

    Array<OS::FS::Path> GetFrameworkLibraries() const
    {
        Array<String> frameworkList;
        boost::split(frameworkList, Settings.LinkageSettings.Frameworks, boost::is_any_of(";"));
        Array<OS::FS::Path> paths;
        for(const auto &f : frameworkList)
        {
            OS::FS::Path library_file = FrameworkDirectory / f / ("Library/" + f + ".lib");
            if(OS::FS::is_regular_file(library_file))
            {
                paths.push_back(library_file);
            }
        }
        return paths;
    }

    void LinkApp()
    {
        Finalize(GetApplicationOutputFile(), GetFrameworkLibraries(), [this](){
            auto outputFile = GetApplicationOutputFile();
            auto args = Str::Format("{} @{} {} {} {} -o {}",
                GetFrameworks(),
                Settings.LinkageSettings.ArgumentFiles,
                Settings.LinkerSettings.ApplicationFlags,
                Settings.LinkerSettings.Flags,
                join_paths(ObjectFiles),
                outputFile
            );
            RunWithFileArgs(Settings.LinkerSettings.Linker, args, outputFile).wait();
        });
        return;
    }

    void LinkLibrary()
    {
        Finalize(GetDynamicLibraryOutputFile(), GetFrameworkLibraries(), [this](){
            auto outputFile = GetDynamicLibraryOutputFile();
            auto args = Str::Format("{} @{} {} {} {} -o {}",
                GetFrameworks(),
                Settings.LinkageSettings.ArgumentFiles,
                Settings.LinkerSettings.LibraryFlags,
                Settings.LinkerSettings.Flags,
                join_paths(ObjectFiles),
                outputFile
            );
            RunWithFileArgs(Settings.LinkerSettings.Linker, args, outputFile).wait();
        });
        return;
    }

    void Archive()
    {
        Finalize(GetStaticLibraryOutputFile(), {}, [this](){
            auto outputFile = GetStaticLibraryOutputFile();
            auto args = Str::Format("rc {} {}",
                outputFile,
                join_paths(ObjectFiles)
            );
            RunWithFileArgs(Settings.ArchiverSettings.Archiver, args, outputFile).wait();
        });
        return;
    }

    void CompileHeaders()
    {
        if(!CreatePCH.empty())
        {
            //co_await registerTask("Create *.pch.hpp", CreatePCHTask());
        }
        if(!PCHEntries.empty())
        {
            //co_await registerTask("Compile *.pch.hpp Headers", CompileEntires(PCHEntries, PCHObjectFiles, ".pch.hpp", ".hpp.gch"));
        }
    }

    void Compile()
    {
//         co_await registerTask("Compile *.c Sources", CompileEntires(SourceEntries, ObjectFiles, ".c", "." + Settings.FilesSettings.ObjectFileName));
//         co_await registerTask("Compile *.cc Sources", CompileEntires(SourceEntries, ObjectFiles, ".cc", "." + Settings.FilesSettings.ObjectFileName));
//         co_await registerTask("Compile *.cpp Sources", CompileEntires(SourceEntries, ObjectFiles, ".cpp", "." + Settings.FilesSettings.ObjectFileName));
    }

    void CreateApplication()
    {
//         co_await registerTask("Compile Headers", CompileHeaders());
//         co_await Compile();
//         co_await registerTask("Create Application", LinkApp());
    }

    void CreateDynamicLibrary()
    {
//         co_await registerTask("Copy Headers", CopyHeaders());
//         co_await registerTask("Compile Headers", CompileHeaders());
//         co_await Compile();
//         co_await registerTask("Create Dynamic Library", LinkLibrary());
    }

    void CreateStaticLibrary()
    {
//         co_await registerTask("Copy Headers", CopyHeaders());
//         co_await registerTask("Compile Headers", CompileHeaders());
//         co_await Compile();
//         co_await registerTask("Create Static Library", Archive());
    }
};
