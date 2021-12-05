#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "PackageInfo.gen.h"

//CLASSGEN END REGION
#include "ExtensionLibrary.gen.h"

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DeveloperLibrary : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DeveloperLibrary This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    Array<OneStudio::PackageInfo> Packages;
Path LibraryPath;
public:
    DeveloperLibrary();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<OneStudio::PackageInfo> getPackages() const;
    void setPackages(Array<OneStudio::PackageInfo> const &Packages);
    void setPackages(Array<OneStudio::PackageInfo> &&Packages);
    Path getLibraryPath() const;
    void setLibraryPath(Path const &LibraryPath);
    void setLibraryPath(Path &&LibraryPath);
//CLASSGEN END REGION
public:
    PluginLibrary<OSPlugin> pluginLibrary;
    void load();
    void unload();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
