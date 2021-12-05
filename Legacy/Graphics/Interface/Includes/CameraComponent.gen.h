#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Component.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Legacy::Graphics
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class CameraComponent : public Core::Component
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef CameraComponent This;
    typedef Core::Component Super;
    typedef void Interfaces;
public:
    CameraComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
