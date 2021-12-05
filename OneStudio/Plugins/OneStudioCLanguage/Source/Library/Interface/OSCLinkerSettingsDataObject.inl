#pragma once

inline const ADataEntity &OSCLinkerSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCLinkerSettingsDataObject::fetch()
{
    this->fetchLinker();
    this->fetchLibraryFlag();
    this->fetchLibraryPathFlag();
    this->fetchOutputFileFlag();
    this->fetchFlags();
    this->fetchApplicationFlags();
    this->fetchLibraryFlags();
}

inline const String &OSCLinkerSettingsDataObject::getLinker() const
{
    return this->data.linker;
}

inline void OSCLinkerSettingsDataObject::setLinker(const String &linker)
{
    this->data.linker = linker;
    this->commitLinker();
}

inline void OSCLinkerSettingsDataObject::setLinker(String &&linker)
{
    this->data.linker = std::move(linker);
    this->commitLinker();
}

inline void OSCLinkerSettingsDataObject::fetchLinker()
{
    this->getContext()->fetchValue<Entity::LinkerField>(this, this->data.linker);
}

inline void OSCLinkerSettingsDataObject::commitLinker()
{
    this->getContext()->commitValue<Entity::LinkerField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getLibraryFlag() const
{
    return this->data.libraryFlag;
}

inline void OSCLinkerSettingsDataObject::setLibraryFlag(const String &libraryFlag)
{
    this->data.libraryFlag = libraryFlag;
    this->commitLibraryFlag();
}

inline void OSCLinkerSettingsDataObject::setLibraryFlag(String &&libraryFlag)
{
    this->data.libraryFlag = std::move(libraryFlag);
    this->commitLibraryFlag();
}

inline void OSCLinkerSettingsDataObject::fetchLibraryFlag()
{
    this->getContext()->fetchValue<Entity::LibraryFlagField>(this, this->data.libraryFlag);
}

inline void OSCLinkerSettingsDataObject::commitLibraryFlag()
{
    this->getContext()->commitValue<Entity::LibraryFlagField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getLibraryPathFlag() const
{
    return this->data.libraryPathFlag;
}

inline void OSCLinkerSettingsDataObject::setLibraryPathFlag(const String &libraryPathFlag)
{
    this->data.libraryPathFlag = libraryPathFlag;
    this->commitLibraryPathFlag();
}

inline void OSCLinkerSettingsDataObject::setLibraryPathFlag(String &&libraryPathFlag)
{
    this->data.libraryPathFlag = std::move(libraryPathFlag);
    this->commitLibraryPathFlag();
}

inline void OSCLinkerSettingsDataObject::fetchLibraryPathFlag()
{
    this->getContext()->fetchValue<Entity::LibraryPathFlagField>(this, this->data.libraryPathFlag);
}

inline void OSCLinkerSettingsDataObject::commitLibraryPathFlag()
{
    this->getContext()->commitValue<Entity::LibraryPathFlagField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getOutputFileFlag() const
{
    return this->data.outputFileFlag;
}

inline void OSCLinkerSettingsDataObject::setOutputFileFlag(const String &outputFileFlag)
{
    this->data.outputFileFlag = outputFileFlag;
    this->commitOutputFileFlag();
}

inline void OSCLinkerSettingsDataObject::setOutputFileFlag(String &&outputFileFlag)
{
    this->data.outputFileFlag = std::move(outputFileFlag);
    this->commitOutputFileFlag();
}

inline void OSCLinkerSettingsDataObject::fetchOutputFileFlag()
{
    this->getContext()->fetchValue<Entity::OutputFileFlagField>(this, this->data.outputFileFlag);
}

inline void OSCLinkerSettingsDataObject::commitOutputFileFlag()
{
    this->getContext()->commitValue<Entity::OutputFileFlagField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getFlags() const
{
    return this->data.flags;
}

inline void OSCLinkerSettingsDataObject::setFlags(const String &flags)
{
    this->data.flags = flags;
    this->commitFlags();
}

inline void OSCLinkerSettingsDataObject::setFlags(String &&flags)
{
    this->data.flags = std::move(flags);
    this->commitFlags();
}

inline void OSCLinkerSettingsDataObject::fetchFlags()
{
    this->getContext()->fetchValue<Entity::FlagsField>(this, this->data.flags);
}

inline void OSCLinkerSettingsDataObject::commitFlags()
{
    this->getContext()->commitValue<Entity::FlagsField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getApplicationFlags() const
{
    return this->data.applicationFlags;
}

inline void OSCLinkerSettingsDataObject::setApplicationFlags(const String &applicationFlags)
{
    this->data.applicationFlags = applicationFlags;
    this->commitApplicationFlags();
}

inline void OSCLinkerSettingsDataObject::setApplicationFlags(String &&applicationFlags)
{
    this->data.applicationFlags = std::move(applicationFlags);
    this->commitApplicationFlags();
}

inline void OSCLinkerSettingsDataObject::fetchApplicationFlags()
{
    this->getContext()->fetchValue<Entity::ApplicationFlagsField>(this, this->data.applicationFlags);
}

inline void OSCLinkerSettingsDataObject::commitApplicationFlags()
{
    this->getContext()->commitValue<Entity::ApplicationFlagsField>(this);
}

inline const String &OSCLinkerSettingsDataObject::getLibraryFlags() const
{
    return this->data.libraryFlags;
}

inline void OSCLinkerSettingsDataObject::setLibraryFlags(const String &libraryFlags)
{
    this->data.libraryFlags = libraryFlags;
    this->commitLibraryFlags();
}

inline void OSCLinkerSettingsDataObject::setLibraryFlags(String &&libraryFlags)
{
    this->data.libraryFlags = std::move(libraryFlags);
    this->commitLibraryFlags();
}

inline void OSCLinkerSettingsDataObject::fetchLibraryFlags()
{
    this->getContext()->fetchValue<Entity::LibraryFlagsField>(this, this->data.libraryFlags);
}

inline void OSCLinkerSettingsDataObject::commitLibraryFlags()
{
    this->getContext()->commitValue<Entity::LibraryFlagsField>(this);
}

