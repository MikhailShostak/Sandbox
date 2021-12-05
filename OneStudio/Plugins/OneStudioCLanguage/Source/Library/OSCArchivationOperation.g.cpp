/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCArchivationOperation.h"

OSCArchiverSettingsDataObject::Data const &OSCArchivationOperation::getArchiverSettings() const
{
    auto &&result = this->archiverSettings;
    return result;
}

void OSCArchivationOperation::setArchiverSettings(OSCArchiverSettingsDataObject::Data const &archiverSettings)
{
    this->archiverSettings = archiverSettings;
}

void OSCArchivationOperation::setArchiverSettings(OSCArchiverSettingsDataObject::Data &&archiverSettings)
{
    this->archiverSettings = std::move(archiverSettings);
}

OSCFilesSettingsDataObject::Data const &OSCArchivationOperation::getFilesSettings() const
{
    auto &&result = this->filesSettings;
    return result;
}

void OSCArchivationOperation::setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings)
{
    this->filesSettings = filesSettings;
}

void OSCArchivationOperation::setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings)
{
    this->filesSettings = std::move(filesSettings);
}

