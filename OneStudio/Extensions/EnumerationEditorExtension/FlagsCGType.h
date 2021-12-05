#pragma once

#include "Core/BaseCGType.h"

namespace LegacyClassGen
{

class FlagsCGType : public BaseCGType
{
public:

    static void processAllFiles(const Array<SharedReference<FlagsCGType>> &textures, const APath &source)
    {

    }

    void generate() override
    {
        Array<String> values;
        data.read("Values", values);
        if (values.empty())
        {
            return;
        }

        String name = path.baseName();
        String namespaceName = getNamespace();

        String enumName = name + "::Enum";

        size_t bit = 0x1;
        Array<String> flags;
        for (auto &value : values)
        {
            flags.push_back(fmt::format("{} = {0:#x}", value, bit));
            bit <<= 1;
        }

        auto generateFlagsHeader = [&]() {
            //generateEntry
        };
        auto generateFlagsBody = [&]() {
            generateVisiblityScope(VisibilityType::Public, [&]() {
                pushRegion(String());
                generateEnumeration("Enum", flags);
                popRegion();
                generateField("size_t", "value", "0");
                writeWithIndent("" + name + "();\r\n");
                writeWithIndent("inline " + name + "(size_t value):value(value) {}\r\n");
                writeWithIndent("inline " + name + "(Enum value):value(size_t(value)) {}\r\n");
                writeWithIndent("inline explicit operator size_t() const { return size_t(value); }\r\n");
                writeWithIndent("inline explicit operator bool() const { return bool(value); }\r\n");

                writeWithIndent("static constexpr const char *Names[] =\r\n");
                generateBlock([&]() {
                    for (const auto &value : values)
                    {
                        writeWithIndent("\"" + value + "\",\r\n");
                    }
                }, BlockFlags::AddIndents | BlockFlags::CompleteWithSemicolon);

                writeWithIndent("inline StringArray toStrings() const\r\n");
                generateBlock([&]() {
                    generateField("StringArray", "strings");
                    size_t i = 0;
                    for (const auto &value : values)
                    {
                        writeWithIndent("if (value & " + name + "::" + value + ") { strings.append(Names[" + Str::ToString(i) + "]); }\r\n");
                        ++i;
                    }
                    generateReturn("strings");
                }, BlockFlags::AddIndents);

                writeWithIndent("inline " + name + "(const String &flags)\r\n");
                generateBlock([&]() {
                    generateField("StringArray", "data", "flags.split('|')");
                    for (const auto &value : values)
                    {
                        writeWithIndent("if (data.find_first_of(\"" + value + "\") != size_t(-1)) { value |= " + value +"; }\r\n");
                    }
                }, BlockFlags::AddIndents);
                writeWithIndent("inline String toString() const { return String::join(toStrings(), \"|\"); }\r\n");
            });
        };

        auto generateOperators = [&]() {
            auto generateOperator = [&](const char *operatorToken) {
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + enumName + " l, " + enumName + " r) { return size_t(l) " + operatorToken + " size_t(r); }\r\n");
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + enumName + " l, " + name + " r) { return size_t(l) " + operatorToken + " r.value; }\r\n");
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + name + " l, " + enumName + " r) { return l.value " + operatorToken + " size_t(r); }\r\n");
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + name + " l, " + name + " r) { return l.value " + operatorToken + " r.value; }\r\n");
                writeWithIndent("inline " + name + " &operator " + operatorToken + "=(" + name + " &l, " + enumName + " r) { l.value = l.value " + operatorToken + " size_t(r); return l; }\r\n");
                writeWithIndent("inline " + name + " &operator " + operatorToken + "=(" + name + " &l, " + name + " r) { l.value = l.value " + operatorToken + " r.value; return l; }\r\n");
            };
            auto generateOneComponentOperator = [&](const char *operatorToken) {
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + enumName + " v) { v = " + enumName + "(size_t(" + operatorToken + "v)); return v; }\r\n");
                writeWithIndent("inline " + name + " operator " + operatorToken + "(" + name + " v) { v.value = " + operatorToken + "v.value; return v; }\r\n");
            };
            generateOperator("|");
            generateOperator("&");
            generateOperator("^");
            generateOneComponentOperator("~");
        };

        auto generateSerialization = [&]() {

            if (!namespaceName.empty()) writeWithIndent("}\r\n"); //HACK: excluding serialization from namespace
            writeWithIndent("inline AJSONValue toJSONValue(const " + namespaceName + "::" + name + " &value) { return value.toString(); }\r\n");
            writeWithIndent("inline void fromJSONValue(const AJSONValue &value, " + namespaceName + "::" + name + " &output) { output = " + namespaceName + "::" + name + "(value.toString()); }\r\n");
            if (!namespaceName.empty()) writeWithIndent("namespace " + namespaceName + " {\r\n"); //HACK: excluding serialization from namespace
        };

        writeHeaderFile({ "cstddef", "Data" }, {}, namespaceName, [&]() {
            pushRegion("Flags");
            generateClass(name, String(), {}, [&]() {
                generateFlagsBody();
            });
            popRegion();

            generateRegion("Operators", generateOperators);
            generateRegion("Serialization", generateSerialization);
        }, {
            { "FlagsHeader", [&]() { generateClassWithoutBlock(name, String(), {}); } },
            { "FlagsBody", generateFlagsBody },
            { "Operators", generateOperators },
            { "Serialization", generateSerialization },
        });

        auto generateImplementation = [&]() {
            generateFunction(String(), "AStaticRun", { name }, [&]() {
                writeWithIndent("MetaObjectInformation::getInstance().flags.insert({ AMeta::getStaticTypeHash<" + name + ">(), {\"" + (!namespaceName.empty() ? namespaceName + "." + name : name) + "\", { \"" + Str::Join(values, "\", \"") + "\" } } });\r\n");
            });
            generateMethodImplementation(String(), name, name, {}, [&]() {
                generateCall("LinkStaticRun", { name });
            });
        };

        writeSourceFile(namespaceName, [&]() {
            generateRegion("Implementation", generateImplementation);
        }, { { "Implementation", generateImplementation } });
    }

    String generateInitialization(const LegacyClassGen::TypeInfo &typeInfo, const AJSONValue &value, const String &indent, const String &variableName, Array<String> &dependencies) override
    {
        Array<String> flags = Str::Split(value.toString(), "|");

        String typePrefix = getDefaultType(true) + "::";
        for (String &flag : flags)
        {
            flag = typePrefix + flag;
        }

        return Str::Join(flags, "|");
    }
};

}
