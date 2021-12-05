#pragma once

#include "Core/BaseCGType.h"

#include "Includes/PropertyInfo.gen.h"
#include "Includes/FunctionInfo.gen.h"
#include "Includes/EventInfo.gen.h"

namespace LegacyClassGen
{

class ClassCGType : public BaseCGType
{
public:

    using Super = BaseCGType;

    static void processTypeDependencies(const TypeInfo& type, Array<String>& dependencies)
    {
        addDependencies(type.Name, dependencies);
        for (const TypeInfo &t : type.Parameters)
        {
            processTypeDependencies(t, dependencies);
        }
    }

    static void processParameterDependencies(const Parameter& parameter, Array<String>& dependencies)
    {
        processTypeDependencies(parameter.Type, dependencies);
    }

    static void processParametersDependencies(const Array<Parameter>& parameters, Array<String>& dependencies)
    {
        for (const Parameter &p : parameters)
        {
            processParameterDependencies(p, dependencies);
        }
    }

    static void processFunctionDependencies(const FunctionInfo& f, Array<String>& dependencies)
    {
        processParametersDependencies(f.InputArguments, dependencies);
        processParametersDependencies(f.OutputArguments, dependencies);
    }

    static void processPropertiesDependencies(const PropertyInfo &p, Array<String> &dependencies)
    {
        addDependencies(p.Type, dependencies);
        if (!p.Parameters.empty())
        {
            for (auto &t : p.Parameters)
            {
                addDependencies(t, dependencies);
            }
        }
    };

    static void processAllFiles(const Array<SharedReference<ClassCGType>> &classTypes, const APath &source)
    {
        AFile sourceFile;
        if (!sourceFile.open(source + "Classes.h", AFileOpenMode::WriteBinary))
        {
            return;
        }

        sourceFile << "#pragma once\"\r\n";
        sourceFile << "#include \"MetaObject.h\"\r\n";
        sourceFile << "#include \"MetaObjectSerializationHelper.h\"\r\n";
        for (auto &classType : classTypes)
        {
            if (classType->isExternal())
            {
                continue;
            }

            for (auto &importFile : classType->getImportFiles())
            {
                sourceFile << "#include \"" << importFile << "\"\r\n";
            }
        }

        sourceFile << "inline void RegisterMetaClasses()\r\n{\r\n\r\n";
        sourceFile << "MetaObjectManager &manager = MetaObjectManager::getInstance();\r\n";

        for (auto &classType : classTypes)
        {
            if (classType->isExternal())
            {
                continue;
            }

            ALogMessage("", "Process ClassCGType %s", classType->path);
            if (classType->data.hasKey("TemplateTypes"))
            {
                continue;
            }

            if (classType->getBaseType().empty())
            {
                continue; 
            }

            classType->generateMetaTypeRegistration();
            sourceFile << classType->flush();
        }
        sourceFile << "\r\n}\r\n";
    }

    void generateValues(const LegacyClassGen::BaseCGType *typeData, const String &variable, Array<String> &dependencies);

    void generateMetaTypeRegistration()
    {
        String name = getDefaultType(false);
        String resolvedName = resolveType(name);
        String baseType = getBaseType();
        generateBlock([&]() {
            generateField("MetaObject &", "object", "manager.getMetaObject<" + resolvedName + ">()");
            generateAssignment("object.serialize", "[](const AObject &object, AJSONObject &data) { static_cast<const " + resolvedName + "&>(object).serialize(data); }");
            generateAssignment("object.deserialize", "[](const AJSONObject &data, AObject &object) { static_cast<" + resolvedName + "&>(object).deserialize(data); }");
            if (!baseType.empty())
            {
                generateAssignment("object.baseObject", "&manager.getMetaObject<" + resolveType(baseType) + ">()");
            }

            Array<String> attributes;
            data.read("Attributes", attributes);
            bool isStruct = false;
            if (ArrayUtils::FindFirst(attributes, String("Structure")) != size_t(-1))
            {
                isStruct = true;
            }

            AJSONArray properties;
            if (data.read("Properties", properties))
            {
                size_t i = 0;
                for (const AJSONValue &value : properties)
                {
                    PropertyInfo propertyInfo;
                    propertyInfo.deserialize(value.asObject());
                    ++i;

                    String propertyType = addTemplateParameters(resolveType(propertyInfo.Type), resolveTypes(propertyInfo.Parameters));

                    String getter;
                    if (!isStruct)
                    {
                        getter = "&" + resolvedName + "::get" + propertyInfo.Name;
                    }
                    else
                    {
                        getter = "nullptr";
                    }

                    String setter;
                    if (!isStruct && !(propertyInfo.Attributes & PropertyAttributes::ReadOnly))
                    {
                        setter = "&" + resolvedName + "::set" + propertyInfo.Name;
                    }
                    else
                    {
                        setter = "nullptr";
                    }

                    String method = addTemplateParameters("object.registerMetaProperty", {
                        resolvedName,
                        propertyType,
                        propertyType + "(" + resolvedName + "::*)() const",
                        "void(" + resolvedName + "::*)(const " + propertyType + " &)"
                    });

                    generateCall(method, { Str::Quote(propertyInfo.Name), getter, setter, "true" });
                }
            }
            generateCall("manager.registerMetaObject", { Str::Quote(name), "object" });
        }, BlockFlags::AddIndents);
    }

    virtual void onGenerateHeaderDependencies() {}
    virtual void onGenerateSourceDependencies() {}
    virtual void onGenerateConstructor(Array<String> &dependencies) {}
    virtual void onGenerateClassBody(Array<String> &dependencies) {}
    virtual void onGenerateClassSource(Array<String> &dependencies) {}

    void generate() override;

    String generateInitialization(const LegacyClassGen::TypeInfo &typeInfo, const AJSONValue &value, const String &indent, const String &variableName, Array<String> &dependencies) override;
};

}
