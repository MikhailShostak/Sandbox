/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCBuildOperation.h"


APathList OSCBuildOperation::getObjectFiles() const
{
    auto &&result = this->objectFiles;
    return result;
}

void OSCBuildOperation::setObjectFiles(APathList objectFiles)
{
    this->objectFiles = objectFiles;
}

OSCCompilerSettingsDataObject::Data const &OSCBuildOperation::getCompilerSettings() const
{
    auto &&result = this->compilerSettings;
    return result;
}

void OSCBuildOperation::setCompilerSettings(OSCCompilerSettingsDataObject::Data const &compilerSettings)
{
    this->compilerSettings = compilerSettings;
}

void OSCBuildOperation::setCompilerSettings(OSCCompilerSettingsDataObject::Data &&compilerSettings)
{
    this->compilerSettings = std::move(compilerSettings);
}

OSCCompilationSettingsDataObject::Data const &OSCBuildOperation::getCompilationSettings() const
{
    auto &&result = this->compilationSettings;
    return result;
}

void OSCBuildOperation::setCompilationSettings(OSCCompilationSettingsDataObject::Data const &compilationSettings)
{
    this->compilationSettings = compilationSettings;
}

void OSCBuildOperation::setCompilationSettings(OSCCompilationSettingsDataObject::Data &&compilationSettings)
{
    this->compilationSettings = std::move(compilationSettings);
}

OSCArchiverSettingsDataObject::Data const &OSCBuildOperation::getArchiverSettings() const
{
    auto &&result = this->archiverSettings;
    return result;
}

void OSCBuildOperation::setArchiverSettings(OSCArchiverSettingsDataObject::Data const &archiverSettings)
{
    this->archiverSettings = archiverSettings;
}

void OSCBuildOperation::setArchiverSettings(OSCArchiverSettingsDataObject::Data &&archiverSettings)
{
    this->archiverSettings = std::move(archiverSettings);
}

OSCLinkerSettingsDataObject::Data const &OSCBuildOperation::getLinkerSettings() const
{
    auto &&result = this->linkerSettings;
    return result;
}

void OSCBuildOperation::setLinkerSettings(OSCLinkerSettingsDataObject::Data const &linkerSettings)
{
    this->linkerSettings = linkerSettings;
}

void OSCBuildOperation::setLinkerSettings(OSCLinkerSettingsDataObject::Data &&linkerSettings)
{
    this->linkerSettings = std::move(linkerSettings);
}

OSCLinkageSettingsDataObject::Data const &OSCBuildOperation::getLinkageSettings() const
{
    auto &&result = this->linkageSettings;
    return result;
}

void OSCBuildOperation::setLinkageSettings(OSCLinkageSettingsDataObject::Data const &linkageSettings)
{
    this->linkageSettings = linkageSettings;
}

void OSCBuildOperation::setLinkageSettings(OSCLinkageSettingsDataObject::Data &&linkageSettings)
{
    this->linkageSettings = std::move(linkageSettings);
}

OSCFilesSettingsDataObject::Data const &OSCBuildOperation::getFilesSettings() const
{
    auto &&result = this->filesSettings;
    return result;
}

void OSCBuildOperation::setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings)
{
    this->filesSettings = filesSettings;
}

void OSCBuildOperation::setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings)
{
    this->filesSettings = std::move(filesSettings);
}

bool OSCBuildOperation::getBuildLibrary() const
{
    auto &&result = this->buildLibrary;
    return result;
}

void OSCBuildOperation::setBuildLibrary(bool buildLibrary)
{
    this->buildLibrary = buildLibrary;
}

