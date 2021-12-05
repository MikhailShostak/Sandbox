//CLASSGEN GENERATED REGION: Includes
#include "EnumerationPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EnumerationPropertyEditor::EnumerationPropertyEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnumerationPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EnumerationPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnumerationPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("EnumerationPropertyEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
