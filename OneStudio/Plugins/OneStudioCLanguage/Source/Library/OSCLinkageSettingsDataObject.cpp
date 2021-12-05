/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCLinkageSettingsDataObject.h"
#include "OSCLinkageSettingsDataObject.inl"

String OSCLinkageSettingsDataObjectEntity::LibraryPathsFieldName = "LibraryPaths";
const String &OSCLinkageSettingsDataObjectEntity::getLibraryPathsFieldName()
{
    return LibraryPathsFieldName;
}

String OSCLinkageSettingsDataObjectEntity::LibrariesFieldName = "Libraries";
const String &OSCLinkageSettingsDataObjectEntity::getLibrariesFieldName()
{
    return LibrariesFieldName;
}

String OSCLinkageSettingsDataObjectEntity::FrameworksFieldName = "Frameworks";
const String &OSCLinkageSettingsDataObjectEntity::getFrameworksFieldName()
{
    return FrameworksFieldName;
}

const OSCLinkageSettingsDataObjectEntity &OSCLinkageSettingsDataObject::getStaticEntity()
{
    static OSCLinkageSettingsDataObjectEntity entity("OSCLinkageSettingsDataObject", "OSCLinkageSettingsDataObject");
    return entity;
}

AVariant OSCLinkageSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getLibraryPaths();
        case 1: return getLibraries();
        case 2: return getFrameworks();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCLinkageSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        LibraryPathsFieldName,        LibrariesFieldName,        FrameworksFieldName,
    };
    return properties;
}

const Array<String> &OSCLinkageSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


