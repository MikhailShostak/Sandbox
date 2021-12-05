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
class ArrayPropertyEditor : public UI::FlexBox, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ArrayPropertyEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    ArrayPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::TextButton> button;
    SharedReference<UI::ListView> list;
    void onHierarchyCreate();
//CLASSGEN END REGION
    Array<APair<SharedReference<FieldEditor>, SharedReference<UI::View>>> items;
    SharedReference<LegacyClassGen::BaseCGType> type;
    LegacyClassGen::TypeInfo itemTypeInfo;
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
            auto editorAndView = LegacyClassGen::Context::getInstance().createFieldEditorAndView(Str::ToString(items.size()), itemTypeInfo, type);
            editorAndView.first->onValueChanged = [this]() {
                notifyValueChange();
            };
            items.push_back(editorAndView);
            list->notifyInsertItems(items.size() - 1);
            notifyValueChange();
        });
    }
    
    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) override
    {
        if (!typeInfo.Parameters.empty())
        {
            itemTypeInfo = typeInfo.Parameters[0];
            auto it = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(itemTypeInfo.Name);
            if (it != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
            {
                this->type = it->second;
            }
        }
    }

    virtual UI::SizeType getCountItems(const AObject &sender) const { return items.size(); }
    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index)
    {
        //SharedReference<View> view = .cast<View>();
        //view->setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);
        return items[index].second;
    }

    void onSerialize(const AJSONValue &value) override
    {
        if (!value.isArray())
        {
            return;
        }

        const AJSONArray &data = value.asArray();
        for (const AJSONValue &itemValue : data)
        {
            auto editorAndView = LegacyClassGen::Context::getInstance().createFieldEditorAndView(Str::ToString(items.size()), itemTypeInfo, type);
            editorAndView.first->onValueChanged = [this]() {
                notifyValueChange();
            };
            editorAndView.first->serializeValue(itemValue);
            //TODO: temporary solution for reducing label space
            editorAndView.second->getViews()[0]->setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
            items.push_back(editorAndView);
        }

        list->notifyUpdateAllItems();
    }

    AJSONValue onDeserialize() override
    {
        AJSONArray data;
        for (auto &item : items)
        {
            AJSONValue v = item.first->deserializeValue();
            if (!v)
            {
                if (type->group == LegacyClassGen::CGTypeGroup::Object)
                {
                    v = AJSONObject();
                }
            }
            data.push_back(v);
        }
        return data;
    }

    FieldEditorLayoutType getLayoutType() const { return Multiline; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
