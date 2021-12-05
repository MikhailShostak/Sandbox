/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCArchiverSettingsDataObject.h"
#include "OSCArchiverSettingsDataObject.inl"

String OSCArchiverSettingsDataObjectEntity::ArchiverFieldName = "Archiver";
const String &OSCArchiverSettingsDataObjectEntity::getArchiverFieldName()
{
    return ArchiverFieldName;
}

String OSCArchiverSettingsDataObjectEntity::OutputFileFlagFieldName = "OutputFileFlag";
const String &OSCArchiverSettingsDataObjectEntity::getOutputFileFlagFieldName()
{
    return OutputFileFlagFieldName;
}

String OSCArchiverSettingsDataObjectEntity::FlagsFieldName = "Flags";
const String &OSCArchiverSettingsDataObjectEntity::getFlagsFieldName()
{
    return FlagsFieldName;
}

const OSCArchiverSettingsDataObjectEntity &OSCArchiverSettingsDataObject::getStaticEntity()
{
    static OSCArchiverSettingsDataObjectEntity entity("OSCArchiverSettingsDataObject", "OSCArchiverSettingsDataObject");
    return entity;
}

AVariant OSCArchiverSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getArchiver();
        case 1: return getOutputFileFlag();
        case 2: return getFlags();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCArchiverSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        ArchiverFieldName,        OutputFileFlagFieldName,        FlagsFieldName,
    };
    return properties;
}

const Array<String> &OSCArchiverSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


