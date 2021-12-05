#include "Core/BaseCGType.h"

#include "Types/Class/ClassManager.h"
#include "Includes/PropertyAttributes.gen.h"

namespace LegacyClassGen
{

//TODO: make it thread-safe
String getNextIdentifier()
{
    static size_t identifier = 0;
    return Str::ToString(identifier++);
}

void BaseCGType::addDependencies(const BaseCGType &type, Array<String> &dependencies)
{
    const Array<String> &names = type.getImportFiles();
    for (const String &name : names)
    {
        if (ranges::find(dependencies, name) == dependencies.end())
        {
            dependencies.push_back(name);
        }
    }
}

void BaseCGType::addDependencies(const String &typeName, Array<String> &dependencies)
{
    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeName);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        addDependencies(*typeIt->second, dependencies);
    }
};

void BaseCGType::addDependencies(const Array<String> &typeNames, Array<String> &dependencies)
{
    for (const String &typeName : typeNames)
    {
        addDependencies(typeName, dependencies);
    }
}

void BaseCGType::processProperties(const String &variable, const LegacyClassGen::BaseCGType *typeData, const AJSONObject &values, Array<String> &dependencies)
{
    String baseType;
    if (typeData->data.read("BaseType", baseType))
    {
        LegacyClassGen::TypeInfo baseTypeInfo;
        if (!baseType.empty())
        {
            readRecursively(baseType, baseTypeInfo);
        }

        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(baseTypeInfo.Name);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            processProperties(variable, typeIt->second.get(), values, dependencies);
        }
    }

    bool isStruct = false;

    Array<String> attributes;
    typeData->data.read("Attributes", attributes);
    if (ranges::find(attributes, "Structure") != attributes.end())
    {
        isStruct = true;
    }

    AJSONArray propertiesData;
    typeData->data.read("Properties", propertiesData);
    for (const AJSONValue &propertyData : propertiesData)
    {
        if (!propertyData.isObject())
        {
            continue;
        }

        const AJSONObject &object = propertyData.toObject();

        String propertyName;
        object.read("Name", propertyName);

        LegacyClassGen::PropertyAttributes propertyAttributes;
        AJSONValue propertyAttributesData;
        object.read("Attributes", propertyAttributesData);
        fromJSONValue(propertyAttributesData, propertyAttributes);

        String propertyType;
        object.read("Type", propertyType);

        LegacyClassGen::TypeInfo typeInfo;
        readRecursively(propertyType, typeInfo);

        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeInfo.Name);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            const SharedReference<LegacyClassGen::BaseCGType> &type = typeIt->second;

            addDependencies(*type, dependencies);

            const bool isReadOnly = bool(propertyAttributes & LegacyClassGen::PropertyAttributes::ReadOnly);
            const bool isSerialized = bool(propertyAttributes & LegacyClassGen::PropertyAttributes::Serialized);
            const bool isMapped = bool(propertyAttributes & LegacyClassGen::PropertyAttributes::Mapped);
            if ((isReadOnly || !isSerialized) && variable != "(*this)")
            {
                continue;
            }

            if (isReadOnly && isMapped)
            {
                continue;
            }

            auto valueIt = values.find(propertyName);
            if (valueIt == values.end())
            {
                continue;
            }

            const AJSONValue &value = valueIt->second;

            AJSONArray parameters;
            object.read("Parameters", parameters);
            String propertyVariable = type->generateInitialization(typeInfo, !parameters.empty() ? AJSONValue(AJSONArray{ parameters, value }) : value, this->indent, Str::ToFirstLowerCase(propertyName) + "_" + getNextIdentifier(), dependencies);
            
            if (!type->generatedBuffer.empty())
            {
                write(type->flush());
            }

            if (!propertyVariable.empty())
            {
                if (isStruct || isReadOnly)
                {
                    generateAssignment(variable + "." + propertyName, propertyVariable);
                }
                else
                {
                    generateCall(variable + ".set" + propertyName, { propertyVariable });
                }
            }
        }

        /*//TODO: property type is not found

        if (!editableProperty->embeddedProperties)
        {
            auto editorAndView = createEditorForProperty(editableProperty);
            editableProperty->editor = editorAndView.first;
            editableProperty->propertyEditorView = editorAndView.second;
        }

        properties.append(editableProperty);*/
    }
}

}
