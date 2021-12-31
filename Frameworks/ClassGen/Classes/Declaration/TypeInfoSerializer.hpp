#pragma once

namespace ClassGen
{


inline std::string writeRecursively(const ClassGen::TypeInfo &value)
{
    std::string result = value.Name;
    if (!value.Parameters.empty())
    {
        result.append("<");
        result.append(boost::join(value.Parameters | ranges::views::transform([](auto &t) { return writeRecursively(t); }), ", "));
        result.append(">");
    }
    return result;
}

inline std::string writeRecursivelyResolved(const ClassGen::TypeInfo &value)
{
    std::string result = boost::replace_all_copy(value.Name, ".", "::");
    if (!value.Parameters.empty())
    {
        result.append("<");
        result.append(boost::join(value.Parameters | ranges::views::transform([](auto &t) { return writeRecursivelyResolved(t); }), ", "));
        result.append(">");
    }
    return result;
}

inline void readRecursively(const std::string &value, ClassGen::TypeInfo &output)
{
    struct TypeParser
    {
        std::string data;
        size_t begin = 0;
        size_t it = 0;
        size_t end = 0;

        TypeParser() = default;

        TypeParser(const std::string &type) :
            data(type),
            end(data.size())
        {

        }

        void parseParameters(ClassGen::TypeInfo &type)
        {
            type.Parameters.resize(type.Parameters.size() + 1);
            while (it != end)
            {
                type.Parameters[type.Parameters.size() - 1] = parseType();
                auto c = data[it];
                switch (c)
                {
                case ',':
                    type.Parameters.resize(type.Parameters.size() + 1);
                    ++it;
                    break;
                case '>':
                    ++it;
                    return;
                default:
                    return;
                }
            }

            //TODO: Unexpected end
            return;
        }

        ClassGen::TypeInfo parseType()
        {
            ClassGen::TypeInfo t;
            while (it != end)
            {
                auto c = data[it];
                switch (c)
                {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    ++it;
                    break;
                case '<':
                    ++it;
                    parseParameters(t);
                    return t;
                case '>':
                case ',':
                    return t;
                default:
                    t.Name.push_back(c);
                    ++it;
                    break;
                }
            }
            return t;
        }
    };

    output = TypeParser(value).parseType();
}

}

namespace Serialization
{

template<>
struct Serializer<InputValue, ClassGen::TypeInfo>
{
    template<typename InputValue, typename ValueType>
    static void Write(InputValue &&data, ValueType &&value)
    {
        std::string v;
        data & v;
        ClassGen::readRecursively(v, value);
    }
};

template<>
struct Serializer<OutputValue, ClassGen::TypeInfo>
{
    template<typename OutputValue, typename ValueType>
    static void Write(OutputValue &&data, ValueType &&value)
    {
        data & ClassGen::writeRecursively(value);
    }
};

}
