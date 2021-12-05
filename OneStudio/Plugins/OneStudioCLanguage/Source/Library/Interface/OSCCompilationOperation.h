/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include <OneStudioProjectLibrary>
#include "OSCCompilerSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.h"
#include "OSCCompilationSettingsDataObject.h"
class OSCCompilationOperation : public OSCompilationOperation
{

public:
    typedef OSCCompilationOperation This;
    typedef OSCompilationOperation Super;
public: //aliases
private: //fields
    OSCCompilerSettingsDataObject::Data compilerSettings;
    OSCCompilationSettingsDataObject::Data compilationSettings;
    OSCFilesSettingsDataObject::Data filesSettings;
    APath destinationPath;
public: //construction
    OSCCompilationOperation() {}
    virtual ~OSCCompilationOperation() {}
public:
    virtual OSCCompilerSettingsDataObject::Data const &getCompilerSettings() const;
    virtual void setCompilerSettings(OSCCompilerSettingsDataObject::Data const &compilerSettings);
    virtual void setCompilerSettings(OSCCompilerSettingsDataObject::Data &&compilerSettings);
public:
    virtual OSCCompilationSettingsDataObject::Data const &getCompilationSettings() const;
    virtual void setCompilationSettings(OSCCompilationSettingsDataObject::Data const &compilationSettings);
    virtual void setCompilationSettings(OSCCompilationSettingsDataObject::Data &&compilationSettings);
public:
    virtual OSCFilesSettingsDataObject::Data const &getFilesSettings() const;
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings);
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings);
public:
    virtual APath const &getDestinationPath() const;
public:
    virtual AError main();
};

