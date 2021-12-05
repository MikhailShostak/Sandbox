/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCLinkerSettingsDataObject.h"
#include "OSCLinkerSettingsDataObject.inl"

String OSCLinkerSettingsDataObjectEntity::LinkerFieldName = "Linker";
const String &OSCLinkerSettingsDataObjectEntity::getLinkerFieldName()
{
    return LinkerFieldName;
}

String OSCLinkerSettingsDataObjectEntity::LibraryFlagFieldName = "LibraryFlag";
const String &OSCLinkerSettingsDataObjectEntity::getLibraryFlagFieldName()
{
    return LibraryFlagFieldName;
}

String OSCLinkerSettingsDataObjectEntity::LibraryPathFlagFieldName = "LibraryPathFlag";
const String &OSCLinkerSettingsDataObjectEntity::getLibraryPathFlagFieldName()
{
    return LibraryPathFlagFieldName;
}

String OSCLinkerSettingsDataObjectEntity::OutputFileFlagFieldName = "OutputFileFlag";
const String &OSCLinkerSettingsDataObjectEntity::getOutputFileFlagFieldName()
{
    return OutputFileFlagFieldName;
}

String OSCLinkerSettingsDataObjectEntity::FlagsFieldName = "Flags";
const String &OSCLinkerSettingsDataObjectEntity::getFlagsFieldName()
{
    return FlagsFieldName;
}

String OSCLinkerSettingsDataObjectEntity::ApplicationFlagsFieldName = "ApplicationFlags";
const String &OSCLinkerSettingsDataObjectEntity::getApplicationFlagsFieldName()
{
    return ApplicationFlagsFieldName;
}

String OSCLinkerSettingsDataObjectEntity::LibraryFlagsFieldName = "LibraryFlags";
const String &OSCLinkerSettingsDataObjectEntity::getLibraryFlagsFieldName()
{
    return LibraryFlagsFieldName;
}

const OSCLinkerSettingsDataObjectEntity &OSCLinkerSettingsDataObject::getStaticEntity()
{
    static OSCLinkerSettingsDataObjectEntity entity("OSCLinkerSettingsDataObject", "OSCLinkerSettingsDataObject");
    return entity;
}

AVariant OSCLinkerSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getLinker();
        case 1: return getLibraryFlag();
        case 2: return getLibraryPathFlag();
        case 3: return getOutputFileFlag();
        case 4: return getFlags();
        case 5: return getApplicationFlags();
        case 6: return getLibraryFlags();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCLinkerSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        LinkerFieldName,        LibraryFlagFieldName,        LibraryPathFlagFieldName,        OutputFileFlagFieldName,        FlagsFieldName,        ApplicationFlagsFieldName,        LibraryFlagsFieldName,
    };
    return properties;
}

const Array<String> &OSCLinkerSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


