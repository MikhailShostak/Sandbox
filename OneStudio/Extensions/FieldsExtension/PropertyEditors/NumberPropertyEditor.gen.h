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
class NumberPropertyEditor : public UI::TextField, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef NumberPropertyEditor This;
    typedef UI::TextField Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    NumberPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    AJSONValue value;
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
            notifyValueChange();
        });
    }
protected:
    virtual void onSerialize(const AJSONValue &value) override { setText(Str::ToString(value.toNumber())); }
    virtual AJSONValue onDeserialize() override { return !getText().empty() ? Str::To<double>(getText()) : 0.0; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
