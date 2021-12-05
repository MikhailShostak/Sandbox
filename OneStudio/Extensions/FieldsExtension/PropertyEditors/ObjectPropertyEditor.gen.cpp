//CLASSGEN GENERATED REGION: Includes
#include "ObjectPropertyEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ClassGenExtensions"
#include "MathClasses"
#include "ExperimentalDebug"
#include "Math"

//CLASSGEN END REGION
//#include <OneStduioPlatform>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ObjectPropertyEditor::ObjectPropertyEditor()
{
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    (*this).setData({item_0_0,item_1_1,});
    (*this).setDirection(UI::Direction::Vertical);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ObjectPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ObjectPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ObjectPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ObjectPropertyEditor");
    classPicker = CreateShared<LegacyClassGen::ClassPicker>([this](LegacyClassGen::ClassPicker *v)
    {
    }
);
    (*classPicker).setName("ClassPicker");
    {
    }
    (*classPicker).setAffectsParentLayout(true);
    (*this).addView(classPicker);
    propertyEditor = CreateShared<LegacyClassGen::EmbeddedObjectFieldEditor>([this](LegacyClassGen::EmbeddedObjectFieldEditor *v)
    {
    }
);
    (*propertyEditor).setName("PropertyEditor");
    {
    }
    (*propertyEditor).setAffectsParentLayout(true);
    (*this).addView(propertyEditor);
}
//CLASSGEN END REGION

void ObjectPropertyEditor::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    suggestionsComponent.findAsset = true;
    suggestionsComponent.addView(*classPicker->textField);

    classPicker->textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
        updateType();
        notifyValueChange();
    });
    propertyEditor->onValueChanged = [this]() {
        ALogMessage("", "Property changed");
        notifyValueChange();
    };
}

void ObjectPropertyEditor::onSerialize(const AJSONValue &value)
{
    if(value.isString())
    {
        classPicker->textField->setText(value.toString());
        updateType();
    }
    else if (value.isObject())
    {
        const APair<String, AJSONValue> &data = *value.asObject().begin();
        
        String baseType = data.first;
        classPicker->textField->setText(baseType);
        updateType();
        propertyEditor->serializeValue(data.second);
    }
}

AJSONValue ObjectPropertyEditor::onDeserialize()
{
    String typeName = classPicker->textField->getText();

    AJSONValue data;
    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeName);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        if (typeIt->second->group == CGTypeGroup::Asset)
        {
            data = typeName;
        }
        else
        {
            AJSONObject object;
            object.insert(typeName, propertyEditor->deserializeValue(), false);
            data = object;
        }
    }
    return data;
}

void ObjectPropertyEditor::updateType()
{
    String typeName = classPicker->textField->getText();

    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeName);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        if (typeIt->second->group == CGTypeGroup::Asset)
        {
            propertyEditor->setType(nullptr, {});
            propertyEditor->collapse();
        }
        else
        {
            propertyEditor->setType(typeName);
            propertyEditor->expand();
        }
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
