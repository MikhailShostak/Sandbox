//        Author: Insane Team
//          File: OSUnixCompilationSettingsDataObject.inl
// Creation date: 01/15/17 08:15:35
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSUnixCompilationSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSUnixCompilationSettingsDataObject::fetch()
{
    this->fetchIncludes();
    this->fetchFlags();
    this->fetchIncludePaths();
    this->fetchDefines();
    this->fetchCompiler();
}

inline const String &OSUnixCompilationSettingsDataObject::getIncludes() const
{
    return this->data.includes;
}

inline void OSUnixCompilationSettingsDataObject::setIncludes(const String &includes)
{
    this->data.includes = includes;
    this->commitIncludes();
}

inline void OSUnixCompilationSettingsDataObject::setIncludes(String &&includes)
{
    this->data.includes = std::move(includes);
    this->commitIncludes();
}

inline void OSUnixCompilationSettingsDataObject::fetchIncludes()
{
    this->getContext()->fetchValue<Entity::IncludesField>(this, this->data.includes);
}

inline void OSUnixCompilationSettingsDataObject::commitIncludes()
{
    this->getContext()->commitValue<Entity::IncludesField>(this);
}
inline const String &OSUnixCompilationSettingsDataObject::getFlags() const
{
    return this->data.flags;
}

inline void OSUnixCompilationSettingsDataObject::setFlags(const String &flags)
{
    this->data.flags = flags;
    this->commitFlags();
}

inline void OSUnixCompilationSettingsDataObject::setFlags(String &&flags)
{
    this->data.flags = std::move(flags);
    this->commitFlags();
}

inline void OSUnixCompilationSettingsDataObject::fetchFlags()
{
    this->getContext()->fetchValue<Entity::FlagsField>(this, this->data.flags);
}

inline void OSUnixCompilationSettingsDataObject::commitFlags()
{
    this->getContext()->commitValue<Entity::FlagsField>(this);
}
inline const String &OSUnixCompilationSettingsDataObject::getIncludePaths() const
{
    return this->data.includePaths;
}

inline void OSUnixCompilationSettingsDataObject::setIncludePaths(const String &includePaths)
{
    this->data.includePaths = includePaths;
    this->commitIncludePaths();
}

inline void OSUnixCompilationSettingsDataObject::setIncludePaths(String &&includePaths)
{
    this->data.includePaths = std::move(includePaths);
    this->commitIncludePaths();
}

inline void OSUnixCompilationSettingsDataObject::fetchIncludePaths()
{
    this->getContext()->fetchValue<Entity::IncludePathsField>(this, this->data.includePaths);
}

inline void OSUnixCompilationSettingsDataObject::commitIncludePaths()
{
    this->getContext()->commitValue<Entity::IncludePathsField>(this);
}
inline const String &OSUnixCompilationSettingsDataObject::getDefines() const
{
    return this->data.defines;
}

inline void OSUnixCompilationSettingsDataObject::setDefines(const String &defines)
{
    this->data.defines = defines;
    this->commitDefines();
}

inline void OSUnixCompilationSettingsDataObject::setDefines(String &&defines)
{
    this->data.defines = std::move(defines);
    this->commitDefines();
}

inline void OSUnixCompilationSettingsDataObject::fetchDefines()
{
    this->getContext()->fetchValue<Entity::DefinesField>(this, this->data.defines);
}

inline void OSUnixCompilationSettingsDataObject::commitDefines()
{
    this->getContext()->commitValue<Entity::DefinesField>(this);
}
inline const String &OSUnixCompilationSettingsDataObject::getCompiler() const
{
    return this->data.compiler;
}

inline void OSUnixCompilationSettingsDataObject::setCompiler(const String &compiler)
{
    this->data.compiler = compiler;
    this->commitCompiler();
}

inline void OSUnixCompilationSettingsDataObject::setCompiler(String &&compiler)
{
    this->data.compiler = std::move(compiler);
    this->commitCompiler();
}

inline void OSUnixCompilationSettingsDataObject::fetchCompiler()
{
    this->getContext()->fetchValue<Entity::CompilerField>(this, this->data.compiler);
}

inline void OSUnixCompilationSettingsDataObject::commitCompiler()
{
    this->getContext()->commitValue<Entity::CompilerField>(this);
}

