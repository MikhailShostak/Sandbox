#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GeneralSettingsData : public AObject
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
protected:
    typedef GeneralSettingsData This;
    typedef AObject Super;
    typedef void Interfaces;
protected:
    String ProductName;
String Package;
String Revision;
String VersionCode;
String VersionName;
String BuildingDirectory;
String DestinationDirectory;
Array<String> SourcePaths;
public:
    GeneralSettingsData();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getProductName() const;
    void setProductName(String const &ProductName);
    void setProductName(String &&ProductName);
    String getPackage() const;
    void setPackage(String const &Package);
    void setPackage(String &&Package);
    String getRevision() const;
    void setRevision(String const &Revision);
    void setRevision(String &&Revision);
    String getVersionCode() const;
    void setVersionCode(String const &VersionCode);
    void setVersionCode(String &&VersionCode);
    String getVersionName() const;
    void setVersionName(String const &VersionName);
    void setVersionName(String &&VersionName);
    String getBuildingDirectory() const;
    void setBuildingDirectory(String const &BuildingDirectory);
    void setBuildingDirectory(String &&BuildingDirectory);
    String getDestinationDirectory() const;
    void setDestinationDirectory(String const &DestinationDirectory);
    void setDestinationDirectory(String &&DestinationDirectory);
    Array<String> getSourcePaths() const;
    void setSourcePaths(Array<String> const &SourcePaths);
    void setSourcePaths(Array<String> &&SourcePaths);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
