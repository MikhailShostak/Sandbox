/*        Author: Insane Team
 *          File: OSTaskPropertyDataObject.cpp
 * Creation date: 01/11/17 04:27:01
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSTaskPropertyDataObject.h"
#include "OSTaskPropertyDataObject.inl"

String OSTaskPropertyDataObjectEntity::NameFieldName = "Name";
const String &OSTaskPropertyDataObjectEntity::getNameFieldName()
{
    return NameFieldName;
}

String OSTaskPropertyDataObjectEntity::ValueFieldName = "Value";
const String &OSTaskPropertyDataObjectEntity::getValueFieldName()
{
    return ValueFieldName;
}

String OSTaskPropertyDataObjectEntity::TaskFieldName = "Task";
const String &OSTaskPropertyDataObjectEntity::getTaskFieldName()
{
    return TaskFieldName;
}

const OSTaskPropertyDataObjectEntity &OSTaskPropertyDataObject::getStaticEntity()
{
    static OSTaskPropertyDataObjectEntity entity("OSTaskPropertyDataObject", "OSTaskPropertyDataObject");
    return entity;
}

