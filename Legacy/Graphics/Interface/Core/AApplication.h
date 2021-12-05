#pragma once

#include <Foundation>

#include "APlatformInegration.h"

/*class AApplication final : public APlatformApplicationDelegate
{

    APlatformApplication *platformApplication = nullptr;
    Array<String> arguments;

public:

    AApplication(int argc, char **argv)
    {
        for(int i = 0; i < argc; ++i)
        {
            arguments.append(argv[i]);
        }

        platformApplication = APlatformInstance()->createApplication(this);
    }

    ~AApplication()
    {
        delete platformApplication;
    }

    const Array<String> &getArguments() const override
    {
        return arguments;
    }

    int run()
    {
        return platformApplication->run();
    }

};*/
