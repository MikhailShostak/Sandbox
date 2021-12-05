//CLASSGEN GENERATED REGION: Includes
#include "EmbeddedObjectFieldEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EmbeddedObjectFieldEditor::EmbeddedObjectFieldEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EmbeddedObjectFieldEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EmbeddedObjectFieldEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
const String &EmbeddedObjectFieldEditor::getOriginalPropertyName(const String &name) const
{
    auto it = std::find_if(propertyOverrides.begin(), propertyOverrides.end(), [&](const auto &item) {
        return item.second.Name == name;
    });

    if (it != propertyOverrides.end())
    {
        return it->first;
    }

    return name;
}

LegacyClassGen::PropertyInfo &EmbeddedObjectFieldEditor::overrideProperty(const LegacyClassGen::PropertyInfo &property, const String &name)
{
    auto it = std::find_if(propertyOverrides.begin(), propertyOverrides.end(), [&](const auto &item) {
        return item.second.Name == name;
    });

    if (it != propertyOverrides.end())
    {
        return it->second;
    }

    propertyOverrides.insert({ name, property });

    return propertyOverrides[name];
};

void EmbeddedObjectFieldEditor::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if (!getProxyAdapter())
    {
        setProxyAdapter(this);
    }
    setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
}


SharedReference<UI::View> EmbeddedObjectFieldEditor::provideViewForItem(const AObject &sender, UI::SizeType depth, UI::EditableProperty *item)
{
    if (!item->propertyEditorView)
    {
        SharedReference<UI::DefaultExpandableItemView> sharedV = CreateShared<UI::DefaultExpandableItemView>();
        WeakReference<UI::DefaultExpandableItemView> v = sharedV;
        sharedV->applyParameters(depth, item->propertyName, !item->embeddedProperties.empty());
        if (item->isExpanded)
        {
            sharedV->expandButton->setBackgroundImage(MinusButtonSmall);
        }
        else
        {
            sharedV->expandButton->setBackgroundImage(PlusButtonSmall);
        }
        sharedV->icon->collapse();
        sharedV->expandButton->eventChannel.registerDelegate([this, v, item](UI::TapGestureEvent &event) {
            item->isExpanded = !item->isExpanded;
            if (item->isExpanded)
            {
                v.lock()->expandButton->setBackgroundImage(MinusButtonSmall);
            }
            else
            {
                v.lock()->expandButton->setBackgroundImage(PlusButtonSmall);
            }
            this->notifyUpdateChildren(item);
        });
        return sharedV;
    }

    return item->propertyEditorView;
}

void EmbeddedObjectFieldEditor::setType(const String &name)
{
    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(name);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        setType(typeIt->second, {});
    }
    else
    {
        setType(nullptr, {});
    }
}

void EmbeddedObjectFieldEditor::setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo)
{
    if (!getProxyAdapter())
    {
        //this code is added because onLoad happens too late
        setProxyAdapter(this);
    }
    properties.clear();

    if (type != nullptr)
    {
        properties = UI::EditableProperty::createProperties(type, propertyOverrides);
        for (const SharedReference<UI::EditableProperty> &property : properties)
        {
            auto propertyPtr = property.get();
            property->onValueChanged = [this, propertyPtr]() {
                ALogMessage("", "Property %s is changed in EmbeddedObjectFieldEditor", propertyPtr->propertyName);
                notifyValueChange();
            };
        }
        notifyUpdateAllItems();
    }
}

void EmbeddedObjectFieldEditor::serializeInternal(const AJSONObject &data, const Array<SharedReference<UI::EditableProperty>> &properties)
{
    for (auto &property : properties)
    {
        const String &propertyName = &properties == &this->properties ? getOriginalPropertyName(property->propertyName) : property->propertyName;
        if (!property->embeddedProperties.empty())
        {
            AJSONObject values;
            data.read(propertyName, values);
            serializeInternal(values, property->embeddedProperties);
            continue;
        }

        auto it = data.find(propertyName);
        if (it != data.end())
        {
            if(!property->editor)
            {
                Log::Print("Editor doesn't exists for property \"{}\"", propertyName);
                continue;
            }
            property->editor->serializeValue(it->second);
        }
    }
};

AJSONObject EmbeddedObjectFieldEditor::deserializeInternal(const Array<SharedReference<UI::EditableProperty>> &properties)
{
    AJSONObject data;
    for (auto &property : properties)
    {
        if (!property->embeddedProperties.empty())
        {
            data.insert(property->propertyName, deserializeInternal(property->embeddedProperties));
            continue;
        }

        SharedReference<FieldEditor> editor = property->editor;
        if (!editor)
        {
            continue;
        }
        AJSONValue value = editor->deserializeValue();
        if (value.isValid())
        {
            data.insert(property->propertyName, value, false);
        }
    }
    return data;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
