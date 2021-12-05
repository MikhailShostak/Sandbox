#pragma once

#include "AError.h"
#include "AMemory.h"

class AApplication;

class ApplicationComponent
{
public:

    virtual void onApplicationLoad(const AApplication& application) {}
    virtual void onApplicationStart(const AApplication &application) {}
    virtual void onApplicationFinish(const AApplication& application) {}
    virtual void onApplicationUnload(const AApplication& application) {}

    virtual bool shouldUpdate() { return false; }
    virtual void onUpdate(const AApplication &application) {}

    virtual ~ApplicationComponent() {}

};

class AApplication
{
    Array<String> arguments;
public:

    Array<SharedReference<ApplicationComponent>> components;

    const Array<String> &getArguments() const
    {
        return arguments;
    }

    void setArguments(const Array<String> &arguments)
    {
        this->arguments = arguments;
    }

    void setArguments(Array<String> &&arguments)
    {
        this->arguments = std::move(arguments);
    }

    void setArguments(int argc, char *argv[])
    {
        for(int i = 0; i < argc; ++i)
        {
            arguments.push_back(argv[i]);
        }
    }

    virtual AError execute() = 0;
    virtual void stop(const AError &error = AError::getEmptyError()) = 0;

};
