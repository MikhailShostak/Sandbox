#include "ScriptCGType.h"

//#include "Includes/GraphData.gen.h"
//#include "Includes/PropertyInfo.gen.h"
//#include "Includes/ClassContext.gen.h"

#include "AJSONObject.h"
#include "FunctionManager.gen.h"
#include "Includes/Connection.gen.h"
#include "Includes/ItemView.gen.h"
#include "Includes/TypeInfo.gen.h"
#include "Str.hpp"
#include "range/v3/algorithm/for_each.hpp"
#include "range/v3/view/cache1.hpp"
#include "range/v3/view/drop.hpp"
#include "range/v3/view/join.hpp"
#include "range/v3/view/split.hpp"
#include "range/v3/view/transform.hpp"

namespace LegacyClassGen
{

template<typename CallbackType>
void walkExecution(const Array<LegacyClassGen::NodeData> &nodes, const String &startNode, CallbackType &&callback)
{
    auto findNode = [&nodes](const String &name) { return std::find_if(nodes.begin(), nodes.end(), [&](const LegacyClassGen::NodeData &d) { return d.Identifier == name; }); };

    auto it = findNode(startNode);
    if (it != nodes.end())
    {
        std::function<void(const LegacyClassGen::NodeData &)> processNodes = [&nodes, &findNode, &processNodes, &callback](const LegacyClassGen::NodeData &d) {
            for (const UI::Connection &connection : d.ExecutionBranches)
            {
                auto it = findNode(connection.Target);
                if (it != nodes.end())
                {
                    callback(*it);
                    processNodes(*it);
                }
            }
        };

        processNodes(*it);
    }
}

template<typename CallbackType>
void walkProperty(const Array<LegacyClassGen::NodeData> &nodes, const LegacyClassGen::NodeData &node, CallbackType &&callback)
{
    auto findNode = [&nodes](const String &name) { return std::find_if(nodes.begin(), nodes.end(), [&](const LegacyClassGen::NodeData &d) { return d.Identifier == name; }); };

    std::function<void(const LegacyClassGen::NodeData &)> processNodes = [&nodes, &findNode, &processNodes, &callback](const LegacyClassGen::NodeData &d) {
        for (const UI::Connection &connection : d.Connections)
        {
            Path p(connection.Target);
            auto it = findNode(p.source()[0]);
            if (it != nodes.end())
            {
                processNodes(*it);
                callback(connection, *it, p);
            }
        }
    };

    processNodes(node);
}

void ScriptCGType::generateFunctionImplementation(const Array<LegacyClassGen::FunctionInfo> &functions, const Array<LegacyClassGen::NodeData> &nodes, const String &entryPoint)
{
    auto findFn = [&functions](const String &identifier) { return rng::find_if(functions, [&](const auto &d) { return d.Identifier == identifier; }); };

    auto thisTypeName = getDefaultType();
    Map<String, String> variables;
    walkExecution(nodes, entryPoint, [&](const LegacyClassGen::NodeData &node) {        
        Map<String, String> values;
        walkProperty(nodes, node, [&](const UI::Connection &connection, const LegacyClassGen::NodeData &parentNode, const Path &path) {
            auto functionIt = findFn(parentNode.Identifier);
            if (functionIt == functions.end())
            {
                Log::Print("Function \"{}\" is not found", parentNode.Identifier);
                return;
            }
            if(functionIt->Callable)
            {
                values.insert(connection.Source, variables.at(connection.Target));
            }
            else
            {
                std::function<String(const LegacyClassGen::NodeData &node, const LegacyClassGen::FunctionInfo &info)> walkInput = [&](const LegacyClassGen::NodeData &node, const LegacyClassGen::FunctionInfo &info){
                    
                    auto findNode = [&nodes](const String &name) { return rng::find_if(nodes, [&](const LegacyClassGen::NodeData &d) { return d.Identifier == name; }); };

                    auto walkInputConnection = [&](const String &SourceName){
                        String result;
                        auto it = rng::find_if(node.Connections, [&](const UI::Connection &v){ return v.Source == SourceName; });
                        if(it != node.Connections.end())
                        {
                            auto var = variables.find(it->Target);
                            if(var != variables.end())
                            {
                                result = var->second;
                            }
                            else
                            {
                                Path p(it->Target);
                                auto nodeIt = findNode(p.source()[0]);
                                if (nodeIt != nodes.end())
                                {
                                    auto itFn = findFn(nodeIt->Identifier);
                                    if (itFn == functions.end())
                                    {
                                        Log::Print("Function \"{}\" is not found", nodeIt->Identifier);
                                        return result;
                                    }
                                    if(itFn->Callable)
                                    {
                                        Log::Print("Function \"{}\" is callbable but variable for \"{}\" doesn't exist", nodeIt->Identifier, it->Target);
                                    }
                                    result = walkInput(*nodeIt, *itFn);
                                }
                            }
                        }
                        return result;
                    };

                    Array<String> args;

                    auto index = info.Identifier.lastfind_first_of(".");
                    String variable; 
                    if(info.Identifier.find_first_of(thisTypeName) != UI::InvalidIndex)
                    {
                        variable = "(*this)";
                    }
                    else
                    {
                        variable = walkInputConnection("Object");
                    }
                    String method = index != UI::InvalidIndex ? info.Identifier.mid(index + 1) : info.Identifier;
                    for (const LegacyClassGen::Parameter &argument : functionIt->InputArguments)
                    {
                        args.append(walkInputConnection(argument.Name));
                    }
                    return Str::Format("{}{}{}({})", variable, variable ? "." : "", method.toFirstLowerCase(), String::join(args, ", "));
                };
                //getDefaultType(false);
                values.insert(connection.Source, walkInput(parentNode, *functionIt));
            }
        });

        bool isReturnPoint = node.Identifier == "ReturnPoint";

        Array<String> args;
        if(isReturnPoint)
        {
            std::string args = node.Connections
                | rngv::transform([&](const auto &v){ return values.at(v.Source); })
                | rngv::cache1
                | rngv::join(', ')
                | rng::to<std::string>();
            generateReturn(Str::Format("{{{}}}", args));//parentNode.ExecutionBranches ? path.baseName() : (parentNode.Identifier + "()"));
            return;
        }
        
        auto functionIt = findFn(node.Identifier);
        if (functionIt == functions.end())
        {
            Log::Print("Function \"{}\" is not found", node.Identifier);
            return;
        }

        for (const LegacyClassGen::Parameter &argument : functionIt->InputArguments)
        {
            args.append(values.at(argument.Name));
        }

        if (functionIt->OutputArguments)
        {
            Array<String> localVariables;
            for(const auto &argument : functionIt->OutputArguments)
            {
                String var = Str::Format("{}_{}", argument.Name, variables.size());
                localVariables.append(var);
                variables.insert(functionIt->Identifier + "/" + argument.Name, var);
            }
            std::string args = localVariables
                | rngv::join(', ')
                | rng::to<std::string>();
            auto format = functionIt->OutputArguments.size() == 1 ? "auto {} = " : "auto [{}] = ";
            writeWithIndent(Str::Format(format, args));
        }

        Array<String> templateValues;
        for (const auto &p : functionIt->TemplateParameters)
        {
            AJSONObject values;
            if (node.Data.read("Values", values))
            {
                String v;
                if (values.read(p, v))
                {
                    templateValues.append(v);
                }                    
            }
        }

        //TODO: Implement method calls in ClassGen
        auto sep_index = node.Identifier.lastfind_first_of(".");
        if (sep_index != -1)
        {
            generateCall((values.hasKey("Object") ? values.at("Object") : "(*this)") + "." + node.Identifier.mid(node.Identifier.lastfind_first_of(".") + 1).toFirstLowerCase(), args, templateValues);
        }
        else
        {
            generateCall(node.Identifier, args, templateValues);
        }
    });
}

void ScriptCGType::collectClassDependencies()
{
    AJSONValue v4;
    data.read("Interfaces", v4);
    Array<LegacyClassGen::TypeInfo> properties;
    fromJSONValue(v4, properties);
}

void ScriptCGType::collectPropertiesDependencies()
{
    AJSONValue v4;
    data.read("Properties", v4);
    Array<LegacyClassGen::PropertyInfo> properties;
    fromJSONValue(v4, properties);
}

void ScriptCGType::collectValuesDependencies()
{
    AJSONObject values;
    data.read("Values", values);
}

void ScriptCGType::collectFunctionsDependencies()
{
    AJSONValue v2;
    data.read("Functions", v2);
    Array<LegacyClassGen::FunctionInfo> functions;
    fromJSONValue(v2, functions);
}

void ScriptCGType::collectGraphsDependencies()
{
    AJSONValue v3;
    data.read("Graphs", v3);
    Map<String, LegacyClassGen::GraphData> graphData;
    fromJSONValue(v3, graphData);
}


void ScriptCGType::collectEventsDependencies()
{
    //AJSONValue v3;
    //data.read("Events", v3);
    //Map<String, LegacyClassGen::GraphData> graphData;
    //fromJSONValue(v3, graphData);
}

void ScriptCGType::collectDependencies()
{
    Super::collectDependencies();

    collectPropertiesDependencies();
    collectFunctionsDependencies();
    collectGraphsDependencies();
    collectEventsDependencies();
}

void ScriptCGType::generate()
{
    static String EntryPoint = "EntryPoint";

    AJSONValue v;
    data.read("Nodes", v);
    Array<LegacyClassGen::NodeData> nodesData;
    fromJSONValue(v, nodesData);

    AJSONValue v2;
    data.read("Functions", v2);
    Array<LegacyClassGen::FunctionInfo> functions;
    fromJSONValue(v2, functions);

    AJSONValue v3;
    data.read("Graphs", v3);
    Map<String, LegacyClassGen::GraphData> graphData;
    fromJSONValue(v3, graphData);

    AJSONValue v4;
    data.read("Properties", v4);
    Array<LegacyClassGen::PropertyInfo> properties;
    fromJSONValue(v4, properties);

    collectDependencies();

    clear();

    generateIncludes({ "Experimental", "LanguageFunctions.h" }, {});

    LegacyClassGen::FunctionManager::getInstance().Index();
    auto allFunctions = LegacyClassGen::FunctionManager::getInstance().Cache;

    generateClass("ScriptEntryPoint", String(), {}, [&]() {
        generateVisiblityScope(LegacyClassGen::VisibilityType::Public, [&]() {
            for (const LegacyClassGen::PropertyInfo &p : properties)
            {
                generateField(resolveType(p.Type), p.Name);
                generatePropertyImplementation(resolveType(p.Type), String(), p.Name);
            }

            for (const auto &pair : graphData)
            {
                if (!pair.first)
                {
                    continue;
                }

                auto functionIt = std::find_if(functions.begin(), functions.end(), [&](const LegacyClassGen::FunctionInfo &f) { return f.Identifier == pair.first; });

                if (functionIt == functions.end())
                {
                    ALogMessage("", "Warning: Function %s not found", pair.first);
                    continue;
                }

                Array<String> in;
                for (auto &a : functionIt->InputArguments)
                {
                    in.append(writeRecursivelyResolved(a.Type) + " const& " + a.Name);
                }

                LegacyClassGen::TypeInfo returnType;

                if (functionIt->OutputArguments)
                {
                    returnType.Name = "std::tuple";
                    Array<String> out;
                    for (auto &a : functionIt->OutputArguments)
                    {
                        returnType.Parameters.append(a.Type);
                    }
                }
                else
                {
                    returnType.Name = "void";
                }

                generateFunction(writeRecursivelyResolved(returnType), pair.first, { in }, [&]() {
                    generateFunctionImplementation(allFunctions, pair.second.Nodes, EntryPoint);
                });
            }

            generateFunction("int", "Main", { "int argc, const char *argv[]" }, [&]() {
                AJSONObject values;
                data.read("Values", values);
                Array<String> dependencies;
                processProperties("(*this)", this, values, dependencies);

                graphData.applyForValue("", [&](const LegacyClassGen::GraphData &data) {
                    generateFunctionImplementation(allFunctions, data.Nodes, EntryPoint);
                });
            });
        });
    });

    generateFunction("int", "main", { "int argc, const char *argv[]" }, [&]() {
        generateReturn("ScriptEntryPoint().Main(argc, argv)");
    });

    ALogMessage("", "%s", generatedBuffer);
}

}
