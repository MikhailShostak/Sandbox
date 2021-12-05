#pragma once

#include <Experimental>
#include <ClassGenLibrary>

namespace UI
{

struct EditableProperty
{
    AJSONObject data;
    String propertyName;
    LegacyClassGen::TypeInfo typeInfo;

    SharedReference<LegacyClassGen::BaseCGType> type;
    SharedReference<View> propertyEditorView;
    SharedReference<FieldEditor> editor;

    bool isExpanded = false;
    Array<SharedReference<EditableProperty>> embeddedProperties;

    bool isChanged = false;
    ADelegate<void()> onValueChanged;

    void createEditor();
    static SharedReference<EditableProperty> createProperty(const AJSONObject &data, const Map<String, LegacyClassGen::PropertyInfo> &propertyOverrides = {});
    static Array<SharedReference<EditableProperty>> createProperties(const SharedReference<LegacyClassGen::BaseCGType> &typeData, const Map<String, LegacyClassGen::PropertyInfo> &propertyOverrides = {});
};

}

template<typename Functor1, typename Functor2>
inline void walkInheritance(const SharedReference<LegacyClassGen::BaseCGType> &typeData, Functor1 &&descendingCallback, Functor2 &&ascendingCallback)
{
    descendingCallback(typeData);
    String baseType;
    if (typeData->data.read("BaseType", baseType))
    {
        LegacyClassGen::TypeInfo typeInfo;
        readRecursively(baseType, typeInfo);
        
        //TODO: base type is not found
        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeInfo.Name);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            walkInheritance(typeIt->second, std::forward<Functor1>(descendingCallback), std::forward<Functor2>(ascendingCallback));
        }
    }
    ascendingCallback(typeData);
}
