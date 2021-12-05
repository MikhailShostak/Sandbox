//        Author: Insane Team
//          File: OSUnixLinkingSettingsDataObject.inl
// Creation date: 01/15/17 08:15:35
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

inline const ADataEntity &OSUnixLinkingSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSUnixLinkingSettingsDataObject::fetch()
{
    this->fetchFlags();
    this->fetchLibraryPaths();
    this->fetchLibraries();
    this->fetchLinker();
    this->fetchFrameworks();
}

inline const String &OSUnixLinkingSettingsDataObject::getFlags() const
{
    return this->data.flags;
}

inline void OSUnixLinkingSettingsDataObject::setFlags(const String &flags)
{
    this->data.flags = flags;
    this->commitFlags();
}

inline void OSUnixLinkingSettingsDataObject::setFlags(String &&flags)
{
    this->data.flags = std::move(flags);
    this->commitFlags();
}

inline void OSUnixLinkingSettingsDataObject::fetchFlags()
{
    this->getContext()->fetchValue<Entity::FlagsField>(this, this->data.flags);
}

inline void OSUnixLinkingSettingsDataObject::commitFlags()
{
    this->getContext()->commitValue<Entity::FlagsField>(this);
}
inline const String &OSUnixLinkingSettingsDataObject::getLibraryPaths() const
{
    return this->data.libraryPaths;
}

inline void OSUnixLinkingSettingsDataObject::setLibraryPaths(const String &libraryPaths)
{
    this->data.libraryPaths = libraryPaths;
    this->commitLibraryPaths();
}

inline void OSUnixLinkingSettingsDataObject::setLibraryPaths(String &&libraryPaths)
{
    this->data.libraryPaths = std::move(libraryPaths);
    this->commitLibraryPaths();
}

inline void OSUnixLinkingSettingsDataObject::fetchLibraryPaths()
{
    this->getContext()->fetchValue<Entity::LibraryPathsField>(this, this->data.libraryPaths);
}

inline void OSUnixLinkingSettingsDataObject::commitLibraryPaths()
{
    this->getContext()->commitValue<Entity::LibraryPathsField>(this);
}
inline const String &OSUnixLinkingSettingsDataObject::getLibraries() const
{
    return this->data.libraries;
}

inline void OSUnixLinkingSettingsDataObject::setLibraries(const String &libraries)
{
    this->data.libraries = libraries;
    this->commitLibraries();
}

inline void OSUnixLinkingSettingsDataObject::setLibraries(String &&libraries)
{
    this->data.libraries = std::move(libraries);
    this->commitLibraries();
}

inline void OSUnixLinkingSettingsDataObject::fetchLibraries()
{
    this->getContext()->fetchValue<Entity::LibrariesField>(this, this->data.libraries);
}

inline void OSUnixLinkingSettingsDataObject::commitLibraries()
{
    this->getContext()->commitValue<Entity::LibrariesField>(this);
}
inline const String &OSUnixLinkingSettingsDataObject::getLinker() const
{
    return this->data.linker;
}

inline void OSUnixLinkingSettingsDataObject::setLinker(const String &linker)
{
    this->data.linker = linker;
    this->commitLinker();
}

inline void OSUnixLinkingSettingsDataObject::setLinker(String &&linker)
{
    this->data.linker = std::move(linker);
    this->commitLinker();
}

inline void OSUnixLinkingSettingsDataObject::fetchLinker()
{
    this->getContext()->fetchValue<Entity::LinkerField>(this, this->data.linker);
}

inline void OSUnixLinkingSettingsDataObject::commitLinker()
{
    this->getContext()->commitValue<Entity::LinkerField>(this);
}
inline const String &OSUnixLinkingSettingsDataObject::getFrameworks() const
{
    return this->data.frameworks;
}

inline void OSUnixLinkingSettingsDataObject::setFrameworks(const String &frameworks)
{
    this->data.frameworks = frameworks;
    this->commitFrameworks();
}

inline void OSUnixLinkingSettingsDataObject::setFrameworks(String &&frameworks)
{
    this->data.frameworks = std::move(frameworks);
    this->commitFrameworks();
}

inline void OSUnixLinkingSettingsDataObject::fetchFrameworks()
{
    this->getContext()->fetchValue<Entity::FrameworksField>(this, this->data.frameworks);
}

inline void OSUnixLinkingSettingsDataObject::commitFrameworks()
{
    this->getContext()->commitValue<Entity::FrameworksField>(this);
}


