#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "CompilerSettings.gen.h"
#include "CompilationSettings.gen.h"
#include "ArchiverSettings.gen.h"
#include "LinkerSettings.gen.h"
#include "LinkageSettings.gen.h"
#include "FilesSettings.gen.h"

//CLASSGEN END REGION
#include <Data>
//CLASSGEN GENERATED REGION: Namespace
namespace BuildSystem
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct BuildingSettings : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef BuildingSettings This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    BuildSystem::CompilerSettings CompilerSettings;
    BuildSystem::CompilationSettings CompilationSettings;
    BuildSystem::ArchiverSettings ArchiverSettings;
    BuildSystem::LinkerSettings LinkerSettings;
    BuildSystem::LinkageSettings LinkageSettings;
    BuildSystem::FilesSettings FilesSettings;
public:
    BuildingSettings();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
