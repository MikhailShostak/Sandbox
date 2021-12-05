//CLASSGEN GENERATED REGION: Includes
#include "Space.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Space::Space()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Space::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void Space::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<SharedReference<Core::Entity>> Space::getEntities() const
{
    return this->Entities;
}
void Space::setEntities(Array<SharedReference<Core::Entity>> const &Entities)
{
    this->Entities = Entities;
}
void Space::setEntities(Array<SharedReference<Core::Entity>> &&Entities)
{
    this->Entities = std::move(Entities);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
