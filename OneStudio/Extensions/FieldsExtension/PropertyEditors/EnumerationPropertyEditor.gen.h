#pragma once

//CLASSGEN GENERATED REGION: Includes
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
class EnumerationPropertyEditor : public UI::DropDownList, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EnumerationPropertyEditor This;
    typedef UI::DropDownList Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    EnumerationPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    Array<String> values;
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        eventChannel.registerDelegate([this](UI::CurrentIndexChangedEvent &event) {
            notifyValueChange();
        });
    }
    
    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type, const LegacyClassGen::TypeInfo &typeInfo) override
    {
        type->data.read("Values", values);
        setElements(values);
        setCurrentIndex(0);
    }

    void onSerialize(const AJSONValue &value) override
    {
        size_t index = ArrayUtils::FindFirst(values, value.toString());
        setCurrentIndex(index != size_t(-1) ? index : 0);
    }

    AJSONValue onDeserialize() override
    {
        if (getCurrentIndex() == -1)
        {
            return AJSONValue();
        }

        return values[getCurrentIndex()];
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
