#pragma once

#include <Foundation>

class Console : public ASingleton<Console>
{
    Map<String, std::function<void(const Array<String> &arguments)>> observers;
    Array<String> history;
    mutable size_t currentCommand = 0;
public:
    void addCommand(const String &command, const std::function<void(const Array<String> &arguments)> &callback) { observers.insert({ command, callback }); }
    void removeCommand(const String &command) { observers.erase(command); }
    void removeCommands() { observers.clear(); }

    const Map<String, std::function<void(const Array<String> &arguments)>> &getCommands() const
    {
        return observers;
    }

    const String &getPreviousCommand() const
    {
        if (currentCommand > 0)
        {
            return history[--currentCommand];
        }
        return String();
    }

    const String &getNextCommand() const
    {
        if (currentCommand < history.size())
        {
            return history[currentCommand++];
        }
        return String();
    }

    void applyCommand(const String &command)
    {
        if (command.empty())
        {
            return;
        }

        history.push_back(command);
        currentCommand = history.size();

        Array<String> arguments;
        boost::split(arguments, command, boost::is_any_of(" "));
        auto observer = observers.find(arguments.front());
        if (observer != observers.end())
        {
            arguments.erase(arguments.begin());
            observer->second(arguments);
        }
    }
};

template<typename Type>
class ConsoleVariable
{
    Type value;
public:
    ConsoleVariable(const Type &defaultValue, const String &name):value(defaultValue) { Console::getInstance().addCommand(name, std::bind(&ConsoleVariable::processArguments, this, std::placeholders::_1)); }
    ConsoleVariable(Type &&defaultValue, const String &name):value(std::move(defaultValue)) { Console::getInstance().addCommand(name, std::bind(&ConsoleVariable::processArguments, this, std::placeholders::_1)); }
    
    operator Type() const { return value; }
    ConsoleVariable & operator =(const Type &value) { this->value = value; return *this; }
    ConsoleVariable & operator =(Type &&value) { this->value = std::move(value); return *this; }

    void processArguments(const Array<String> &arguments)
    {
        if (arguments.empty())
        {
            return;
        }

        if constexpr (std::is_same_v<Type, bool>)
        {
            value = arguments.front() == "1";
        }
        else if constexpr (std::is_same_v<Type, int> || std::is_same_v<Type, unsigned int>)
        {
            value = std::stoi(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, long>)
        {
            value = std::stol(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, unsigned long>)
        {
            value = std::stoul(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, long long>)
        {
            value = std::stoll(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, unsigned long long>)
        {
            value = std::stoull(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, float>)
        {
            value = std::stof(arguments.front());
        }
        else if constexpr (std::is_same_v<Type, double>)
        {
            value = std::stod(arguments.front());
        }
    }
};
