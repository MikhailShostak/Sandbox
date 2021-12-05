/*        Author: Insane Team
 *          File: OSProjectEntryDataObject.cpp
 * Creation date: 01/11/17 04:27:01
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSProjectEntryDataObject.h"
#include "OSProjectEntryDataObject.inl"

String OSProjectEntryDataObjectEntity::PackageFieldName = "Package";
const String &OSProjectEntryDataObjectEntity::getPackageFieldName()
{
    return PackageFieldName;
}

String OSProjectEntryDataObjectEntity::PathFieldName = "Path";
const String &OSProjectEntryDataObjectEntity::getPathFieldName()
{
    return PathFieldName;
}

const OSProjectEntryDataObjectEntity &OSProjectEntryDataObject::getStaticEntity()
{
    static OSProjectEntryDataObjectEntity entity("OSProjectEntryDataObject", "Entries");
    return entity;
}

