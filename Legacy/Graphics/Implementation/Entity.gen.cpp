//CLASSGEN GENERATED REGION: Includes
#include "Entity.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Entity::Entity()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Entity::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void Entity::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<::SharedReference<Core::Component>> Entity::getComponents() const
{
    return this->Components;
}
void Entity::setComponents(Array<::SharedReference<Core::Component>> const &Components)
{
    this->Components = Components;
}
void Entity::setComponents(Array<::SharedReference<Core::Component>> &&Components)
{
    this->Components = std::move(Components);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
