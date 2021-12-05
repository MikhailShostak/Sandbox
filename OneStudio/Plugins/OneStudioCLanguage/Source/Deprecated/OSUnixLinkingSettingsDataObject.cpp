/*        Author: Insane Team
 *          File: OSUnixLinkingSettingsDataObject.cpp
 * Creation date: 01/15/17 08:15:35
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSUnixLinkingSettingsDataObject.h"
#include "OSUnixLinkingSettingsDataObject.inl"

String OSUnixLinkingSettingsDataObjectEntity::FlagsFieldName = "Flags";
const String &OSUnixLinkingSettingsDataObjectEntity::getFlagsFieldName()
{
    return FlagsFieldName;
}

String OSUnixLinkingSettingsDataObjectEntity::LibraryPathsFieldName = "LibraryPaths";
const String &OSUnixLinkingSettingsDataObjectEntity::getLibraryPathsFieldName()
{
    return LibraryPathsFieldName;
}

String OSUnixLinkingSettingsDataObjectEntity::LibrariesFieldName = "Libraries";
const String &OSUnixLinkingSettingsDataObjectEntity::getLibrariesFieldName()
{
    return LibrariesFieldName;
}

String OSUnixLinkingSettingsDataObjectEntity::LinkerFieldName = "Linker";
const String &OSUnixLinkingSettingsDataObjectEntity::getLinkerFieldName()
{
    return LinkerFieldName;
}

String OSUnixLinkingSettingsDataObjectEntity::FrameworksFieldName = "Frameworks";
const String &OSUnixLinkingSettingsDataObjectEntity::getFrameworksFieldName()
{
    return FrameworksFieldName;
}

const OSUnixLinkingSettingsDataObjectEntity &OSUnixLinkingSettingsDataObject::getStaticEntity()
{
    static OSUnixLinkingSettingsDataObjectEntity entity("OSUnixLinkingSettingsDataObject", "UnixLinkingSettings");
    return entity;
}

AVariant OSUnixLinkingSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0:
            return getFlags();
        case 1:
            return getLibraryPaths();
        case 2:
            return getLibraries();
        case 3:
            return getLinker();
        case 4:
            return getFrameworks();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSUnixLinkingSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {
        FlagsFieldName,
        LibraryPathsFieldName,
        LibrariesFieldName,
        LinkerFieldName,
        FrameworksFieldName,
    };
    return properties;
}

const Array<String> &OSUnixLinkingSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


