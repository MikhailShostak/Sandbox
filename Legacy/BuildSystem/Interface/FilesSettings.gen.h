#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include <Data>
//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct FilesSettings : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FilesSettings This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Legacy::String ObjectFileName;
    Legacy::String StaticLibraryFileName;
    Legacy::String DynamicLibraryFileName;
    Legacy::String ApplicationFileName;
    Legacy::String DebugSymbolsFileName;
public:
    FilesSettings();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
