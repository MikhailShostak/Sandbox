/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCLinkageOperation.h"

OSCLinkageSettingsDataObject::Data const &OSCLinkageOperation::getLinkageSettings() const
{
    auto &&result = this->linkageSettings;
    return result;
}

void OSCLinkageOperation::setLinkageSettings(OSCLinkageSettingsDataObject::Data const &linkageSettings)
{
    this->linkageSettings = linkageSettings;
}

void OSCLinkageOperation::setLinkageSettings(OSCLinkageSettingsDataObject::Data &&linkageSettings)
{
    this->linkageSettings = std::move(linkageSettings);
}

bool OSCLinkageOperation::getBuildLibrary() const
{
    auto &&result = this->buildLibrary;
    return result;
}

void OSCLinkageOperation::setBuildLibrary(bool buildLibrary)
{
    this->buildLibrary = buildLibrary;
}

OSCFilesSettingsDataObject::Data const &OSCLinkageOperation::getFilesSettings() const
{
    auto &&result = this->filesSettings;
    return result;
}

void OSCLinkageOperation::setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings)
{
    this->filesSettings = filesSettings;
}

void OSCLinkageOperation::setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings)
{
    this->filesSettings = std::move(filesSettings);
}

OSCLinkerSettingsDataObject::Data const &OSCLinkageOperation::getLinkerSettings() const
{
    auto &&result = this->linkerSettings;
    return result;
}

void OSCLinkageOperation::setLinkerSettings(OSCLinkerSettingsDataObject::Data const &linkerSettings)
{
    this->linkerSettings = linkerSettings;
}

void OSCLinkageOperation::setLinkerSettings(OSCLinkerSettingsDataObject::Data &&linkerSettings)
{
    this->linkerSettings = std::move(linkerSettings);
}

