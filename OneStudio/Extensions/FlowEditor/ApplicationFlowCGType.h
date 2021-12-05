#pragma once

#include <ClassGenLibrary>

//#include "Core/BaseCGType.h"
//#include "Includes/TextureCompilation.gen.h"
//
//#include "Includes/NodeData.gen.h"
//
//#include "Types/Class/ClassManager.h"

namespace LegacyClassGen
{

class ApplicationFlowCGType : public BaseCGType
{
    String flowName;
    Array<String> declarationDependencies;
    Array<String> implementationDependencies;
    Array<NodeData> states;
    Array<String> applicationComponents;
public:

    String getBaseType() const override
    {
        return "AObject";
    }

    void generateStateMachine()
    {
        size_t index = 0;
        generateClass(flowName, String(), {}, [&]() {
            AJSONArray nodesData;
            if (!data.read("Nodes", nodesData))
            {
                return;
            }

            Array<String> stateNames;
            String statesTable = "\r\n";
            for (const AJSONValue& nodeData : nodesData)
            {
                if (!nodeData.isObject())
                {
                    continue;
                }

                NodeData data;
                data.deserialize(nodeData.asObject());

                if (data.Type == "State")
                {
                    statesTable.append("{ &" + flowName + "::on" + data.Identifier + "Create, &" + flowName + "::on" + data.Identifier + "Destroy, &" + flowName + "::on" + data.Identifier + "Enter, &" + flowName + "::on" + data.Identifier + "Exit },\r\n");
                    stateNames.append(data.Identifier);
                    states.emplaceBack(std::move(data));
                }
                else if (data.Type == "AplicationComponent")
                {
                    if (data.Data.isEmpty())
                    {
                        continue;
                    }

                    String baseType;
                    if (!data.Data.read("BaseType", baseType))
                    {
                        return;
                    }

                    addDependencies(baseType, implementationDependencies);

                    applicationComponents.emplaceBack(std::move(resolveType(baseType)));
                }
                //TODO: should it support other nodes?
                /*else
                {
                    generateField(fmt::format("SharedReference<{}>", data.Identifier),
                        data.Identifier + String::number(index),
                        fmt::format("new {}()", data.Identifier, data.Identifier));
                    objects.emplaceBack(std::move(data));
                    ++index;
                }*/
            }

            const String& entryPoint = stateNames[0];

            generateField("static Array<SharedReference<FlowState>>", "states");

            for (const NodeData& state : states)
            {
                bool needToRemoveObject = false;
                generateFunction("static void", "on" + state.Identifier + "Create", {}, [&]() {
                    if (state.Data.isEmpty())
                    {
                        return;
                    }

                    String baseType;
                    if (!state.Data.read("BaseType", baseType))
                    {
                        return;
                    }

                    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(baseType);
                    if (typeIt == LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
                    {
                        return;
                    }

                    SharedReference<BaseCGType> type = typeIt->second;

                    generateField("SharedReference<UI::WindowFlowState>", "state", "new UI::WindowFlowState()"); //TODO: this is window related code. support other types

                    String resolvedType = resolveType(baseType);
                    generateField("std::unique_ptr<" + resolvedType + ">", "instance{ " + type->createNewInstance(resolvedType) + "}");

                    AJSONObject values;
                    if (state.Data.read("Values", values))
                    {
                        String dereferencedVariableName = "(*instance)";
                        processProperties(dereferencedVariableName, typeIt->second.data(), values, declarationDependencies);
                    }

                    needToRemoveObject = true;

                    if (entryPoint == state.Identifier) //TODO: this is window related code. support other types
                    {
                        generateAssignment("(*instance).onClosed", { "[](){ UIApplication::getInstance().stop(); }" });
                    }
                    else
                    {
                        generateAssignment("(*instance).onClosed", { "[](){ sm.popState(); }" });
                    }
                    generateCall("state->setInstance", { "std::move(instance)" });
                    generateCall("state->onCreate", {});
                    generateCall("states.append", { "state" });

                });
                generateFunction("static void", "on" + state.Identifier + "Enter", {}, [&]() {
                    generateCall("states.last()->onEnter", {});
                });
                generateFunction("static void", "on" + state.Identifier + "Exit", {}, [&]() {
                    generateCall("states.last()->onExit", {});
                });
                generateFunction("static void", "on" + state.Identifier + "Destroy", {}, [&]() {
                    if (needToRemoveObject)
                    {
                        generateCall("states.last()->onDestroy", {});
                        generateCall("states.removeLast", {});
                    }
                });
            }

            generateField("static constexpr StaticStackState", "StatesTable[]", "{ " + statesTable + "}");

            generateVisiblityScope(VisibilityType::Public, [&]() {
                generateEnumeration("States", stateNames);
                generateAssignment("constexpr static const char *StateNames[]", fmt::format("{{ \"{}\" }}", String::join(stateNames, "\", \"")));
                String sm = "VariantStaticStackBasedStateMachine<" + flowName + "::StatesTable, " + String::number(states.size()) + ", " + flowName + "::" + entryPoint + ", false>";
                generateField("using", "StateMachineType", sm);
                generateField("static StateMachineType", "sm");
            });
        });
    }

    void collectDependencies()
    {
        declarationDependencies.clear();
        declarationDependencies.append("Experimental");
        AJSONArray nodesData;
        if (!data.read("Nodes", nodesData))
        {
            return;
        }

        for (const AJSONValue& nodeData : nodesData)
        {
            if (!nodeData.isObject())
            {
                continue;
            }

            NodeData data;
            data.deserialize(nodeData.asObject());

            String type;
            if (!data.Data.read("BaseType", type))
            {
                return;
            }

            addDependencies(type, declarationDependencies);
        }

        declarationDependencies.append("WindowFlowState.h");
    }

    void generateStateMachineImplementation()
    {
        generateField("Array<SharedReference<FlowState>>", flowName + "::states");
        generateField(flowName + "::StateMachineType", flowName + "::sm");
    }

    void generateEntryPoint()
    {
        generateFunction("int", "main", { "int argv", "const char *argc[]" }, [&]() {
            generateField("UIApplication", "application");

            writeWithIndent("application.components = {\r\n");
            for (auto& applicationComponent : applicationComponents)
            {
                writeWithIndent("    createNew<" + applicationComponent + ">(),\r\n");
            }
            writeWithIndent("};\r\n");
            
            generateReturn("application.execute().getErrorCode()");
        });
    }

    APair<String, ADelegate<void()>> getDefaultDependenciesRegionForHeaderFile()
    {
        return { "Dependencies", [&]() {
            write("#pragma once\r\n");
            generateIncludes({}, declarationDependencies);
        } };
    }

    APair<String, ADelegate<void()>> getDefaultDependenciesRegionForSourceFile()
    {
        return { "Dependencies", [&]() {
            auto includes = getImportFiles();
            for (auto &i : implementationDependencies)
            {
                includes.append(i);
            }
            generateIncludes({}, includes);
        } };
    }

    void generate() override
    {
        flowName = getDefaultType(true);
        applicationComponents.clear();
        applicationComponents.append("FlowApplicationComponent<" + flowName + ">");

        collectDependencies();
        pushBuffer();
        generateStateMachine();
        String classData = popBuffer();
        
        writeGeneratedFile2("h", {
            getDefaultDependenciesRegionForHeaderFile(),
            { "Declaration", [&]() {
                write(classData);
        } } });

        writeGeneratedFile2("cpp", {
            getDefaultDependenciesRegionForSourceFile(),
            { "Implementation", [&]() {
                generateStateMachineImplementation();
                //generateApplicationController();
                generateEntryPoint();
        } } });
    }
};

}
