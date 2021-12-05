//        Author: Insane Team
//          File: OSBuildingSettingsDataObject.h
// Creation date: 01/11/17 04:50:15
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <Data>
#include <Foundation>

//       Class: OSBuildingSettingsDataObject
//        Base: ADataObject
//        Link: 
// Description: 

class OSBuildingSettingsDataObject : public ADataObject
{
public:
    typedef OSBuildingSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSBuildingSettingsDataObjectEntity Entity;

    struct Data
    {
        String productName;
        String destinationDirectory;
        String sourcePaths;
        String buildingDirectory;
    };

private:
    Data data;

public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    void fetch() override;

public:
    const String &getProductName() const;
    void setProductName(const String &productName);
    void setProductName(String &&productName);
    void fetchProductName();
private:
    void commitProductName();

public:
    const String &getDestinationDirectory() const;
    void setDestinationDirectory(const String &destinationDirectory);
    void setDestinationDirectory(String &&destinationDirectory);
    void fetchDestinationDirectory();
private:
    void commitDestinationDirectory();

public:
    const String &getSourcePaths() const;
    void setSourcePaths(const String &sourcePaths);
    void setSourcePaths(String &&sourcePaths);
    void fetchSourcePaths();
private:
    void commitSourcePaths();

public:
    const String &getBuildingDirectory() const;
    void setBuildingDirectory(const String &buildingDirectory);
    void setBuildingDirectory(String &&buildingDirectory);
    void fetchBuildingDirectory();
private:
    void commitBuildingDirectory();
};

class OSBuildingSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;

    static String ProductNameFieldName;
    static String DestinationDirectoryFieldName;
    static String SourcePathsFieldName;
    static String BuildingDirectoryFieldName;

public:
    typedef OSBuildingSettingsDataObject DataType;

    static const String &getProductNameFieldName();
    typedef StringDataField<DataType, ProductNameFieldName, &OSBuildingSettingsDataObject::getProductName, &OSBuildingSettingsDataObject::setProductName> ProductNameField;

    static const String &getDestinationDirectoryFieldName();
    typedef StringDataField<DataType, DestinationDirectoryFieldName, &OSBuildingSettingsDataObject::getDestinationDirectory, &OSBuildingSettingsDataObject::setDestinationDirectory> DestinationDirectoryField;

    static const String &getSourcePathsFieldName();
    typedef StringDataField<DataType, SourcePathsFieldName, &OSBuildingSettingsDataObject::getSourcePaths, &OSBuildingSettingsDataObject::setSourcePaths> SourcePathsField;

    static const String &getBuildingDirectoryFieldName();
    typedef StringDataField<DataType, BuildingDirectoryFieldName, &OSBuildingSettingsDataObject::getBuildingDirectory, &OSBuildingSettingsDataObject::setBuildingDirectory> BuildingDirectoryField;
};

