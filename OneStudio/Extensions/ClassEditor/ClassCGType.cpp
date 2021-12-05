#include "ClassCGType.h"

#include "Includes/TypeInfo.gen.h"
#include "Types/Class/ClassManager.h"

namespace LegacyClassGen
{

void ClassCGType::generate()
{
    String namespaceName;
    data.read("Namespace", namespaceName);

    String name = path.baseName();

    bool isNative = false;
    bool isStruct = false;
    bool isInterface = false;
    bool serializable = true;

    Array<String> attributes;
    String entityType = "Class";
    data.read("Attributes", attributes);
    if (ArrayUtils::Contains(attributes, String("Interface")))
    {
        entityType = "class";
        isInterface = true;
    }
    else if (ArrayUtils::Contains(attributes, String("Structure")))
    {
        entityType = "struct";
        isStruct = true;
    }
    else if (ArrayUtils::Contains(attributes, String("Native")))
    {
        isNative = true;
    }
    else if (ArrayUtils::Contains(attributes, String("CascadeData")))
    {
        entityType = "class";
        isStruct = false;
    }
    else
    {
        entityType = "class";
    }

    if (ArrayUtils::Contains(attributes, String("NotSerializable")))
    {
        serializable = false;
    }

    Array<String> dependencies;

    String baseType;
    data.read("BaseType", baseType);
    if (baseType.empty() && serializable && !isInterface)
    {
        baseType = "Serializable"; //HACK: it's temporary needed for to be sure that all classes have serialization methods
        dependencies.push_back("Serializable.h");
    }

    LegacyClassGen::TypeInfo baseTypeInfo;
    if (!baseType.empty())
    {
        readRecursively(baseType, baseTypeInfo);
    }

    Array<String> interfaces;
    data.read("Interfaces", interfaces);

    Array<String> templateTypes;
    data.read("TemplateTypes", templateTypes);

    processTypeDependencies(baseTypeInfo, dependencies);
    addDependencies(interfaces, dependencies);

    Array<PropertyInfo> propertyInfos;
    Array<EventInfo> eventInfos;
    Array<FunctionInfo> functionInfos;

    AJSONArray properties;
    if (isStruct && data.read("Properties", properties))
    {
        //TODO: reserve propertyInfo
        propertyInfos.resize(properties.size());
        size_t i = 0;
        for (const AJSONValue &value : properties)
        {
            PropertyInfo &propertyInfo = propertyInfos[i];
            propertyInfo.deserialize(value.asObject());
            ++i;

            processPropertiesDependencies(propertyInfo, dependencies);
        }
    }
    else if (!isStruct && data.read("Properties", properties))
    {
        //TODO: reserve propertyInfo
        propertyInfos.resize(properties.size());
        size_t i = 0;
        for (const AJSONValue &value : properties)
        {
            PropertyInfo &propertyInfo = propertyInfos[i];
            propertyInfo.deserialize(value.asObject());

            /*EventInfo &eventInfo = eventInfos[i];
            eventInfo.name = propertyInfo.Name + "Changed";
            eventInfo.canBeSent = false;
            eventInfo.canBeListened = true;
            eventInfo.implemented = false;*/

            ++i;

            processPropertiesDependencies(propertyInfo, dependencies);
        }
    }

    AJSONArray events;
    if (data.read("Events", events))
    {
        eventInfos.resize(events.size());
        size_t i = 0;
        for (const AJSONValue &value : events)
        {
            EventInfo &eventInfo = eventInfos[i];
            eventInfo.deserialize(value.asObject());
            ++i;
            
            processTypeDependencies(eventInfo.BaseType, dependencies);
            processParametersDependencies(eventInfo.InputArguments, dependencies);
        }
    }

    AJSONArray functions;
    if (data.read("Functions", functions))
    {
        functionInfos.resize(functions.size());
        size_t i = 0;
        for (const AJSONValue& value : functions)
        {
            FunctionInfo& f = functionInfos[i];
            f.deserialize(value.asObject());
            ++i;

            processFunctionDependencies(f, dependencies);
        }
    }

    auto generateClassDeclarationRegion = [&]() {
        generateDefaultClassAliases(name, resolveType(baseType), resolveTypes(interfaces));
        if (!isInterface && !eventInfos.empty())
        {
            generateVisiblityScope(VisibilityType::Public, [&]() {
                for (const EventInfo &eventInfo : eventInfos)
                {
                    Array<String> inputArguments;
                    for (auto &a : eventInfo.InputArguments)
                    {
                        inputArguments.push_back(writeRecursivelyResolved(a.Type) + " const& " + a.Name);
                    }
					generateField(fmt::format("ADelegate<{}({})>", writeRecursivelyResolved(eventInfo.BaseType), inputArguments), eventInfo.Name);
                }
            });
        }
        if (!isInterface && !propertyInfos.empty())
        {
            if (isStruct)
            {
                generateVisiblityScope(VisibilityType::Public, [&]() {
                    for (const PropertyInfo &propertyInfo : propertyInfos)
                    {
                        generateField(addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters)), propertyInfo.Name/*, propertyInfo.DefaultValue*/);
                    }
                });
            }
            else
            {
                VisibilityType currentVisibility = VisibilityType::Private;
                for (const PropertyInfo &propertyInfo : propertyInfos)
                {
                    auto generatePropertyField = [&]() {
                        generateField(addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters)), propertyInfo.Name);
                    };

                    VisibilityType propertyVisibility = isStruct ? VisibilityType{ VisibilityType::Protected } : (propertyInfo.Variable ? propertyInfo.Visibility : VisibilityType{ VisibilityType::Protected });
                    if (propertyVisibility != currentVisibility)
                    {
                        currentVisibility = propertyVisibility;
                        generateVisiblityScope(propertyVisibility, generatePropertyField);
                    }
                    else
                    {
                        generatePropertyField();
                    }
                }
            }
        }

        generateVisiblityScope(VisibilityType::Public, [&]() {

            if (!isInterface)
            {
                generateConstructor(name, {});

                if (serializable)
                {
                    generatePreProcessorBranch("METAOBJECT_SUPPORT || REFLECTION_SUPPORT", [&]() {
                        generateFunction("void", "serialize", { "class AJSONObject &object" }, nullptr, true);
                        generateFunction("void", "deserialize", { "const class AJSONObject &object" });
                    });
                }
            }
            else
            {
                generateDestructor(name, nullptr, true);
            }

            if (!isStruct)
            {
                for (const PropertyInfo &propertyInfo : propertyInfos)
                {
                    if (propertyInfo.Variable)
                    {
                        continue;
                    }
                    generatePropertyMethods(
                        addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters)),
                        propertyInfo.Name,
                        bool(propertyInfo.Attributes & PropertyAttributes::ReadOnly),
                        isInterface
                    );
                }
            }

            /*for (const EventInfo &eventInfo : eventInfos)
            {
                if (eventInfo.dynamic)
                {
                    continue;
                }

                String eventType = eventInfo.name + "Event";
                String eventArgument = eventType + " &event";
                String eventDelegate = eventInfo.name;

                if (eventInfo.canBeListened)
                {
                    generateField("Array<ADelegate<void(" + eventArgument + ")>>", eventDelegate);
                }

                if (!eventInfo.canBeSent)
                {
                    continue;
                }

                generateFunction(voidType, "send" + eventInfo.name + "Event", { eventArgument }, [&]() {
                    generateCall("on" + eventInfo.name, { "event" });
                    if (eventInfo.canBeListened)
                    {
                        writeWithIndent("for (const auto &delegate : " + eventDelegate + ")\r\n");
                        generateBlock([&]() {
                            generateCall("delegate", { "event" });
                        }, BlockFlags::AddIndents);
                    }
                });
            }*/

            for (const FunctionInfo& f : functionInfos)
            {
                String type;
                if (f.OutputArguments.size() > 1)
                {
                    type = "std::tuple<";
                    for (auto& a : f.OutputArguments)
                    {
                        type.append(writeRecursivelyResolved(a.Type) + " /*" + a.Name + "*/" + ",");
                    }
                    type[type.size() - 1] = '>';
                }
                else if (f.OutputArguments.size() == 1)
                {
                    type = writeRecursivelyResolved(f.OutputArguments[0].Type) + " /*" + f.OutputArguments[0].Name + "*/";
                }
                Array<String> inputArguments;
                for (auto& a : f.InputArguments)
                {
                    inputArguments.push_back(writeRecursivelyResolved(a.Type) + " const& " + a.Name);
                }

                generateFunction(!type.empty() ? type : voidType, Str::ToFirstLowerCase(f.Identifier), inputArguments, nullptr, bool(f.Attributes & FunctionAttributes::Constant), isInterface || bool(f.Attributes& FunctionAttributes::Abstract));
            }
        });

        onGenerateClassBody(dependencies);

        /*if (eventInfos)
        {
            generateVisiblityScope(VisibilityType::Protected, [&]() {
                for (const EventInfo &eventInfo : eventInfos)
                {
                    generateFunction(voidType, "on" + eventInfo.name, {}, eventInfo.implemented ? nullptr : ADelegate<void()>([&]() {}));
                }
            });
        }*/
    };

    auto generateEntireHeaderFile = [&]() {
        if (isNative)
        {
            return;
        }

        pushRegion("Class");
        generateEntity(entityType, name, resolveType(baseType), resolveTypes(interfaces), generateClassDeclarationRegion);
        popRegion();
    };

    auto generateClassImplementationRegion = [&]() {
        if (isNative)
        {
            return;
        }
        generateConstructorImplementation(name, {}, [&]() {
            generateValues(this, "(*this)", dependencies);
            onGenerateConstructor(dependencies);
        });
        if (serializable)
        {
            generatePreProcessorBranch("METAOBJECT_SUPPORT || REFLECTION_SUPPORT", [&]() {
                generateMethodImplementation("void", name, "serialize", { "AJSONObject &object" }, [&]() {

                    if (!baseType.empty())
                    {
                        generateCall("Super::serialize", { "object" });
                    }

                    for (const PropertyInfo &propertyInfo : propertyInfos)
                    {
                        if (propertyInfo.Attributes & (PropertyAttributes::Mapped | PropertyAttributes::ReadOnly))
                        {
                            ALogMessage("", "Warning: Serialized mapped property should be writable. Serialization for %s will be skipped", propertyInfo.Name);
                            continue;
                        }

                        if (propertyInfo.Attributes & PropertyAttributes::Serialized)
                        {
                            if (propertyInfo.Attributes & PropertyAttributes::Mapped)
                            {
                                writeWithIndent(fmt::format("object.insert(\"{}\", toJSONValue(get{}()));\r\n", propertyInfo.Name, propertyInfo.Name));
                            }
                            else
                            {
                                writeWithIndent(fmt::format("object.insert(\"{}\", toJSONValue({}));\r\n", propertyInfo.Name, propertyInfo.Name));
                            }
                        }
                    }
                }, true);
                generateMethodImplementation("void", name, "deserialize", { "const AJSONObject &object" }, [&]() {

                    if (!baseType.empty())
                    {
                        generateCall("Super::deserialize", { "object" });
                    }

                    if (!propertyInfos.empty())
                    {
                        writeWithIndent("AJSONValue value;\r\n");
                    }
                    for (const PropertyInfo &propertyInfo : propertyInfos)
                    {
                        if (propertyInfo.Attributes & (PropertyAttributes::Mapped | PropertyAttributes::ReadOnly))
                        {
                            ALogMessage("", "Warning: Serialized mapped property should be writable. Deserialization for %s will be skipped", propertyInfo.Name);
                            continue;
                        }

                        if (propertyInfo.Attributes & PropertyAttributes::Serialized)
                        {
                            generateAssignment("value", "AJSONValue()");
                            generateCall("object.read", { Str::Quote(propertyInfo.Name), "value" });
                            if (propertyInfo.Attributes & PropertyAttributes::Mapped)
                            {
                                generateField(addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters)), propertyInfo.Name);
                            }
                            generateCall("fromJSONValue", { "value", propertyInfo.Name });
                            if (propertyInfo.Attributes & PropertyAttributes::Mapped)
                            {
                                generateCall("set" + propertyInfo.Name, { propertyInfo.Name });
                            }
                        }
                    }
                });
            });
        }
        if (!isStruct)
        {
            for (const PropertyInfo &propertyInfo : propertyInfos)
            {
                if (propertyInfo.Variable)
                {
                    continue;
                }
                generatePropertyImplementation(
                    addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters)),
                    name,
                    propertyInfo.Name,
                    propertyInfo.PreCallbacks,
                    /*Array<String>({ "on" + propertyInfo.Name + "Changed" }) +*/ propertyInfo.PostCallbacks,
                    bool(propertyInfo.Attributes & PropertyAttributes::ReadOnly)
                );
            }
        }
        onGenerateClassSource(dependencies);
    };

    auto generateEntireSourceFile = [&]() {
        if (isNative)
        {
            return;
        }
        generateRegion("ClassImplementation", generateClassImplementationRegion);
    };

    for (const auto &importFile : getImportFiles())
    {
        ArrayUtils::Remove(dependencies, importFile);
    }
    writeHeaderFile({}, dependencies, namespaceName, generateEntireHeaderFile, {
        { "Includes", [&]() { generateIncludes({}, { dependencies }); onGenerateHeaderDependencies(); } },
        { "Namespace", [&]() { generateNamespaceWithoutBlock(namespaceName); } },
        { "ClassHeader", [&]() {
            if (isNative)
            {
                return;
            }
            if (!templateTypes.empty())
            {
                generateTemplate(templateTypes);
            }
            generateEntity(entityType, name, resolveType(baseType), resolveTypes(interfaces));
        } },
        { "ClassBody", generateClassDeclarationRegion },
    });

    if(!isInterface)
    {
        writeSourceFile(namespaceName, generateEntireSourceFile, {
            { "Includes", [&]() {
                generateHeaderInclude();
                generateInclude("MetaObjectSerializationHelper.h", true);
                onGenerateSourceDependencies(); } },
            { "Namespace", [&]() { generateNamespaceWithoutBlock(namespaceName); } },
            { "ClassImplementation", generateClassImplementationRegion },
        });
    }
}

void ClassCGType::generateValues(const LegacyClassGen::BaseCGType *typeData, const String &variable, Array<String> &dependencies)
{
    AJSONObject values;
    data.read("Values", values);
    processProperties(variable, typeData, values, dependencies);
}

String ClassCGType::generateInitialization(const LegacyClassGen::TypeInfo &typeInfo, const AJSONValue &value, const String &indent, const String &variableName, Array<String> &dependencies)
{
    //TODO: add check that this is not recursive call

    String typeName = getDefaultType(true);
    if (typeName == "SharedReference" || typeName == "WeakReference" || typeName == "AssetReference")
    {
        String variable;
        if (value.isString())
        {
            auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(value.asString());
            if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                addDependencies(*typeIt->second, dependencies);
                variable = resolveType(value.asString()) + "_Asset.load()";
            }
        }
        else
        {
            this->indent = indent;
            const APair<String, AJSONValue> &data = *value.asObject().begin();
            String baseType = data.first;
            auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(baseType);
            if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                addDependencies(*typeIt->second, dependencies);
                auto resolvedBaseType = resolveType(baseType);
                generateField(resolvedBaseType + "*", variableName, typeIt->second->createNewInstance(resolvedBaseType));
                if(data.second.isObject())
                {
                    processProperties("(*" + variableName + ")", typeIt->second.get(), data.second.asObject(), dependencies);
                }
                return variableName;
            }
            this->indent.clear();
        }
        return variable;
    }

    if (value.isString()) //Asset
    {
        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(value.asString());
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            String variable;
            if (typeIt->second->group == CGTypeGroup::Asset)
            {
                variable = typeIt->second->generateInitialization(LegacyClassGen::TypeInfo(),value, indent, variableName, dependencies);
            }
            else // TODO: This is a hack, need to implement proper templates initialization...
            {
                addDependencies(*typeIt->second, dependencies);
                variable = typeIt->second->createNewInstance(resolveType(value.asString()));
            }
            this->generatedBuffer = std::move(typeIt->second->generatedBuffer);
            return variable;
        }
    }
    else if (value.isObject()) //Object
    {
        this->indent = indent;
        AJSONObject values = value.toObject();
        generateField(typeName, variableName);
        processProperties(variableName, this, values, dependencies);
        this->indent.clear();
        return variableName;
    }
    else if (value.isArray()) //Containers
    {
        AJSONArray containerLayout;
        if(!data.read("ContainerLayout", containerLayout))
        {
            ALogMessage("", "Warning: Container layout is not defined for %s!", typeName);
        }
        
        Array<String> templateTypes;
        data.read("TemplateTypes", templateTypes);

        auto processItem = [&](const LegacyClassGen::TypeInfo &paremeterType, const AJSONValue &item, size_t itemIndex, size_t containerItemIndex) {
            auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(paremeterType.Name);
            if (typeIt == LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                return String();
            }
            SharedReference<LegacyClassGen::BaseCGType> itemType = typeIt->second;

            addDependencies(*itemType, dependencies);

            String variable = itemType->generateInitialization(paremeterType, item, indent, "item_" + getNextIdentifier() + "_" + Str::ToString(itemIndex) + (containerItemIndex != -1 ? "_" + Str::ToString(containerItemIndex) : String()), dependencies);
            this->generatedBuffer.append(itemType->flush());
            return variable;
            /*if(item.isObject())
            {
                String variable = itemType->generateInitialization(paremeterType, item, indent, "item_" + getNextIdentifier() + "_" + String::number(itemIndex) + (containerItemIndex != -1 ? "_" + String::number(containerItemIndex) : String()), dependencies);
                this->generatedBuffer.append(itemType->flush());
                return variable;
            }
            else
            {
                //TODO: implement type deduction
                if (item.isBoolean())
                {
                    return String(item.asBoolean() ? "true" : "false");
                }
                else if (item.isNumber())
                {
                    return String::number(item.asNumber());
                }
                
                return item.toString().quote();
            }*/
        };

        String container;
        const AJSONArray &valueData = value.asArray();
        size_t i = 0;
        for (const AJSONValue &item : valueData)
        {
            if(containerLayout.size() == 1)
            {
                container.append(processItem(typeInfo.Parameters[0], item, i, -1) + ",");
            }
            else
            {
                String tuple;
                for(size_t j = 0; j < containerLayout.size(); ++j)
                {
                    tuple.append(processItem(typeInfo.Parameters[j], item.asArray()[j], i, j) + ",");
                }
            }
            ++i;
        }

        return "{" + container + "}";
        
        /*this->indent = indent;
        String variable = path.baseName().toFirstLowerCase();

        const AJSONArray &valueData = value.asArray();

        // TODO: Wrapping strings with arrays is a hack, need to implement proper templates initialization...
        //const AJSONArray &parameters = valueData[0].isArray() ? valueData[0].asArray() : AJSONArray({ valueData[0].asString() });
        //bool isContainer = valueData[1].isArray();
        //const AJSONArray &items = isContainer ? valueData[1].asArray() : AJSONArray({ valueData[1].asString() });

        auto processItem = [&](const AJSONValue &item, const SharedReference<LegacyClassGen::BaseCGType> &itemType, size_t itemIndex, size_t parameterIndex) {
            String variable = itemType->generateInitialization(item, indent, "item_" + getNextIdentifier() + "_" + String::number(itemIndex) + (parameterIndex != -1 ? "_" + String::number(parameterIndex) : String()), dependencies);
            this->generatedBuffer.append(itemType->flush());
            return variable;
        };

        String data;

        Array<SharedReference<LegacyClassGen::BaseCGType>> parameterTypes;
        for (const AJSONValue &parameter : parameters)
        {
            auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(parameters[0].asString());
            if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                auto type = typeIt->second;
                parameterTypes.append(type);
            }
            else
            {
                //TODO: error - type is not found
                return "{}";
            }
        }

        if (parameters.size() == 1)
        {
            if (isContainer)
            {
                size_t i = 0;
                for (const AJSONValue &item : items)
                {
                    data.append(processItem(item, parameterTypes[0], i, -1) + ",");
                    ++i;
                }
            }
            else
            {
                data.append(processItem(items[0], parameterTypes[0], 0, -1));
            }
        }
        else
        {
            size_t i = 0;
            for (const AJSONValue &item : items)
            {
                String set;
                const AJSONArray &itemData = item.asArray();
                size_t j = 0;
                for (const SharedReference<LegacyClassGen::BaseCGType> &parameterType : parameterTypes)
                {
                    set.append(processItem(itemData[j], parameterType, i, j) + ",");
                    ++j;
                }
                data.append("{" + set + "},");
                ++i;
            }
        }

        this->indent.clear();
        return isContainer ? "{" + data + "}" : data;*/
    }

    return String();
}

}
