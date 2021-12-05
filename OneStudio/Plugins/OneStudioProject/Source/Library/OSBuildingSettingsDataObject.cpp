/*        Author: Insane Team
 *          File: OSBuildingSettingsDataObject.cpp
 * Creation date: 01/11/17 04:27:01
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSBuildingSettingsDataObject.h"
#include "OSBuildingSettingsDataObject.inl"

String OSBuildingSettingsDataObjectEntity::ProductNameFieldName = "ProductName";
const String &OSBuildingSettingsDataObjectEntity::getProductNameFieldName()
{
    return ProductNameFieldName;
}

String OSBuildingSettingsDataObjectEntity::DestinationDirectoryFieldName = "DestinationDirectory";
const String &OSBuildingSettingsDataObjectEntity::getDestinationDirectoryFieldName()
{
    return DestinationDirectoryFieldName;
}

String OSBuildingSettingsDataObjectEntity::SourcePathsFieldName = "SourcePaths";
const String &OSBuildingSettingsDataObjectEntity::getSourcePathsFieldName()
{
    return SourcePathsFieldName;
}

String OSBuildingSettingsDataObjectEntity::BuildingDirectoryFieldName = "BuildingDirectory";
const String &OSBuildingSettingsDataObjectEntity::getBuildingDirectoryFieldName()
{
    return BuildingDirectoryFieldName;
}

const OSBuildingSettingsDataObjectEntity &OSBuildingSettingsDataObject::getStaticEntity()
{
    static OSBuildingSettingsDataObjectEntity entity("OSBuildingSettingsDataObject", "BuildingSettings");
    return entity;
}

