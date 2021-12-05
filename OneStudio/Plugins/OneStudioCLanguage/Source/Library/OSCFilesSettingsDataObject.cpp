/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCFilesSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.inl"

String OSCFilesSettingsDataObjectEntity::ObjectFileNameFieldName = "ObjectFileName";
const String &OSCFilesSettingsDataObjectEntity::getObjectFileNameFieldName()
{
    return ObjectFileNameFieldName;
}

String OSCFilesSettingsDataObjectEntity::StaticLibraryFileNameFieldName = "StaticLibraryFileName";
const String &OSCFilesSettingsDataObjectEntity::getStaticLibraryFileNameFieldName()
{
    return StaticLibraryFileNameFieldName;
}

String OSCFilesSettingsDataObjectEntity::DynamicLibraryFileNameFieldName = "DynamicLibraryFileName";
const String &OSCFilesSettingsDataObjectEntity::getDynamicLibraryFileNameFieldName()
{
    return DynamicLibraryFileNameFieldName;
}

String OSCFilesSettingsDataObjectEntity::ApplicationFileNameFieldName = "ApplicationFileName";
const String &OSCFilesSettingsDataObjectEntity::getApplicationFileNameFieldName()
{
    return ApplicationFileNameFieldName;
}

String OSCFilesSettingsDataObjectEntity::DebugSymbolsFileNameFieldName = "DebugSymbolsFileName";
const String &OSCFilesSettingsDataObjectEntity::getDebugSymbolsFileNameFieldName()
{
    return DebugSymbolsFileNameFieldName;
}

const OSCFilesSettingsDataObjectEntity &OSCFilesSettingsDataObject::getStaticEntity()
{
    static OSCFilesSettingsDataObjectEntity entity("OSCFilesSettingsDataObject", "OSCFilesSettingsDataObject");
    return entity;
}

AVariant OSCFilesSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getObjectFileName();
        case 1: return getStaticLibraryFileName();
        case 2: return getDynamicLibraryFileName();
        case 3: return getApplicationFileName();
        case 4: return getDebugSymbolsFileName();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCFilesSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        ObjectFileNameFieldName,        StaticLibraryFileNameFieldName,        DynamicLibraryFileNameFieldName,        ApplicationFileNameFieldName,        DebugSymbolsFileNameFieldName,
    };
    return properties;
}

const Array<String> &OSCFilesSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


