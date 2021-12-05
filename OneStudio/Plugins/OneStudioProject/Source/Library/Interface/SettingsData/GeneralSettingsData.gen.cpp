//CLASSGEN GENERATED REGION: Includes
#include "GeneralSettingsData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GeneralSettingsData::GeneralSettingsData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GeneralSettingsData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("ProductName", toJSONValue(ProductName));
    object.insert("Package", toJSONValue(Package));
    object.insert("Revision", toJSONValue(Revision));
    object.insert("VersionCode", toJSONValue(VersionCode));
    object.insert("VersionName", toJSONValue(VersionName));
    object.insert("BuildingDirectory", toJSONValue(BuildingDirectory));
    object.insert("DestinationDirectory", toJSONValue(DestinationDirectory));
    object.insert("SourcePaths", toJSONValue(SourcePaths));
}
void GeneralSettingsData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("ProductName", value);
    fromJSONValue(value, ProductName);
    value = AJSONValue();
    object.read("Package", value);
    fromJSONValue(value, Package);
    value = AJSONValue();
    object.read("Revision", value);
    fromJSONValue(value, Revision);
    value = AJSONValue();
    object.read("VersionCode", value);
    fromJSONValue(value, VersionCode);
    value = AJSONValue();
    object.read("VersionName", value);
    fromJSONValue(value, VersionName);
    value = AJSONValue();
    object.read("BuildingDirectory", value);
    fromJSONValue(value, BuildingDirectory);
    value = AJSONValue();
    object.read("DestinationDirectory", value);
    fromJSONValue(value, DestinationDirectory);
    value = AJSONValue();
    object.read("SourcePaths", value);
    fromJSONValue(value, SourcePaths);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String GeneralSettingsData::getProductName() const
{
    return this->ProductName;
}
void GeneralSettingsData::setProductName(String const &ProductName)
{
    this->ProductName = ProductName;
}
void GeneralSettingsData::setProductName(String &&ProductName)
{
    this->ProductName = std::move(ProductName);
}
String GeneralSettingsData::getPackage() const
{
    return this->Package;
}
void GeneralSettingsData::setPackage(String const &Package)
{
    this->Package = Package;
}
void GeneralSettingsData::setPackage(String &&Package)
{
    this->Package = std::move(Package);
}
String GeneralSettingsData::getRevision() const
{
    return this->Revision;
}
void GeneralSettingsData::setRevision(String const &Revision)
{
    this->Revision = Revision;
}
void GeneralSettingsData::setRevision(String &&Revision)
{
    this->Revision = std::move(Revision);
}
String GeneralSettingsData::getVersionCode() const
{
    return this->VersionCode;
}
void GeneralSettingsData::setVersionCode(String const &VersionCode)
{
    this->VersionCode = VersionCode;
}
void GeneralSettingsData::setVersionCode(String &&VersionCode)
{
    this->VersionCode = std::move(VersionCode);
}
String GeneralSettingsData::getVersionName() const
{
    return this->VersionName;
}
void GeneralSettingsData::setVersionName(String const &VersionName)
{
    this->VersionName = VersionName;
}
void GeneralSettingsData::setVersionName(String &&VersionName)
{
    this->VersionName = std::move(VersionName);
}
String GeneralSettingsData::getBuildingDirectory() const
{
    return this->BuildingDirectory;
}
void GeneralSettingsData::setBuildingDirectory(String const &BuildingDirectory)
{
    this->BuildingDirectory = BuildingDirectory;
}
void GeneralSettingsData::setBuildingDirectory(String &&BuildingDirectory)
{
    this->BuildingDirectory = std::move(BuildingDirectory);
}
String GeneralSettingsData::getDestinationDirectory() const
{
    return this->DestinationDirectory;
}
void GeneralSettingsData::setDestinationDirectory(String const &DestinationDirectory)
{
    this->DestinationDirectory = DestinationDirectory;
}
void GeneralSettingsData::setDestinationDirectory(String &&DestinationDirectory)
{
    this->DestinationDirectory = std::move(DestinationDirectory);
}
Array<String> GeneralSettingsData::getSourcePaths() const
{
    return this->SourcePaths;
}
void GeneralSettingsData::setSourcePaths(Array<String> const &SourcePaths)
{
    this->SourcePaths = SourcePaths;
}
void GeneralSettingsData::setSourcePaths(Array<String> &&SourcePaths)
{
    this->SourcePaths = std::move(SourcePaths);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
