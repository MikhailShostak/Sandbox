#pragma once

#include "Core/BaseCGType.h"

namespace LegacyClassGen
{

class EnumerationCGType : public BaseCGType
{
public:

    static void processAllFiles(const Array<SharedReference<EnumerationCGType>> &textures, const APath &source)
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

        auto generateEnumerationBody = [&]() {
            generateVisiblityScope(VisibilityType::Public, [&]() {
                pushRegion(String());
                generateEnumeration("Enum", values);
                popRegion();
                generateField("Enum", "value", values[0]);
                writeWithIndent("" + name + "();\r\n");
                writeWithIndent("inline " + name + "(Enum value):value(value) {}\r\n");
                writeWithIndent("inline " + name + "(const " + name + " &value):value(value.value) {}\r\n");

                writeWithIndent("inline operator Enum() const { return value; }\r\n");

                writeWithIndent("static constexpr const char *Names[] =\r\n");
                generateBlock([&]() {
                    for (const auto &value : values)
                    {
                        writeWithIndent("\"" + value + "\",\r\n");
                    }
                }, BlockFlags::AddIndents | BlockFlags::CompleteWithSemicolon);

                writeWithIndent("inline " + name + "(const String &name)\r\n");
                generateBlock([&]() {
                    for (const auto &value : values)
                    {
                        writeWithIndent("if (name == \"" + value + "\") { value = " + value + "; return; }\r\n");
                    }
                }, BlockFlags::AddIndents);
                writeWithIndent("inline String toString() const\r\n");
                generateBlock([&]() {
                    generateSwitch("value", name, values, [&](const String &value, size_t index) {
                        generateReturn(fmt::format("Names[{}]", index));
                    });
                    generateReturn("String()");
                }, BlockFlags::AddIndents);
            });
        };

        String namespaceName = getNamespace();

        auto generateSerialization = [&]() {
            if (!namespaceName.empty()) writeWithIndent("}\r\n"); //HACK: excluding serialization from namespace
            writeWithIndent("inline AJSONValue toJSONValue(const " + namespaceName + "::" + name + " &value) { return value.toString(); }\r\n");
            writeWithIndent("inline void fromJSONValue(const AJSONValue &value, " + namespaceName + "::" + name + " &output) { output = " + namespaceName + "::" + name + "(value.toString()); }\r\n");
            if (!namespaceName.empty()) writeWithIndent("namespace " + namespaceName + " {\r\n"); //HACK: excluding serialization from namespace
        };

        writeHeaderFile({ "cstddef", "Data" }, {}, namespaceName, [&]() {
            pushRegion("Enumeration");
            generateClass(name, String(), {}, [&]() {
                generateEnumerationBody();
            });
            popRegion();
            generateRegion("Serialization", generateSerialization);
        }, {
            { "EnumerationHeader", [&]() { generateClassWithoutBlock(name, String(), {}); } },
            { "EnumerationBody", generateEnumerationBody },
            { "Serialization", generateSerialization },
        });

        auto generateImplementation = [&]() {
            generateFunction(String(), "AStaticRun", { name }, [&]() {
                writeWithIndent("MetaObjectInformation::getInstance().enums.insert({ AMeta::getStaticTypeHash<" + name + ">(), { \"" + (!namespaceName.empty() ? namespaceName + "." + name : name) + "\", { \"" + Str::Join(values, "\", \"") + "\" } } });\r\n");
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
        return getDefaultType(true) + "::" + value.toString();
    }
};

}
