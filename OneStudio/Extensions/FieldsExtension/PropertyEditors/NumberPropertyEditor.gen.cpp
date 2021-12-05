//CLASSGEN GENERATED REGION: Includes
#include "NumberPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
NumberPropertyEditor::NumberPropertyEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NumberPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void NumberPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NumberPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("NumberPropertyEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
