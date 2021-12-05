#pragma once

#include "ALog.h"
#include "AAssert.h"
#include "String.h"
#include "AFile.h"

#include <iostream>

#include "AThread.h"

struct ALogOptions
{
    bool writeToFile = false;
    bool writeToOutput = true;
};

class ALogStream
{
    std::ostream &outputStream;
    const ALogOptions *logOptions;

    static Map<String, ALogOptions> &getLogOptions()
    {
        static Map<String, ALogOptions> logOptions;
        return logOptions;
    }

    ALogStream(std::ostream &stream):
        outputStream(stream)
    {

    }

    ~ALogStream()
    {
        outputStream.flush();
        if(&outputStream == &std::cout)
        {
            fflush(stdout);
        }
        else if(&outputStream == &std::cout)
        {
            fflush(stderr);
        }
    }

    static String &getFilePath()
    {
        static String filePath;
        return filePath;
    }

    static AFile &getFile()
    {
        static AFile file;
        if (!file.isOpen())
        {
            file.open(!getFilePath().empty() ? APath(getFilePath()) : APath(APath::applicationDirectory() + "log.txt"), AFileOpenMode::ReadBinary);
        }
        return file;
    }

    static AMutex &getMutex()
    {
        static AMutex m;
        return m;
    }

public:

    struct EndLine final {};

    static void setFilePath(const String &path)
    {
        getFilePath() = path;
    }

    static ALogStream &getLogStream(std::ostream &stream)
    {
        static ALogStream logStream(stream);
        return logStream;
    }

    const ALogOptions &getLogOptionsForCategory(const String &category) const
    {
        return getLogOptions()[category];
    }

    void setLogOptionsForCategory(const String &category, const ALogOptions &logOptions)
    {
        getLogOptions()[category] = logOptions;
    }

    ALogStream &getCategory(const String &category = String())
    {
        logOptions = &getLogOptionsForCategory(category);
        return *this;
    }

    template<typename ...Type>
    ALogStream &getCategory(const String &category, const char *format, const Type &...values)
    {
        logOptions = &getLogOptionsForCategory(category);
        AMutexLock lock(getMutex());
        writeWithoutBlock(fmt::format(format, values...));
        writeWithoutBlock(EndLine());
        return *this;
    }

    template<typename Type>
    ALogStream &operator <<(const Type &value)
    {
        AMutexLock lock(getMutex());
        writeWithoutBlock(value);
        return *this;
    }

private:
    template<typename Type>
    void writeWithoutBlock(const Type &value)
    {
        AAssert(logOptions, "Invalid log options");
        if (logOptions->writeToFile)
        {
            getFile() << value;
        }
        if (logOptions->writeToOutput)
        {
            outputStream << value;
        }
    }

    template<>
    void writeWithoutBlock<EndLine>(const EndLine &)
    {
        AAssert(logOptions, "Invalid log options");
        if (logOptions->writeToFile)
        {
            getFile() << "\r\n";
        }
        if (logOptions->writeToOutput)
        {
            outputStream << "\n";
        }
    }
};

#define ALogMessage ALogStream::getLogStream(std::cout).getCategory
#define ALogError ALogStream::getLogStream(std::cerr).getCategory
