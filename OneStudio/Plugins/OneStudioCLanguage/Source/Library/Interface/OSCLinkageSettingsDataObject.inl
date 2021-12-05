#pragma once

inline const ADataEntity &OSCLinkageSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCLinkageSettingsDataObject::fetch()
{
    this->fetchLibraryPaths();
    this->fetchLibraries();
    this->fetchFrameworks();
}

inline const String &OSCLinkageSettingsDataObject::getLibraryPaths() const
{
    return this->data.libraryPaths;
}

inline void OSCLinkageSettingsDataObject::setLibraryPaths(const String &libraryPaths)
{
    this->data.libraryPaths = libraryPaths;
    this->commitLibraryPaths();
}

inline void OSCLinkageSettingsDataObject::setLibraryPaths(String &&libraryPaths)
{
    this->data.libraryPaths = std::move(libraryPaths);
    this->commitLibraryPaths();
}

inline void OSCLinkageSettingsDataObject::fetchLibraryPaths()
{
    this->getContext()->fetchValue<Entity::LibraryPathsField>(this, this->data.libraryPaths);
}

inline void OSCLinkageSettingsDataObject::commitLibraryPaths()
{
    this->getContext()->commitValue<Entity::LibraryPathsField>(this);
}

inline const String &OSCLinkageSettingsDataObject::getLibraries() const
{
    return this->data.libraries;
}

inline void OSCLinkageSettingsDataObject::setLibraries(const String &libraries)
{
    this->data.libraries = libraries;
    this->commitLibraries();
}

inline void OSCLinkageSettingsDataObject::setLibraries(String &&libraries)
{
    this->data.libraries = std::move(libraries);
    this->commitLibraries();
}

inline void OSCLinkageSettingsDataObject::fetchLibraries()
{
    this->getContext()->fetchValue<Entity::LibrariesField>(this, this->data.libraries);
}

inline void OSCLinkageSettingsDataObject::commitLibraries()
{
    this->getContext()->commitValue<Entity::LibrariesField>(this);
}

inline const String &OSCLinkageSettingsDataObject::getFrameworks() const
{
    return this->data.frameworks;
}

inline void OSCLinkageSettingsDataObject::setFrameworks(const String &frameworks)
{
    this->data.frameworks = frameworks;
    this->commitFrameworks();
}

inline void OSCLinkageSettingsDataObject::setFrameworks(String &&frameworks)
{
    this->data.frameworks = std::move(frameworks);
    this->commitFrameworks();
}

inline void OSCLinkageSettingsDataObject::fetchFrameworks()
{
    this->getContext()->fetchValue<Entity::FrameworksField>(this, this->data.frameworks);
}

inline void OSCLinkageSettingsDataObject::commitFrameworks()
{
    this->getContext()->commitValue<Entity::FrameworksField>(this);
}

