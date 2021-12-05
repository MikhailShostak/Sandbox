/*        Author: Insane Team
 *          File: OSProjectFeatureInfoDataObject.cpp
 * Creation date: 01/11/17 04:27:01
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSProjectFeatureInfoDataObject.h"
#include "OSProjectFeatureInfoDataObject.inl"

String OSProjectFeatureInfoDataObjectEntity::PackageFieldName = "Package";
const String &OSProjectFeatureInfoDataObjectEntity::getPackageFieldName()
{
    return PackageFieldName;
}

String OSProjectFeatureInfoDataObjectEntity::PathFieldName = "Path";
const String &OSProjectFeatureInfoDataObjectEntity::getPathFieldName()
{
    return PathFieldName;
}

const OSProjectFeatureInfoDataObjectEntity &OSProjectFeatureInfoDataObject::getStaticEntity()
{
    static OSProjectFeatureInfoDataObjectEntity entity("OSProjectFeatureInfoDataObject", "OSProjectFeatureInfoDataObject");
    return entity;
}

