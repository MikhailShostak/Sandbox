#include "EditableProperty.h"
#include "AJSONObject.h"

namespace UI
{

void EditableProperty::createEditor()
{
    //TODO: remove parameters field from files
    Array<String> parameters;
    if(data.read("Parameters", parameters))
    {
        typeInfo.Parameters.clear();
        for(auto &p : parameters)
        {
            LegacyClassGen::TypeInfo info;
            info.Name = p;
            typeInfo.Parameters.push_back(info);
        }
    }

    auto editorAndView = LegacyClassGen::Context::getInstance().createFieldEditorAndView(this->propertyName, this->typeInfo, this->type);

    this->editor = editorAndView.first;
    this->editor->onValueChanged = [this]() {
        ALogMessage("", "Property \"%s\" is changed in a field editor", propertyName);
        isChanged = true;
        onValueChanged();
    };
    this->propertyEditorView = editorAndView.second;
}

SharedReference<EditableProperty> EditableProperty::createProperty(const AJSONObject &data, const Map<String, LegacyClassGen::PropertyInfo> &propertyOverrides)
{
    SharedReference<EditableProperty> editableProperty = CreateShared<EditableProperty>();
    data.read("Name", editableProperty->propertyName);
    
    String typeName;
    if (!propertyOverrides.empty() && propertyOverrides.find(editableProperty->propertyName) != propertyOverrides.end())
    {
        auto p = propertyOverrides.at(editableProperty->propertyName);
        editableProperty->propertyName = p.Name;
        typeName = p.Type;
    }
    else
    {
        data.read("Type", typeName);
    }
    editableProperty->data = data;
    readRecursively(typeName, editableProperty->typeInfo);

    //TODO: property type is not found
    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(editableProperty->typeInfo.Name);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        editableProperty->type = typeIt->second;
        if (!LegacyClassGen::Context::getInstance().canCreateEditorForInstance(editableProperty->typeInfo.Name))
        {
            editableProperty->embeddedProperties = createProperties(editableProperty->type);
            for (const SharedReference<EditableProperty> &property : editableProperty->embeddedProperties)
            {
                auto propertyPtr = property.get();
                property->onValueChanged = [propertyPtr, editableProperty]() {
                    ALogMessage("", "Embedded property \"%s.%s\" is changed in a property editor", editableProperty->propertyName, propertyPtr->propertyName);
                    editableProperty->isChanged = true;
                    if (editableProperty->onValueChanged)
                    {
                        editableProperty->onValueChanged();
                    }
                };
            }
        }
    }

    if (editableProperty->embeddedProperties.empty())
    {
        //AAssert(editableProperty->type, "Type %s is not found for property %s", editableProperty->typeName.toUtf8().data(), editableProperty->propertyName.toUtf8().data());
        if (editableProperty->type)
        {
            editableProperty->createEditor();
        }
    }

    return editableProperty;
}

void fillDafaultValues(const Array<SharedReference<EditableProperty>> &properties, const AJSONObject &values)
{
    for(auto &p : properties)
    {
        AJSONValue v;
        if(values.read(p->propertyName, v))
        {
            if(!p->embeddedProperties.empty())
            {
                fillDafaultValues(p->embeddedProperties, v.toObject());
            }
            else
            {
                if(p->editor)
                {
                    p->editor->setDefaultValue(v);
                }
                else
                {
                    Log::Print("Warning: Editor is not found, please investigate...");
                }
            }
        }
    }
}

Array<SharedReference<EditableProperty>> EditableProperty::createProperties(const SharedReference<LegacyClassGen::BaseCGType> &typeData, const Map<String, LegacyClassGen::PropertyInfo> &propertyOverrides)
{
    Array<SharedReference<EditableProperty>> properties;

    /*String baseType;
    if (typeData->data.read("BaseType", baseType))
    {
        LegacyClassGen::TypeInfo typeInfo;
        readRecursively(baseType, typeInfo);
        //TODO: base type is not found
        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeInfo.Name);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            properties = createProperties(typeIt->second);
        }
    }*/

    AJSONObject values;
    walkInheritance(typeData, [&](const SharedReference<LegacyClassGen::BaseCGType> &baseTypeData) {
        AJSONObject valuesData;
        baseTypeData->data.read("Values", valuesData);
        for (const auto &p : valuesData)
        {
            if(!values.hasKey(p.first))
            {
                values.insert(p.first, p.second);
            }
        }
    }, [&](const SharedReference<LegacyClassGen::BaseCGType> &baseTypeData) {

        AJSONArray propertiesData;
        baseTypeData->data.read("Properties", propertiesData);
        for (const AJSONValue &value : propertiesData)
        {
            if (!value.isObject())
            {
                continue;
            }
            auto editableProperty = createProperty(value.toObject(), propertyOverrides);
            properties.push_back(editableProperty);
        }
    });

    fillDafaultValues(properties, values);

    return properties;
}

}
