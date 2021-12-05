//CLASSGEN GENERATED REGION: Includes
#include "ExtensionEditor.gen.h"
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
ExtensionEditor::ExtensionEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ExtensionEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ExtensionEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ExtensionEditor");
}
//CLASSGEN END REGION

void ExtensionEditor::onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type)
{

}

void ExtensionEditor::onSave(AJSONObject &data)
{

}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
