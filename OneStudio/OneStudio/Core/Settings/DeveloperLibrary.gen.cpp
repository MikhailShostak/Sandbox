//CLASSGEN GENERATED REGION: Includes
#include "DeveloperLibrary.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include <Experimental>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
DeveloperLibrary::DeveloperLibrary()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DeveloperLibrary::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DeveloperLibrary::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<OneStudio::PackageInfo> DeveloperLibrary::getPackages() const
{
    return this->Packages;
}
void DeveloperLibrary::setPackages(Array<OneStudio::PackageInfo> const &Packages)
{
    this->Packages = Packages;
}
void DeveloperLibrary::setPackages(Array<OneStudio::PackageInfo> &&Packages)
{
    this->Packages = std::move(Packages);
}
Path DeveloperLibrary::getLibraryPath() const
{
    return this->LibraryPath;
}
void DeveloperLibrary::setLibraryPath(Path const &LibraryPath)
{
    this->LibraryPath = LibraryPath;
}
void DeveloperLibrary::setLibraryPath(Path &&LibraryPath)
{
    this->LibraryPath = std::move(LibraryPath);
}
//CLASSGEN END REGION

void DeveloperLibrary::load()
{
    APathInfo info(LibraryPath);
    if (!info.isExists())
    {
        return;
    }

    if(!pluginLibrary.getDirectory().size())
    {
        pluginLibrary.setDirectory(LibraryPath + "../Extensions");
    }
    pluginLibrary.reload();

    ADirectory dir(info);
    for (auto &package : dir)
    {
        if (package.empty() || package == "." || package == "..")
        {
            continue;
        }

        PackageInfo packageInfo{};
        packageInfo.PackagePath = LibraryPath + package;
        if (!APathInfo(packageInfo.PackagePath).isDirectory())
        {
            continue;
        }

        ADirectory packageDir(packageInfo.PackagePath);
        for (auto &version : packageDir)
        {
            if (version.empty() || version == "." || version == "..")
            {
                continue;
            }

            const APath versionDirectory = packageInfo.PackagePath + version;
            const APath versionDescriptionFile = versionDirectory + "Description.json";
            if (version == "CurrentVersion")
            {
                if (APathInfo(versionDescriptionFile).isExists())
                {
                    AJSONObject description = AJSON::valueFromFile(versionDescriptionFile).toObject();
                    if (!description.read("Version", packageInfo.Version))
                    {
                        packageInfo.Version = "Invalid description";
                    }
                }
                else
                {
                    packageInfo.Version = "Description.json doesn't exist";
                }
            }
            else
            {
                packageInfo.Versions.push_back(version);
            }
        }

        //if (!packageInfo.version) packageInfo.version = "Current version is not set";

        Packages.push_back(std::move(packageInfo));
    }
}

void DeveloperLibrary::unload()
{
    pluginLibrary.unload();
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
