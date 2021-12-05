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
class TextPropertyEditor : public UI::TextField, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TextPropertyEditor This;
    typedef UI::TextField Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    TextPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            notifyValueChange();
        });
    }
protected:
    void onSerialize(const AJSONValue &value) override { setText(value.toString()); }
    AJSONValue onDeserialize() override { return getText(); }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
