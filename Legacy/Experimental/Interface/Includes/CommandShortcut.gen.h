#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <Graphics>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct CommandShortcut : public Core::Shortcut
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef CommandShortcut This;
    typedef Core::Shortcut Super;
    typedef void Interfaces;
public:
    String Command;
    Array<String> Arguments;
public:
    CommandShortcut();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
