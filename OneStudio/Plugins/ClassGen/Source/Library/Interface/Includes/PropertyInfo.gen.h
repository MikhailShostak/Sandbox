#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "VisibilityType.gen.h"
#include "PropertyAttributes.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct PropertyInfo : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PropertyInfo This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Name;
    String Type;
    Array<String> Parameters;
    Array<String> PreCallbacks;
    Array<String> PostCallbacks;
    LegacyClassGen::VisibilityType Visibility;
    LegacyClassGen::PropertyAttributes Attributes;
    Boolean Variable;
    Boolean CustomGetter;
    Boolean CustomSetter;
public:
    PropertyInfo();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
