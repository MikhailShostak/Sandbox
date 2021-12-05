//CLASSGEN GENERATED REGION: Includes
#include "BooleanPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
BooleanPropertyEditor::BooleanPropertyEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void BooleanPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void BooleanPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void BooleanPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("BooleanPropertyEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
