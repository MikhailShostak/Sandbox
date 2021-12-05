#pragma once

#include "ClassCGType.h"

#include "Types/Class/ClassManager.h"

namespace LegacyClassGen
{

class ViewCGType : public ClassCGType
{
    String PreViewsKey = "PreViews";
    String ViewsKey = "Views";
    String PostViewsKey = "PostViews";
public:

    using Super = ClassCGType;

    Array<String> propertyDependencies;
    String propertiesRegion;

    Array<String> constructorDependencies;
    String constructorRegion;
    String contentRegion;

    static void processAllFiles(const Array<SharedReference<ViewCGType>> &views, const APath &source)
    {
        Array<SharedReference<ClassCGType>> classes;
        for (auto &view : views)
        {
            classes.push_back(view);
        }
        Super::processAllFiles(classes, source);
    }

    String getViewName(const String &type, const AJSONObject &data) const
    {
        String name;
        if (!data.read("Name", name))
        {
            name = type;
            boost::replace_all(name, ".", "");
        }
        return name;
    }

    void processBindingContext(const String &parent, const AJSONObject &data)
    {
        AJSONArray bindingContext;
        data.read("BindingContext", bindingContext);
    }

    void processTemplates(const String &parent, const AJSONObject &data, Array<String> &dependencies)
    {
        AJSONArray templateViews;
        data.read("ViewTemplates", templateViews);
        for (const AJSONValue &templateView : templateViews)
        {
            if (!templateView.isObject())
            {
                continue;
            }

            const AJSONObject &templateViewData = templateView.asObject();

            String templateName;
            if (!templateViewData.read("Name", templateName))
            {
                continue;
            }

            String templateType;
            if (!templateViewData.read("BaseType", templateType))
            {
                continue;
            }

            //generateNamespaceWithoutBlock("ViewTemplates");
            //generateBlock([&]() {
            generateClass("ViewTemplates_" + templateName, resolveType(templateType), {}, []() {

            });
            //}, BlockFlags::AddIndents);
        }
    }

    void processBindings(const String &parent, const SharedReference<BaseCGType> &type, const AJSONObject &data)
    {
        AJSONObject bindingContext;
        type->data.read("BindingContext", bindingContext);

        AJSONObject bindings;
        data.read("Bindings", bindings);
        for (const APair<String, AJSONValue> &pair : bindings)
        {
            AJSONObject bindingData;
            bindingContext.read(pair.first, bindingData);

            AJSONValue inputArgumentsJSONData;
            bindingData.read("InputArguments", inputArgumentsJSONData);
            Array<LegacyClassGen::Parameter> inputArgumentsData;
            fromJSONValue(inputArgumentsJSONData, inputArgumentsData);

            Array<String> inputArguments;
            for (auto &a : inputArgumentsData)
            {
                inputArguments.push_back(writeRecursivelyResolved(a.Type) + " const& " + a.Name);
            }

            String expectedType;
            bindingData.read("BaseType", expectedType);

            if (pair.second.isString())
            {
                pushBuffer();
                generateBlock([&]() {
                    if (expectedType != voidType)
                    {
                        generateReturn(pair.second.toString());
                    }
                    else
                    {
                        writeWithIndent(pair.second.toString());
                    }
                }, BlockFlags::AddIndents | BlockFlags::CompleteWithSemicolon);
                String lambda = popBuffer();

                generateAssignment(parent + "." + pair.first, "[this](" + Str::Join(inputArguments, ", ") + ")" + lambda);
                continue;
            }

            const AJSONObject &bindingTemplate = pair.second.asObject();

            String templateType;
            if (!bindingTemplate.read("BaseType", templateType))
            {
                continue;
            }

            pushBuffer();
            generateBlock([&]() {
                generateField("auto", "instance", "Create<" + resolveType(templateType) + ">()");

                AJSONObject templateValues;
                bindingTemplate.read("Values", templateValues);
                for (const APair<String, AJSONValue> &templatePair : templateValues)
                {
                    generateCall("instance->set" + templatePair.first, { templatePair.second.toString() });
                }

                generateReturn("instance");
            }, BlockFlags::AddIndents | BlockFlags::CompleteWithSemicolon);
            String lambda = popBuffer();

            generateAssignment(parent + "." + pair.first, "[this](" + Str::Join(inputArguments, ", ") + ") -> " + resolveType(expectedType) + " " + lambda);
        }
    }

    void processContentViews(const String &parent, const AJSONObject &data, Array<String> &dependencies)
    {
        AJSONObject content;
        data.read("Content", content);
        if (content.size() > 0)
        {
            for (const APair<String, AJSONValue> &item : content)
            {
                const String &viewContentName = item.first;
                const AJSONValue &view = item.second;
                if (!view.isObject())
                {
                    continue;
                }

                const AJSONObject &viewData = view.asObject();
                if (processSubView(parent, viewData, dependencies, true))
                {
                    String viewName;
                    if (!viewData.read("Name", viewName))
                    {
                        continue;
                    }
                    generateAssignment(parent + "." + Str::ToFirstLowerCase(viewContentName), Str::ToFirstLowerCase(viewName));
                }
            }

            return;
        }

        AJSONArray views;
        data.read("Content", views);
        for (const AJSONValue &view : views)
        {
            if (!view.isObject())
            {
                continue;
            }

            const AJSONObject &viewData = view.asObject();
            if (processSubView(parent, viewData, dependencies, true))
            {
                String viewName;
                if (!viewData.read("Name", viewName))
                {
                    continue;
                }
                generateAssignment(parent + "." + Str::ToFirstLowerCase(viewName), Str::ToFirstLowerCase(viewName));
            }
        }
    }

    void processSubViews(const String &parent, const AJSONObject &data, const String &viewGroup, Array<String> &dependencies)
    {
        AJSONArray views;
        data.read(viewGroup, views);
        for (const AJSONValue &view : views)
        {
            if (!view.isObject())
            {
                continue;
            }

            const AJSONObject &viewData = view.asObject();
            processSubView(parent, viewData, dependencies);
        }
    }

    bool processSubView(const String &parent, const AJSONObject &viewData, Array<String> &dependencies, bool isContentView = false)
    {
        String viewType;
        if (!viewData.read("BaseType", viewType))
        {
            return false;
        }

        LegacyClassGen::TypeInfo viewTypeInfo;
        if (!viewType.empty())
        {
            readRecursively(viewType, viewTypeInfo);
        }

        String viewName = getViewName(viewType, viewData);
        
        bool isVariable = false;
        viewData.read("Variable", isVariable);

        bool isExternal = false;
        viewData.read("External", isExternal);

        if (isExternal)
        {
            isVariable = true;
        }
        if (isContentView)
        {
            isExternal = false;
        }

        bool dependencyAdded = false;

        String variableName = Str::ToFirstLowerCase(viewName);
        String resolvedType = resolveType(viewType);
        String dereferencedVariableName = "(*" + variableName + ")";
        if (isVariable)
        {
            propertiesRegion += indent + "SharedReference<" + resolvedType + "> " + variableName + ";\r\n";
            addDependencies(viewTypeInfo.Name, propertyDependencies);
            dependencyAdded = true;
        }

        auto generateSubView = [&]() {
            auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(viewTypeInfo.Name);
            if (typeIt == LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                return;
            }

            const SharedReference<BaseCGType> &type = typeIt->second;

            pushBuffer();
            write("[this](" + resolvedType + " *v)\r\n");
            generateBlock([&]() {
                processSubViews("(*v)", viewData, PreViewsKey, dependencies);
                processContentViews("(*v)", viewData, dependencies);
            }, BlockFlags::AddIndents);
            String preConstructionRegion = popBuffer();

            if (isVariable)
            {
                generateAssignment(variableName, type->createNewInstance(resolvedType, { preConstructionRegion }));
            }
            else
            {
                generateField("SharedReference<" + resolvedType + ">", variableName, type->createNewInstance(resolvedType, { preConstructionRegion }));
            }
            generateCall(dereferencedVariableName + ".setName", { Str::Quote(viewName) });

            generateBlock([&]() {
                processTemplates(dereferencedVariableName, viewData, dependencies);
                processBindings(dereferencedVariableName, type, viewData);
            }, BlockFlags::AddIndents);

            AJSONObject values;
            if (viewData.read("Values", values))
            {
                addDependencies(*typeIt->second, dependencies);
                dependencyAdded = true;
                processProperties(dereferencedVariableName, typeIt->second.get(), values, dependencies);
            }

            if (!dependencyAdded)
            {
                addDependencies(viewTypeInfo.Name, dependencies);
            }

            processSubViews(dereferencedVariableName, viewData, ViewsKey, dependencies);
            processSubViews(dereferencedVariableName, viewData, PostViewsKey, dependencies);

            if (!isContentView)
            {
                generateCall(parent + ".addView", { variableName });
            }
        };

        if (isExternal)
        {
            AJSONObject defaultView;
            if (viewData.read("Default", defaultView))
            {
                writeWithIndent("if (" + variableName + ")\r\n");
                generateBlock([&]() {
                    generateCall(parent + ".addView", { variableName });
                }, BlockFlags::AddIndents);

                String defaultViewName;
                if (!defaultView.read("Name", defaultViewName))
                {
                    return false;
                }

                writeWithIndent("else\r\n");
                generateBlock([&]() {
                    if (processSubView(parent, defaultView, dependencies))
                    {
                        generateAssignment(variableName, Str::ToFirstLowerCase(defaultViewName));
                    }
                }, BlockFlags::AddIndents);
            }
        }
        else
        {
            generateSubView();
        }

        return true;
    }

    void generate() override
    {
        constructorDependencies.clear();
        constructorRegion.clear();

        propertyDependencies.clear();
        propertiesRegion.clear();

        addDependencies("SharedReference", constructorDependencies);
        addDependencies("SharedReference", propertyDependencies);

        pushIndent();
        //generate constructor first for collecting dependencies
        generateCall("setName", { Str::Quote(path.baseName()) });
        processSubViews("(*this)", data, ViewsKey, constructorDependencies);
        processSubViews("(*this)", data, PostViewsKey, constructorDependencies);
        constructorRegion = std::move(generatedBuffer);

        processBindingContext("(*this)", data);

        processSubViews("(*this)", data, PreViewsKey, constructorDependencies);
        processContentViews("(*this)", data, constructorDependencies);
        contentRegion = std::move(generatedBuffer);
        popIndent();

        Super::generate();
    }

    void onGenerateHeaderDependencies() override
    {
        Super::onGenerateHeaderDependencies();
        generateIncludes({}, propertyDependencies);
    }

    void onGenerateSourceDependencies() override
    {
        Super::onGenerateSourceDependencies();
        generateIncludes({}, constructorDependencies);
    }

    void onGenerateClassBody(Array<String> &dependencies) override
    {
        Super::onGenerateClassBody(dependencies);

        write(propertiesRegion);
        pushIndent();
        generateFunction("void", "onHierarchyCreate", {});
        popIndent();
    }

    void onGenerateClassSource(Array<String> &dependencies) override
    {
        Super::onGenerateClassSource(dependencies);

        generateMethodImplementation("void", path.baseName(), "onHierarchyCreate", {}, [this]() {
            write(contentRegion);
            generateCall("Super::onHierarchyCreate", {});
            write(constructorRegion);
        });
    }
};

}
