//        Author: Insane Team
//          File: OSBuildingSettingsDataObject.inl
// Creation date: 01/11/17 04:51:51
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSBuildingSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSBuildingSettingsDataObject::fetch()
{
    this->fetchProductName();
    this->fetchDestinationDirectory();
    this->fetchSourcePaths();
    this->fetchBuildingDirectory();
}

inline const String &OSBuildingSettingsDataObject::getProductName() const
{
    return this->data.productName;
}

inline void OSBuildingSettingsDataObject::setProductName(const String &productName)
{
    this->data.productName = productName;
    this->commitProductName();
}

inline void OSBuildingSettingsDataObject::setProductName(String &&productName)
{
    this->data.productName = std::move(productName);
    this->commitProductName();
}

inline void OSBuildingSettingsDataObject::fetchProductName()
{
    this->getContext()->fetchValue<Entity::ProductNameField>(this, this->data.productName);
}

inline void OSBuildingSettingsDataObject::commitProductName()
{
    this->getContext()->commitValue<Entity::ProductNameField>(this);
}
inline const String &OSBuildingSettingsDataObject::getDestinationDirectory() const
{
    return this->data.destinationDirectory;
}

inline void OSBuildingSettingsDataObject::setDestinationDirectory(const String &destinationDirectory)
{
    this->data.destinationDirectory = destinationDirectory;
    this->commitDestinationDirectory();
}

inline void OSBuildingSettingsDataObject::setDestinationDirectory(String &&destinationDirectory)
{
    this->data.destinationDirectory = std::move(destinationDirectory);
    this->commitDestinationDirectory();
}

inline void OSBuildingSettingsDataObject::fetchDestinationDirectory()
{
    this->getContext()->fetchValue<Entity::DestinationDirectoryField>(this, this->data.destinationDirectory);
}

inline void OSBuildingSettingsDataObject::commitDestinationDirectory()
{
    this->getContext()->commitValue<Entity::DestinationDirectoryField>(this);
}
inline const String &OSBuildingSettingsDataObject::getSourcePaths() const
{
    return this->data.sourcePaths;
}

inline void OSBuildingSettingsDataObject::setSourcePaths(const String &sourcePaths)
{
    this->data.sourcePaths = sourcePaths;
    this->commitSourcePaths();
}

inline void OSBuildingSettingsDataObject::setSourcePaths(String &&sourcePaths)
{
    this->data.sourcePaths = std::move(sourcePaths);
    this->commitSourcePaths();
}

inline void OSBuildingSettingsDataObject::fetchSourcePaths()
{
    this->getContext()->fetchValue<Entity::SourcePathsField>(this, this->data.sourcePaths);
}

inline void OSBuildingSettingsDataObject::commitSourcePaths()
{
    this->getContext()->commitValue<Entity::SourcePathsField>(this);
}
inline const String &OSBuildingSettingsDataObject::getBuildingDirectory() const
{
    return this->data.buildingDirectory;
}

inline void OSBuildingSettingsDataObject::setBuildingDirectory(const String &buildingDirectory)
{
    this->data.buildingDirectory = buildingDirectory;
    this->commitBuildingDirectory();
}

inline void OSBuildingSettingsDataObject::setBuildingDirectory(String &&buildingDirectory)
{
    this->data.buildingDirectory = std::move(buildingDirectory);
    this->commitBuildingDirectory();
}

inline void OSBuildingSettingsDataObject::fetchBuildingDirectory()
{
    this->getContext()->fetchValue<Entity::BuildingDirectoryField>(this, this->data.buildingDirectory);
}

inline void OSBuildingSettingsDataObject::commitBuildingDirectory()
{
    this->getContext()->commitValue<Entity::BuildingDirectoryField>(this);
}

