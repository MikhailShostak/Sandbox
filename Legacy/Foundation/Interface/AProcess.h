#pragma once

#include "AMeta.h"

#include "String.h"
#include "AThread.h"
#include "APathInfo.h"
#include "ADelegate.h"
#include "ALog.h"
#include "AError.h"

#if APlatformWindowsDesktop
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#else
#   include <fcntl.h>
#endif

#if APlatformWindowsDesktop
using APipeHandle = HANDLE;
#else
using APipeHandle = int;
#endif

class APipe
{

    APipeHandle handles[2] = {};

public:

    APipe()
    {
#if APlatformWindowsDesktop
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;

        CreatePipe(&handles[0], &handles[1], &saAttr, 1024);
#else
        pipe(handles, 1024, _O_BINARY);
#endif
    }

    virtual ~APipe()
    {
        if(handles[0])
        {
#if APlatformWindowsDesktop
            CloseHandle(handles[0]);
#else
            close(handles[0]);
#endif
        }
        if(handles[1])
        {
#if APlatformWindowsDesktop
            CloseHandle(handles[1]);
#else
            close(handles[1]);
#endif
        }
    }

    APipeHandle getOutputHandle() const
    {
        return handles[0];
    }


    APipeHandle getInputHandle() const
    {
        return handles[1];
    }

    virtual void close()
    {
        closeInputHandle();
        closeOutputHandle();
    }

protected:

    void closeOutputHandle()
    {
        if(handles[0])
        {
#if APlatformWindowsDesktop
            CloseHandle(handles[0]);
#else
            close(handles[0]);
#endif
            handles[0] = 0;
        }
    }

    void closeInputHandle()
    {
        if(handles[1])
        {
#if APlatformWindowsDesktop
            CloseHandle(handles[1]);
#else
            close(handles[1]);
#endif
            handles[1] = 0;
        }
    }

};

class AAsynchronousPipe : public APipe
{

    AThread thread;

    ADelegate<void(uint8_t *buffer, size_t size)> delegate;

public:

    AAsynchronousPipe():
        APipe(),
        thread(&AAsynchronousPipe::processPipe, this)
    {

    }

    ~AAsynchronousPipe()
    {
        closeAndWait();
    }

    ADelegate<void(uint8_t *buffer, size_t size)> getDelegate() const
    {
        return this->delegate;
    }

    void setDelegate(const ADelegate<void(uint8_t *buffer, size_t size)> &delegate)
    {
        this->delegate = delegate;
    }

    void close() override
    {
        closeAndWait();
    }

private:

    void closeAndWait()
    {
        closeInputHandle();
        thread.join();
        closeOutputHandle();
    }

    void processPipe()
    {
        uint8_t buffer[1024]; //TODO: Replace with StaticArray
#if APlatformWindowsDesktop
        DWORD bytesReaded;
#else
        size_t bytesReaded = 0;
#endif
        while(getInputHandle())
        {
#if APlatformWindowsDesktop
            while(ReadFile(getOutputHandle(), buffer, 1024, &bytesReaded, NULL) && bytesReaded > 0)
#else
            while((bytesReaded = read(getOutputHandle(), buffer, 1024)) > 0)
#endif
            {
                if(delegate)
                {
                    delegate(buffer, bytesReaded);
                }
            }
        }
    }

};

class AProcessObserver
{
public:

    virtual void onOutputMessage(uint8_t *buffer, size_t size) = 0;
    virtual void onErrorMessage(uint8_t *buffer, size_t size) = 0;

};

class AProcess final
{

    std::thread thread;
    APath path;
    Array<String> arguments;
    bool running = false;

    AAsynchronousPipe outputPipe;
    AAsynchronousPipe errorPipe;

    Array<AProcessObserver *> observers;

public:

    enum AProcessError
    {
        ExecutableNotFound,
        ProcessWasCompletedWithError,
    };

    AProcess(const APath &path = APath(), const Array<String> &arguments = Array<String>()):
        path(path),
        arguments(arguments)
    {
        outputPipe.setDelegate([this](uint8_t *buffer, size_t size){
            for(auto &observer : observers)
            {
                observer->onOutputMessage(buffer, size);
            }
        });
        errorPipe.setDelegate([this](uint8_t *buffer, size_t size){
            for(auto &observer : observers)
            {
                observer->onErrorMessage(buffer, size);
            }
        });
    }

    ~AProcess() { }

    String getObjectDescription() const
    {
        return fmt::format("AProcess({} [{}])", path, Str::Join(arguments, ", "));
    }

    const Array<AProcessObserver *> &getObservers() const
    {
        return observers;
    }

    void addObserver(AProcessObserver *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(AProcessObserver *observer)
    {
        ArrayUtils::Remove(observers, observer);
    }

    const APath &getPath() const { return this->path; }
    void setPath(const String &path) { this->path = path; }

    const Array<String> &getArguments() const { return this->arguments; }
    void setArguments(const Array<String> &arguments) { this->arguments = arguments; }

    bool isRunning() const { return this->running; }

    AError execute(const ADelegate<void(const AError &error)> &completionDelegate = ADelegate<void(const AError &error)>());
    void run(const ADelegate<void(const AError &error)> &completionDelegate = ADelegate<void(const AError &error)>());

    bool isJoinable() const { return this->thread.joinable(); }
    void join() { this->thread.join(); }
    void deatach() { this->thread.detach(); }

};

#include "APlatform.h"
#if APlatformWindowsDesktop
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#else
#   include <unistd.h>
#   include <sys/wait.h>
#endif

#include <iostream>
#include <stdio.h>

inline AError AProcess::execute(const ADelegate<void(const AError &error)> &completionDelegate)
{
#if APlatformWindowsDesktop
    APath executable = path;

    if(executable.extension().empty())
    {
        executable.setExtension("exe");
    }

    String fullpath;
    if(executable.isRelative())
    {
        APathInfo info = APathInfo::getFromRelativePath(executable);
        if (!info.isExists())
        {
            return AError(ExecutableNotFound, fmt::format("Executable at {} was not found", path));
        }
        fullpath = info.path().toString();
    }
    else
    {
        fullpath = executable.toString();
    }

    String argv;
    static const char ArgumentQuotes = '"';
    static const char ArgumentSeparator = ' ';
    if(executable.extension() == "bat")
    {
        static const char *BatchArgumentQuotes = "^\"";

        argv.append("/C ");

        argv.push_back(ArgumentQuotes);

        argv.append(BatchArgumentQuotes);
        argv.append(fullpath);
        argv.append(BatchArgumentQuotes);

        for(auto it = arguments.begin(); it != arguments.end(); ++it)
        {
            argv.push_back(ArgumentSeparator);
            argv.append(BatchArgumentQuotes);
            argv.append(*it);
            argv.append(BatchArgumentQuotes);
        }
        argv.push_back(ArgumentQuotes);

        fullpath = "C:\\Windows\\System32\\cmd.exe";
    }
    else
    {
        auto it = arguments.begin();
        if(it != arguments.end())
        {
            argv.push_back(ArgumentQuotes);
            argv.append(*it);
            argv.push_back(ArgumentQuotes);
            ++it;
            while(it != arguments.end())
            {
                argv.push_back(ArgumentSeparator);
                argv.push_back(ArgumentQuotes);
                argv.append(*it);
                argv.push_back(ArgumentQuotes);
                ++it;
            }
        }
    }

    if(argv.empty())
    {
        argv = "\"" + fullpath + "\"";
    }
    else
    {
        argv = "\"" + fullpath + "\" " + argv;
    }

    APipe inputPipe;

    STARTUPINFOA startupInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION processInformation;
    startupInfo.hStdInput = inputPipe.getOutputHandle();//HANDLE(_get_osfhandle(inputPipe.getOutputHandle()));
    startupInfo.hStdOutput = outputPipe.getInputHandle();//HANDLE(_get_osfhandle(outputPipe.getInputHandle()));
    startupInfo.hStdError = errorPipe.getInputHandle();//HANDLE(_get_osfhandle(errorPipe.getInputHandle()));
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;

    DWORD errorCode = 0;
    if(CreateProcessA(nullptr, argv.data(), nullptr, nullptr, true, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInformation))
    {
        errorCode = WaitForSingleObject(processInformation.hProcess, INFINITE);
    }
    GetExitCodeProcess(processInformation.hProcess, &errorCode);

    CloseHandle(processInformation.hThread);
    CloseHandle(processInformation.hProcess);

    AError error = errorCode == 0 ? AError::getEmptyError() : AError(ProcessWasCompletedWithError, fmt::format("Process exited with code = {0:#x}", errorCode));
    if(completionDelegate)
    {
        completionDelegate(error);
    }

    return error;

#else

    /*char **argv = new char *[arguments.size() + 2];
    argv[arguments.size() + 1] = nullptr;

    std::string string = path.toUtf8();
    argv[0] = (char*)malloc(string.size() + 1);
    memcpy(argv[0], string.data(), string.size() + 1);

    StringList::SizeType i = 1;
    for(const String &argument : arguments)
    {
        std::string string = argument.toUtf8();
        argv[i] = (char*)malloc(string.size() + 1);
        memcpy(argv[i], string.data(), string.size() + 1);
        ++i;
    }

    pid_t pid = fork();
    switch(pid)
    {
    case -1:
        exit(1);
    case 0:
        execvp(argv[0], argv);
        exit(1);
    default:
        int status = 0;
        do
        {
            waitpid(pid, &status, 0);
        } while (!WIFEXITED(status));
        for(i = 0; i < arguments.size() + 1; ++i)
            free(argv[i]);
        return WEXITSTATUS(status);
    }*/

    String fullpath;
    if(path.isRelative())
    {
        bool missing = true;
        Array<String> paths = String(std::getenv("PATH")).split(':');
        for(const String &p : paths)
        {
            fullpath = p + APathSeparator + path;
            if(APathInfo(fullpath).isExists())
            {
                missing = false;
                break;
            }
        }
        if(missing)
            return 1;
    }
    else
        fullpath = path;

    String argv = fullpath.quote();
    for(const String &argument : arguments)
        argv.append(" \"" + argument + '"');

    FILE *f;
    if(!(f = popen(argv.toUtf8().data(), "r")))
        return 1;
    /*if(receiver)
    {
        char buffer[512];
        while(fgets(buffer, sizeof(buffer), f) != 0)
            receiver(buffer);
    }*/
    return pclose(f);
#endif
}

inline void AProcess::run(const ADelegate<void(const AError &error)> &completionDelegate)
{
    if(isRunning())
    {
        return;
    }

    this->thread = std::thread((int(AProcess::*)(const ADelegate<void(const AError &error)> &))&AProcess::execute, this, completionDelegate);
}

#include <iostream>

inline std::ostream& operator<<(std::ostream& stream, const AProcess &process)
{
    stream << process.getObjectDescription();
    return stream;
}
