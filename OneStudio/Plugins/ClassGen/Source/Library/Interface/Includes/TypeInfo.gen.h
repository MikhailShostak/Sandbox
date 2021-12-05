#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include <MetaObjectSerializationHelper.h>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct TypeInfo : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TypeInfo This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Name;
    Array<LegacyClassGen::TypeInfo> Parameters;
public:
    TypeInfo();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

inline String writeRecursively(const LegacyClassGen::TypeInfo& value)
{
    String parameters = "<";
    for (const LegacyClassGen::TypeInfo& t : value.Parameters)
    {
        parameters.append(writeRecursively(t) + ",");
    }

    if (parameters.back() == ',')
    {
        parameters[parameters.size() - 1] = '>';
        return value.Name + parameters;
    }

    return value.Name;
}

inline String writeRecursivelyResolved(const LegacyClassGen::TypeInfo& value)
{
    String parameters = "<";
    for (const LegacyClassGen::TypeInfo& t : value.Parameters)
    {
        parameters.append(writeRecursivelyResolved(t) + ",");
    }

    if (parameters.back() == ',')
    {
        parameters[parameters.size() - 1] = '>';
        return boost::replace_all_copy(value.Name, ".", "::") + parameters;
    }

    return boost::replace_all_copy(value.Name, ".", "::");
}

inline void readRecursively(const String& value, LegacyClassGen::TypeInfo& output)
{
    struct TypeParser
    {
        String data;
        size_t begin = 0;
        size_t it = 0;
        size_t end = 0;
        
        TypeParser() = default;

        TypeParser(const String &type):
            data(type),
            end(data.size())
        {
            
        }
        
        void parseParameters(LegacyClassGen::TypeInfo &type)
        {
            type.Parameters.resize(type.Parameters.size() + 1);
            while(it != end)
            {
                type.Parameters[type.Parameters.size() - 1] = parseType();
                auto c = data[it];
                switch(c)
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
            return ;
        }

        LegacyClassGen::TypeInfo parseType()
        {
            LegacyClassGen::TypeInfo t;
            while(it != end)
            {
                auto c = data[it];
                switch(c)
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
    /*if (value.last() == '>')
    {
        size_t i = value.indexOf('<');
        output.Name = value.left(i);
        if (i != size_t(-1))
        {
            Array<String> parameters = value.mid(i + 1, value.size() - 2 - output.Name.size()).split(',');
            for (auto& parameter : parameters)
            {
                size_t i = output.Parameters.size();
                output.Parameters.resize(output.Parameters.size() + 1);
                readRecursively(parameter, output.Parameters[i]);
            }
        }
    }
    else
    {
        output.Name = value;
    }*/
}

inline AJSONValue toJSONValue(const LegacyClassGen::TypeInfo& value)
{
    return writeRecursively(value);
}

inline void fromJSONValue(const AJSONValue& value, LegacyClassGen::TypeInfo& output)
{
    readRecursively(value.toString(), output);
}
