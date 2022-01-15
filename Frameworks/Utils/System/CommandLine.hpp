#pragma once

#include <boost/program_options.hpp>

namespace System
{
    namespace CommandLineDetails
    {
        using namespace boost::program_options;
    }

    struct CommandLine
    {
        using NamedOptions = CommandLineDetails::options_description;
        using PositionalOptions = CommandLineDetails::positional_options_description;
        using ParsedOptions = CommandLineDetails::parsed_options;
        using Variables = CommandLineDetails::variables_map;

        int m_CountArguments = 0;
        const char** m_Arguments = nullptr;

        Array<NamedOptions> m_NamedOptions;
        Array<PositionalOptions> m_PositionalOptions;

        std::function<void(const String& UknownOption)> UnknownOptionHandler;

        CommandLine() = default;

        CommandLine(int argc, const char** argv, size_t CountNamedOptions = 1, size_t CountPositionalOptions = 0) :
            m_CountArguments(argc),
            m_Arguments(argv)
        {
            m_NamedOptions.resize(CountNamedOptions);
            m_PositionalOptions.resize(CountPositionalOptions);
        }

        template<typename Type>
        void AddNamedOption(Type& value, const char* name, const char* description, size_t index = ArrayUtils::InvalidIndex)
        {
            index = std::min(m_NamedOptions.size() - 1, index);
            m_NamedOptions[index].add_options()(name, CommandLineDetails::value<Type>(&value), description);
        }

        template<typename Type>
        void AddPositionalOption(Type& value, const char* name, const char* description, size_t max = ArrayUtils::InvalidIndex, size_t index = ArrayUtils::InvalidIndex)
        {
            index = std::min(m_NamedOptions.size() - 1, index);
            m_NamedOptions[index].add_options()(name, CommandLineDetails::value<Type>(&value), description);
            m_PositionalOptions[index].add(name, max);
        }

        Variables Parse()
        {
            auto parser = CommandLineDetails::command_line_parser(m_CountArguments, m_Arguments);

            for (const auto& option : m_NamedOptions)
            {
                parser.options(option);
            }

            for (const auto& option : m_PositionalOptions)
            {
                parser.positional(option);
            }

            auto result = parser.allow_unregistered().run();

            Variables variables;
            CommandLineDetails::store(result, variables);
            CommandLineDetails::notify(variables);

            if (UnknownOptionHandler)
            {
                for (const auto& variable : CommandLineDetails::collect_unrecognized(result.options, boost::program_options::exclude_positional))
                {
                    UnknownOptionHandler(variable);
                }
            }

            return variables;
        }
    };
}
