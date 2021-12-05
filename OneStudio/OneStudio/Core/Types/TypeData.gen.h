#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct TypeData : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TypeData This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Text Type;
    Array<Text> Extensions;
    Text AssociatedEditor;
public:
    TypeData();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    TypeData(const Text &Type, const Array<Text> &Extensions = Array<Text>(), const Text &AssociatedEditor = Text()):
        Type(Type),
        Extensions(Extensions),
        AssociatedEditor(AssociatedEditor)
    {}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
