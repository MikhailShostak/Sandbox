/* DO NOT MODIFY, THIS FILE WAS GENERATED! */

#include "OSCCompilationOperation.h"

OSCCompilerSettingsDataObject::Data const &OSCCompilationOperation::getCompilerSettings() const
{
    auto &&result = this->compilerSettings;
    return result;
}

void OSCCompilationOperation::setCompilerSettings(OSCCompilerSettingsDataObject::Data const &compilerSettings)
{
    this->compilerSettings = compilerSettings;
}

void OSCCompilationOperation::setCompilerSettings(OSCCompilerSettingsDataObject::Data &&compilerSettings)
{
    this->compilerSettings = std::move(compilerSettings);
}

OSCCompilationSettingsDataObject::Data const &OSCCompilationOperation::getCompilationSettings() const
{
    auto &&result = this->compilationSettings;
    return result;
}

void OSCCompilationOperation::setCompilationSettings(OSCCompilationSettingsDataObject::Data const &compilationSettings)
{
    this->compilationSettings = compilationSettings;
}

void OSCCompilationOperation::setCompilationSettings(OSCCompilationSettingsDataObject::Data &&compilationSettings)
{
    this->compilationSettings = std::move(compilationSettings);
}

OSCFilesSettingsDataObject::Data const &OSCCompilationOperation::getFilesSettings() const
{
    auto &&result = this->filesSettings;
    return result;
}

void OSCCompilationOperation::setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings)
{
    this->filesSettings = filesSettings;
}

void OSCCompilationOperation::setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings)
{
    this->filesSettings = std::move(filesSettings);
}

APath const &OSCCompilationOperation::getDestinationPath() const
{
    auto &&result = this->destinationPath;
    return result;
}

