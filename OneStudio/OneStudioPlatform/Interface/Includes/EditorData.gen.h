#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "EditorInstance.gen.h"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct EditorData : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EditorData This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Text Identifier;
    Array<Text> SuppoertedTypes;
    SharedReference<OneStudioPlatform::EditorInstance> Instance;
public:
    EditorData();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    EditorData(const Text &Identifier, const Array<Text> &SuppoertedTypes = Array<Text>(), const SharedReference<OneStudioPlatform::EditorInstance> &Instance = nullptr):
        Identifier(Identifier),
        SuppoertedTypes(SuppoertedTypes),
        Instance(Instance)
    {}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
