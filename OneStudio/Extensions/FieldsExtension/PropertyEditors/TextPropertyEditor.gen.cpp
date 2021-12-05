//CLASSGEN GENERATED REGION: Includes
#include "TextPropertyEditor.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TextPropertyEditor::TextPropertyEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TextPropertyEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TextPropertyEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TextPropertyEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TextPropertyEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
