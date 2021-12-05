#include "Core/BaseCGType.h"

namespace LegacyClassGen
{

class BasicCGType : public BaseCGType
{
public:
    virtual void generate()
    {
        String namespaceName = getNamespace();

        Array<String> includes;
        data.read("Includes", includes);

        auto generateSource = [&]() {
            String source;
            data.read("Source", source);
            write(source);
            write("\r\n");
        };

        writeHeaderFile(includes, {}, namespaceName, [&]() {
            generateRegion("Source", [&]() {
                generateSource();
            });
        }, {
            { "Includes", [&]() { generateIncludes({ includes }, {}); } },
            { "Namespace", [&]() { generateNamespaceWithoutBlock(namespaceName); } },
            { "Source", generateSource },
        });
    }

    String generateInitialization(const LegacyClassGen::TypeInfo &typeInfo, const AJSONValue &value, const String &indent, const String &variableName, Array<String> &dependencies) override
    {
        if (value.isBoolean())
        {
            return value.asBoolean() ? "true" : "false";
        }
        else if (value.isNumber())
        {
            return Str::ToString(value.asNumber());
        }

        return Str::Quote(value.toString());
    }
};

}
