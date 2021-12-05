#include "ExtensionCGType.h"

#include <Foundation>
#include <Experimental>

#include "Includes/ExtensionDescription.gen.h"
#include "Includes/GraphData.gen.h"
#include "Includes/PropertyInfo.gen.h"
#include "Includes/ClassContext.gen.h"

namespace LegacyClassGen
{

void ExtensionCGType::generate()
{
    AJSONValue v;
    data.read("ExtensionDescription", v);
    LegacyClassGen::ExtensionDescription description;
    fromJSONValue(v, description);

    Array<String> localDependencies;
    addDependencies(description.Implementation, localDependencies);
    writeGeneratedFile2("cpp", {
        { "Includes", [&]() {
            generateIncludes({ "Experimental", "LanguageFunctions.h" }, localDependencies);
        } },
        { "ExtensionImplementation",[&]() {
            generateCall("AApplicationPluginImplementation", {
                description.Interface,
                description.Implementation,
                std::to_string(description.Revision),
                Str::Quote(description.Version),
                Str::Quote(description.Package),
            });
        } },
    });
}

//AApplicationPluginImplementation(OSPlugin, CGPrivatePlugin, 1, "1.0.0", "com.InsaneTeam.OneStudio.ClassGen")

}
