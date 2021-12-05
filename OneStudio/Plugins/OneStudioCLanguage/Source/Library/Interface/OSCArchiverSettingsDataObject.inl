#pragma once

inline const ADataEntity &OSCArchiverSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCArchiverSettingsDataObject::fetch()
{
    this->fetchArchiver();
    this->fetchOutputFileFlag();
    this->fetchFlags();
}

inline const String &OSCArchiverSettingsDataObject::getArchiver() const
{
    return this->data.archiver;
}

inline void OSCArchiverSettingsDataObject::setArchiver(const String &archiver)
{
    this->data.archiver = archiver;
    this->commitArchiver();
}

inline void OSCArchiverSettingsDataObject::setArchiver(String &&archiver)
{
    this->data.archiver = std::move(archiver);
    this->commitArchiver();
}

inline void OSCArchiverSettingsDataObject::fetchArchiver()
{
    this->getContext()->fetchValue<Entity::ArchiverField>(this, this->data.archiver);
}

inline void OSCArchiverSettingsDataObject::commitArchiver()
{
    this->getContext()->commitValue<Entity::ArchiverField>(this);
}

inline const String &OSCArchiverSettingsDataObject::getOutputFileFlag() const
{
    return this->data.outputFileFlag;
}

inline void OSCArchiverSettingsDataObject::setOutputFileFlag(const String &outputFileFlag)
{
    this->data.outputFileFlag = outputFileFlag;
    this->commitOutputFileFlag();
}

inline void OSCArchiverSettingsDataObject::setOutputFileFlag(String &&outputFileFlag)
{
    this->data.outputFileFlag = std::move(outputFileFlag);
    this->commitOutputFileFlag();
}

inline void OSCArchiverSettingsDataObject::fetchOutputFileFlag()
{
    this->getContext()->fetchValue<Entity::OutputFileFlagField>(this, this->data.outputFileFlag);
}

inline void OSCArchiverSettingsDataObject::commitOutputFileFlag()
{
    this->getContext()->commitValue<Entity::OutputFileFlagField>(this);
}

inline const String &OSCArchiverSettingsDataObject::getFlags() const
{
    return this->data.flags;
}

inline void OSCArchiverSettingsDataObject::setFlags(const String &flags)
{
    this->data.flags = flags;
    this->commitFlags();
}

inline void OSCArchiverSettingsDataObject::setFlags(String &&flags)
{
    this->data.flags = std::move(flags);
    this->commitFlags();
}

inline void OSCArchiverSettingsDataObject::fetchFlags()
{
    this->getContext()->fetchValue<Entity::FlagsField>(this, this->data.flags);
}

inline void OSCArchiverSettingsDataObject::commitFlags()
{
    this->getContext()->commitValue<Entity::FlagsField>(this);
}

