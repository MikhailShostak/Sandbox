//CLASSGEN GENERATED REGION: Includes
#include "FlagsPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FlagsPropertyEditor::FlagsPropertyEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FlagsPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FlagsPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FlagsPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("FlagsPropertyEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
