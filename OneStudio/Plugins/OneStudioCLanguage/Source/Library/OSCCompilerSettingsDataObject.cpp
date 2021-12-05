/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCCompilerSettingsDataObject.h"
#include "OSCCompilerSettingsDataObject.inl"

String OSCCompilerSettingsDataObjectEntity::CompilerFieldName = "Compiler";
const String &OSCCompilerSettingsDataObjectEntity::getCompilerFieldName()
{
    return CompilerFieldName;
}

String OSCCompilerSettingsDataObjectEntity::IncludeFlagFieldName = "IncludeFlag";
const String &OSCCompilerSettingsDataObjectEntity::getIncludeFlagFieldName()
{
    return IncludeFlagFieldName;
}

String OSCCompilerSettingsDataObjectEntity::IncludePathFlagFieldName = "IncludePathFlag";
const String &OSCCompilerSettingsDataObjectEntity::getIncludePathFlagFieldName()
{
    return IncludePathFlagFieldName;
}

String OSCCompilerSettingsDataObjectEntity::DefineFlagFieldName = "DefineFlag";
const String &OSCCompilerSettingsDataObjectEntity::getDefineFlagFieldName()
{
    return DefineFlagFieldName;
}

String OSCCompilerSettingsDataObjectEntity::OutputFileFlagFieldName = "OutputFileFlag";
const String &OSCCompilerSettingsDataObjectEntity::getOutputFileFlagFieldName()
{
    return OutputFileFlagFieldName;
}

String OSCCompilerSettingsDataObjectEntity::CompilationFlagFieldName = "CompilationFlag";
const String &OSCCompilerSettingsDataObjectEntity::getCompilationFlagFieldName()
{
    return CompilationFlagFieldName;
}

String OSCCompilerSettingsDataObjectEntity::FlagsFieldName = "Flags";
const String &OSCCompilerSettingsDataObjectEntity::getFlagsFieldName()
{
    return FlagsFieldName;
}

const OSCCompilerSettingsDataObjectEntity &OSCCompilerSettingsDataObject::getStaticEntity()
{
    static OSCCompilerSettingsDataObjectEntity entity("OSCCompilerSettingsDataObject", "OSCCompilerSettingsDataObject");
    return entity;
}

AVariant OSCCompilerSettingsDataObject::getDataProperty(const String &name) const
{
    switch(Entity::getStaticProperties().indexOf(name))
    {
        case 0: return getCompiler();
        case 1: return getIncludeFlag();
        case 2: return getIncludePathFlag();
        case 3: return getDefineFlag();
        case 4: return getOutputFileFlag();
        case 5: return getCompilationFlag();
        case 6: return getFlags();
    }

    return Super::getDataProperty(name);
}

const Array<String> &OSCCompilerSettingsDataObjectEntity::getStaticProperties()
{
    static Array<String> properties = {        CompilerFieldName,        IncludeFlagFieldName,        IncludePathFlagFieldName,        DefineFlagFieldName,        OutputFileFlagFieldName,        CompilationFlagFieldName,        FlagsFieldName,
    };
    return properties;
}

const Array<String> &OSCCompilerSettingsDataObjectEntity::getProperties() const
{
    return getProperties();
}


