#pragma once

inline const ADataEntity &OSCCompilationSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCCompilationSettingsDataObject::fetch()
{
    this->fetchDefines();
    this->fetchIncludes();
    this->fetchIncludePaths();
}

inline const String &OSCCompilationSettingsDataObject::getDefines() const
{
    return this->data.defines;
}

inline void OSCCompilationSettingsDataObject::setDefines(const String &defines)
{
    this->data.defines = defines;
    this->commitDefines();
}

inline void OSCCompilationSettingsDataObject::setDefines(String &&defines)
{
    this->data.defines = std::move(defines);
    this->commitDefines();
}

inline void OSCCompilationSettingsDataObject::fetchDefines()
{
    this->getContext()->fetchValue<Entity::DefinesField>(this, this->data.defines);
}

inline void OSCCompilationSettingsDataObject::commitDefines()
{
    this->getContext()->commitValue<Entity::DefinesField>(this);
}

inline const String &OSCCompilationSettingsDataObject::getIncludes() const
{
    return this->data.includes;
}

inline void OSCCompilationSettingsDataObject::setIncludes(const String &includes)
{
    this->data.includes = includes;
    this->commitIncludes();
}

inline void OSCCompilationSettingsDataObject::setIncludes(String &&includes)
{
    this->data.includes = std::move(includes);
    this->commitIncludes();
}

inline void OSCCompilationSettingsDataObject::fetchIncludes()
{
    this->getContext()->fetchValue<Entity::IncludesField>(this, this->data.includes);
}

inline void OSCCompilationSettingsDataObject::commitIncludes()
{
    this->getContext()->commitValue<Entity::IncludesField>(this);
}

inline const String &OSCCompilationSettingsDataObject::getIncludePaths() const
{
    return this->data.includePaths;
}

inline void OSCCompilationSettingsDataObject::setIncludePaths(const String &includePaths)
{
    this->data.includePaths = includePaths;
    this->commitIncludePaths();
}

inline void OSCCompilationSettingsDataObject::setIncludePaths(String &&includePaths)
{
    this->data.includePaths = std::move(includePaths);
    this->commitIncludePaths();
}

inline void OSCCompilationSettingsDataObject::fetchIncludePaths()
{
    this->getContext()->fetchValue<Entity::IncludePathsField>(this, this->data.includePaths);
}

inline void OSCCompilationSettingsDataObject::commitIncludePaths()
{
    this->getContext()->commitValue<Entity::IncludePathsField>(this);
}

