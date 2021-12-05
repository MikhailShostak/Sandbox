//CLASSGEN GENERATED REGION: Includes
#include "LogicEditor.gen.h"
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
LogicEditor::LogicEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void LogicEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void LogicEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void LogicEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("LogicEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
