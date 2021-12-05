#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "Component.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Entity : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Entity This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    Array<::SharedReference<Core::Component>> Components;
public:
    Entity();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<::SharedReference<Core::Component>> getComponents() const;
    void setComponents(Array<::SharedReference<Core::Component>> const &Components);
    void setComponents(Array < ::SharedReference<Core::Component>> &&Components);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
