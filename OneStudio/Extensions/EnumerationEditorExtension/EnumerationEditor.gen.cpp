//CLASSGEN GENERATED REGION: Includes
#include "EnumerationEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
EnumerationEditor::EnumerationEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnumerationEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void EnumerationEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void EnumerationEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("EnumerationEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
