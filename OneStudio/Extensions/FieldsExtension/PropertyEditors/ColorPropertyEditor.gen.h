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
class ColorPropertyEditor : public UI::ListView, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ColorPropertyEditor This;
    typedef UI::ListView Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    ColorPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    AJSONValue value;
    void onSerialize(const AJSONValue &value) override { this->value = value; }
    AJSONValue onDeserialize() override { return value; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
