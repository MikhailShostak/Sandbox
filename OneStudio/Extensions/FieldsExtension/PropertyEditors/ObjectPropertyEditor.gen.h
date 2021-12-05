#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

#include "Foundation"
#include "ClassGenExtensions"

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "ClassPicker.gen.h"
#include "ClassSuggestionsComponent.h"
#include "FieldEditors/EmbeddedObjectFieldEditor.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ObjectPropertyEditor : public UI::FlexBox, public FieldEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ObjectPropertyEditor This;
    typedef UI::FlexBox Super;
    typedef std::tuple<FieldEditor> Interfaces;
public:
    ObjectPropertyEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<LegacyClassGen::ClassPicker> classPicker;
    SharedReference<LegacyClassGen::EmbeddedObjectFieldEditor> propertyEditor;
    void onHierarchyCreate();
//CLASSGEN END REGION
    UI::ClassSuggestionsComponent suggestionsComponent;
    void onLoad(ALoadEvent &event);
protected:
    void onSerialize(const AJSONValue &value) override;
    AJSONValue onDeserialize() override;
    
    void updateType();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
