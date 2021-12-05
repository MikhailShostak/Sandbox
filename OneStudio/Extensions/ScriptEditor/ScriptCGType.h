#pragma once

#include <ClassGenLibrary>
#include "Includes/NodeData.gen.h"

namespace LegacyClassGen
{

class ScriptCGType : public BaseCGType
{
public:
    using Super = BaseCGType;

    void collectClassDependencies();
    void collectPropertiesDependencies();
    void collectValuesDependencies();
    void collectFunctionsDependencies();
    void collectGraphsDependencies();
    void collectEventsDependencies();

    void collectDependencies() override;
    void generate() override;
    void generateFunctionImplementation(const Array<LegacyClassGen::FunctionInfo> &functions, const Array<LegacyClassGen::NodeData> &nodes, const String &entryPoint);
};

}
