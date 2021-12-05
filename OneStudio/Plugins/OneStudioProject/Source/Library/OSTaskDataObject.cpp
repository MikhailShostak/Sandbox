/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSTaskDataObject.h"
#include "OSTaskDataObject.inl"

String OSTaskDataObjectEntity::PackageFieldName = "Package";
const String &OSTaskDataObjectEntity::getPackageFieldName()
{
    return PackageFieldName;
}

String OSTaskDataObjectEntity::IndexFieldName = "Index";
const String &OSTaskDataObjectEntity::getIndexFieldName()
{
    return IndexFieldName;
}

String OSTaskDataObjectEntity::StepTypeFieldName = "StepType";
const String &OSTaskDataObjectEntity::getStepTypeFieldName()
{
    return StepTypeFieldName;
}

String OSTaskDataObjectEntity::DescriptionFieldName = "Description";
const String &OSTaskDataObjectEntity::getDescriptionFieldName()
{
    return DescriptionFieldName;
}

const OSTaskDataObjectEntity &OSTaskDataObject::getStaticEntity()
{
    static OSTaskDataObjectEntity entity("OSTaskDataObject", "OSTaskDataObject");
    return entity;
}

AVariant OSTaskDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getPackage();
        case 1: return getIndex();
        case 2: return getStepType();
        case 3: return getDescription();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSTaskDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        PackageFieldName,        IndexFieldName,        StepTypeFieldName,        DescriptionFieldName,
    };
    return properties;
}

const Array<String> &OSTaskDataObjectEntity::getProperties() const
{
    return getProperties();
}


