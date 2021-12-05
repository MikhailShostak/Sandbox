/*        Author: Insane Team
 *          File: OSProjectTargetInfoDataObject.cpp
 * Creation date: 01/11/17 04:27:45
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSProjectTargetInfoDataObject.h"
#include "OSProjectTargetInfoDataObject.inl"

String OSProjectTargetInfoDataObjectEntity::PackageFieldName = "Package";
const String &OSProjectTargetInfoDataObjectEntity::getPackageFieldName()
{
    return PackageFieldName;
}

String OSProjectTargetInfoDataObjectEntity::ProductDirectoryFieldName = "ProductDirectory";
const String &OSProjectTargetInfoDataObjectEntity::getProductDirectoryFieldName()
{
    return ProductDirectoryFieldName;
}

String OSProjectTargetInfoDataObjectEntity::NameFieldName = "Name";
const String &OSProjectTargetInfoDataObjectEntity::getNameFieldName()
{
    return NameFieldName;
}

String OSProjectTargetInfoDataObjectEntity::IntermediateDirectoryFieldName = "IntermediateDirectory";
const String &OSProjectTargetInfoDataObjectEntity::getIntermediateDirectoryFieldName()
{
    return IntermediateDirectoryFieldName;
}

String OSProjectTargetInfoDataObjectEntity::RunningCommandFieldName = "RunningCommand";
const String &OSProjectTargetInfoDataObjectEntity::getRunningCommandFieldName()
{
    return RunningCommandFieldName;
}

String OSProjectTargetInfoDataObjectEntity::RunningArgumentsFieldName = "RunningArguments";
const String &OSProjectTargetInfoDataObjectEntity::getRunningArgumentsFieldName()
{
    return RunningArgumentsFieldName;
}

const OSProjectTargetInfoDataObjectEntity &OSProjectTargetInfoDataObject::getStaticEntity()
{
    static OSProjectTargetInfoDataObjectEntity entity("OSProjectTargetInfoDataObject", "Targets");
    return entity;
}

