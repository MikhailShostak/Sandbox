#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

#include "Foundation"
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DictionaryPropertyEditor : public UI::FlexBox, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DictionaryPropertyEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    DictionaryPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::TextButton> button;
    SharedReference<UI::ListView> list;
    void onHierarchyCreate();
//CLASSGEN END REGION
    struct KeyValue
    {
        SharedReference<FieldEditor> keyEditor;
        SharedReference<FieldEditor> valueEditor;
    };
    Array<KeyValue> items;
    SharedReference<LegacyClassGen::BaseCGType> keyType;
    SharedReference<LegacyClassGen::BaseCGType> valueType;
    LegacyClassGen::TypeInfo keyTypeInfo;
    LegacyClassGen::TypeInfo valueTypeInfo;

    bool initialized = false;

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        if (initialized)
        {
            return;
        }
        initialized = true;

        button->eventChannel.registerDelegate([this](UI::TapGestureEvent &event) {
            auto keyEditor = LegacyClassGen::Context::getInstance().createFieldEditor(keyTypeInfo, keyType);
            keyEditor->onValueChanged = [this]() {
                notifyValueChange();
            };
            auto valueEditor = LegacyClassGen::Context::getInstance().createFieldEditor(valueTypeInfo, valueType);
            valueEditor->onValueChanged = [this]() {
                notifyValueChange();
            };
            items.push_back({ keyEditor, valueEditor });
            list->notifyInsertItems(items.size() - 1);
            notifyValueChange();
        });
    }

    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) override
    {
        if (!typeInfo.Parameters.empty())
        {
            keyTypeInfo = typeInfo.Parameters[0];
            auto it = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(keyTypeInfo.Name);
            if (it != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                this->keyType = it->second;
            }

            if (typeInfo.Parameters.size() > 1)
            {
                valueTypeInfo = typeInfo.Parameters[1];
                it = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(valueTypeInfo.Name);
                if (it != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
                {
                    this->valueType = it->second;
                }
            }
        }
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return items.size(); }
    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        SharedReference<FlexBox> box = CreateShared<UI::FlexBox>();
        SharedReference<View> keyView = DynamicCast<View>(items[index].keyEditor);
        keyView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        box->addView(keyView);

        SharedReference<View> valueView = DynamicCast<View>(items[index].valueEditor);
        valueView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        box->addView(valueView);

        box->setData({ {}, {} });
        box->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);

        return box;
    }

    virtual void onSerialize(const AJSONValue &value) override
    {
        if (!value.isArray())
        {
            return;
        }

        const AJSONArray &data = value.asArray();
        for (const AJSONValue &keyValue : data)
        {
            if (!keyValue.isArray() || keyValue.asArray().size() < 2)
            {
                continue;
            }

            const AJSONArray &keyValueData = keyValue.asArray();

            auto keyEditor = LegacyClassGen::Context::getInstance().createFieldEditor(keyTypeInfo, keyType);
            keyEditor->onValueChanged = [this]() {
                notifyValueChange();
            };
            auto valueEditor = LegacyClassGen::Context::getInstance().createFieldEditor(valueTypeInfo, valueType);
            valueEditor->onValueChanged = [this]() {
                notifyValueChange();
            };

            KeyValue keyValueEditors = { keyEditor, valueEditor };
            keyValueEditors.keyEditor->serializeValue(keyValueData[0]);
            keyValueEditors.valueEditor->serializeValue(keyValueData[1]);
            items.push_back(keyValueEditors);
        }

        list->notifyUpdateAllItems();
    }

    virtual AJSONValue onDeserialize() override
    {
        AJSONArray data;
        for (auto &item : items)
        {
            AJSONArray keyValueData;
            keyValueData.push_back(item.keyEditor->deserializeValue());
            AJSONValue v = item.valueEditor->deserializeValue();
            if (!v)
            {
                if (valueType->group == LegacyClassGen::CGTypeGroup::Object)
                {
                    v = AJSONObject();
                }
            }
            keyValueData.push_back(v);
            data.push_back(AJSONValue(keyValueData));
        }
        return data;
    }

    FieldEditorLayoutType getLayoutType() const { return Multiline; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
