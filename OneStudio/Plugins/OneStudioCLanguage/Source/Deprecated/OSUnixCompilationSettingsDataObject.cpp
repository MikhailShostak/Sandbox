/*        Author: Insane Team
 *          File: OSUnixCompilationSettingsDataObject.cpp
 * Creation date: 01/15/17 08:15:35
 *     Copyright: Insane Team, 2016. All rights reseved.
 */

#include "OSUnixCompilationSettingsDataObject.h"
#include "OSUnixCompilationSettingsDataObject.inl"

String OSUnixCompilationSettingsDataObjectEntity::IncludesFieldName = "Includes";
const String &OSUnixCompilationSettingsDataObjectEntity::getIncludesFieldName()
{
    return IncludesFieldName;
}

String OSUnixCompilationSettingsDataObjectEntity::FlagsFieldName = "Flags";
const String &OSUnixCompilationSettingsDataObjectEntity::getFlagsFieldName()
{
    return FlagsFieldName;
}

String OSUnixCompilationSettingsDataObjectEntity::IncludePathsFieldName = "IncludePaths";
const String &OSUnixCompilationSettingsDataObjectEntity::getIncludePathsFieldName()
{
    return IncludePathsFieldName;
}

String OSUnixCompilationSettingsDataObjectEntity::DefinesFieldName = "Defines";
const String &OSUnixCompilationSettingsDataObjectEntity::getDefinesFieldName()
{
    return DefinesFieldName;
}

String OSUnixCompilationSettingsDataObjectEntity::CompilerFieldName = "Compiler";
const String &OSUnixCompilationSettingsDataObjectEntity::getCompilerFieldName()
{
    return CompilerFieldName;
}

const OSUnixCompilationSettingsDataObjectEntity &OSUnixCompilationSettingsDataObject::getStaticEntity()
{
    static OSUnixCompilationSettingsDataObjectEntity entity("OSUnixCompilationSettingsDataObject", "UnixCompilationSettings");
    return entity;
}

AVariant OSUnixCompilationSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0:
            return getIncludes();
        case 1:
            return getFlags();
        case 2:
            return getIncludePaths();
        case 3:
            return getDefines();
        case 4:
            return getCompiler();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSUnixCompilationSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {
        IncludesFieldName,
        FlagsFieldName,
        IncludePathsFieldName,
        DefinesFieldName,
        CompilerFieldName,
    };
    return properties;
}

const Array<String> &OSUnixCompilationSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


