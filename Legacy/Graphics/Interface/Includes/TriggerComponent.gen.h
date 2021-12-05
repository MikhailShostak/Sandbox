#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Component.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Physics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TriggerComponent : public Core::Component
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TriggerComponent This;
    typedef Core::Component Super;
    typedef void Interfaces;
public:
    TriggerComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
