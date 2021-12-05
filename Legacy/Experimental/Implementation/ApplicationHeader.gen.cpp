//CLASSGEN GENERATED REGION: Includes
#include "ApplicationHeader.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationHeader::ApplicationHeader()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationHeader::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationHeader::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationHeader::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ApplicationHeader");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
