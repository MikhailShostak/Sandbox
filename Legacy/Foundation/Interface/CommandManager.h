#pragma once

#include "ADelegate.h"
#include "String.h"
//#include "Array<String>.h"
//#include "StringHashMap.h"

class CommandManager
{
public:
    Map<String, ADelegate<AError(const Array<String> &arguments)>> commands;
    ADelegate<void()> help;

    AError apply(int argc, const char *argv[], bool requireArguments = false)
    {
        String firstArgument(argv[1]);
        if ((argc < 2 && requireArguments) || firstArgument == "?" || firstArgument == "-h" || firstArgument == "-help")
        {
            if (help)
            {
                help();
            }
            return AError(-1, "Invalid Arguments");
        }

        for (int i = 0; i < argc; ++i)
        {
            Array<String> argumentAndValue;
            boost::split(argumentAndValue, String(argv[i]), boost::is_any_of("="));
            if (argumentAndValue.size() == 2)
            {
                auto it = commands.find(argumentAndValue[0]);
                if (it != commands.end())
                {
                    Array<String> values;
                    boost::split(values, argumentAndValue[1], boost::is_any_of(";"));
                    it->second(values);
                }
            }
        }

        return AError::getEmptyError();
    }
};
