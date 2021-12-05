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
class BooleanPropertyEditor : public UI::Switch, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef BooleanPropertyEditor This;
    typedef UI::Switch Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    BooleanPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        eventChannel.registerDelegate([this](UI::UserSwitchEvent &event) {
            notifyValueChange();
        });
    }
protected:
    void onSerialize(const AJSONValue &value) override { setOn(value.toBoolean()); }
    AJSONValue onDeserialize() override { return isOn(); }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
