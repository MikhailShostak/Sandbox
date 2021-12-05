#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

//CLASSGEN END REGION
#include <ClassGenLibrary>

#include "EditableProperty.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class EmbeddedObjectFieldEditor : public UI::TreeView<UI::EditableProperty>, public UI::TreeAdapter<UI::EditableProperty>, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EmbeddedObjectFieldEditor This;
    typedef UI::TreeView<UI::EditableProperty> Super;
    typedef std::tuple<UI::TreeAdapter<UI::EditableProperty>, FieldEditor> Interfaces;
public:
    EmbeddedObjectFieldEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
public:

    Array<SharedReference<UI::EditableProperty>> properties;
    Map<String, LegacyClassGen::PropertyInfo> propertyOverrides;

    const String &getOriginalPropertyName(const String &name) const;
    LegacyClassGen::PropertyInfo &overrideProperty(const LegacyClassGen::PropertyInfo &property, const String &name);
    void onLoad(ALoadEvent &event);

    UI::SizeType getCountRootItems() const override { return properties.size(); }
    UI::EditableProperty *getRootItem(UI::SizeType index) override { return properties[index].get(); }
    UI::SizeType getCountChildItems(UI::EditableProperty *parentItem) const override { return parentItem->isExpanded ? parentItem->embeddedProperties.size() : 0; }
    UI::EditableProperty *getChildItem(UI::EditableProperty *parentItem, UI::SizeType index) override { return parentItem->embeddedProperties[index].get(); }
    SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType depth, UI::EditableProperty *item) override;
    void setType(const String &name);
    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) override;

    void onSerialize(const AJSONValue &value) override { serializeInternal(value.toObject(), properties); }
    AJSONValue onDeserialize() override { return deserializeInternal(properties); }

    void serializeInternal(const AJSONObject &data, const Array<SharedReference<UI::EditableProperty>> &properties);
    AJSONObject deserializeInternal(const Array<SharedReference<UI::EditableProperty>> &properties);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
