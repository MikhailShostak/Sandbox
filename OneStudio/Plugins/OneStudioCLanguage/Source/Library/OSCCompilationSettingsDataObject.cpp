/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCCompilationSettingsDataObject.h"
#include "OSCCompilationSettingsDataObject.inl"

String OSCCompilationSettingsDataObjectEntity::DefinesFieldName = "Defines";
const String &OSCCompilationSettingsDataObjectEntity::getDefinesFieldName()
{
    return DefinesFieldName;
}

String OSCCompilationSettingsDataObjectEntity::IncludesFieldName = "Includes";
const String &OSCCompilationSettingsDataObjectEntity::getIncludesFieldName()
{
    return IncludesFieldName;
}

String OSCCompilationSettingsDataObjectEntity::IncludePathsFieldName = "IncludePaths";
const String &OSCCompilationSettingsDataObjectEntity::getIncludePathsFieldName()
{
    return IncludePathsFieldName;
}

const OSCCompilationSettingsDataObjectEntity &OSCCompilationSettingsDataObject::getStaticEntity()
{
    static OSCCompilationSettingsDataObjectEntity entity("OSCCompilationSettingsDataObject", "OSCCompilationSettingsDataObject");
    return entity;
}

AVariant OSCCompilationSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getDefines();
        case 1: return getIncludes();
        case 2: return getIncludePaths();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCCompilationSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        DefinesFieldName,        IncludesFieldName,        IncludePathsFieldName,
    };
    return properties;
}

const Array<String> &OSCCompilationSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


