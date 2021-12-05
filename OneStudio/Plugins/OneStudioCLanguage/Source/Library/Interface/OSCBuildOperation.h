/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include <OneStudioProjectLibrary>
#include "OSCCompilerSettingsDataObject.h"
#include "OSCCompilationSettingsDataObject.h"
#include "OSCArchiverSettingsDataObject.h"
#include "OSCLinkerSettingsDataObject.h"
#include "OSCLinkageSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.h"
class OSCBuildOperation : public OSBuildingOperation
{

public:
    typedef OSCBuildOperation This;
    typedef OSBuildingOperation Super;
public: //aliases
private: //fields
    AOperationArray compilationOperations;
    APathList objectFiles;
    OSCCompilerSettingsDataObject::Data compilerSettings;
    OSCCompilationSettingsDataObject::Data compilationSettings;
    OSCArchiverSettingsDataObject::Data archiverSettings;
    OSCLinkerSettingsDataObject::Data linkerSettings;
    OSCLinkageSettingsDataObject::Data linkageSettings;
    OSCFilesSettingsDataObject::Data filesSettings;
    bool buildLibrary;
public: //construction
    OSCBuildOperation() {}
    virtual ~OSCBuildOperation() {}
public:
    virtual APathList getObjectFiles() const;
    virtual void setObjectFiles(APathList objectFiles);
public:
    virtual OSCCompilerSettingsDataObject::Data const &getCompilerSettings() const;
    virtual void setCompilerSettings(OSCCompilerSettingsDataObject::Data const &compilerSettings);
    virtual void setCompilerSettings(OSCCompilerSettingsDataObject::Data &&compilerSettings);
public:
    virtual OSCCompilationSettingsDataObject::Data const &getCompilationSettings() const;
    virtual void setCompilationSettings(OSCCompilationSettingsDataObject::Data const &compilationSettings);
    virtual void setCompilationSettings(OSCCompilationSettingsDataObject::Data &&compilationSettings);
public:
    virtual OSCArchiverSettingsDataObject::Data const &getArchiverSettings() const;
    virtual void setArchiverSettings(OSCArchiverSettingsDataObject::Data const &archiverSettings);
    virtual void setArchiverSettings(OSCArchiverSettingsDataObject::Data &&archiverSettings);
public:
    virtual OSCLinkerSettingsDataObject::Data const &getLinkerSettings() const;
    virtual void setLinkerSettings(OSCLinkerSettingsDataObject::Data const &linkerSettings);
    virtual void setLinkerSettings(OSCLinkerSettingsDataObject::Data &&linkerSettings);
public:
    virtual OSCLinkageSettingsDataObject::Data const &getLinkageSettings() const;
    virtual void setLinkageSettings(OSCLinkageSettingsDataObject::Data const &linkageSettings);
    virtual void setLinkageSettings(OSCLinkageSettingsDataObject::Data &&linkageSettings);
public:
    virtual OSCFilesSettingsDataObject::Data const &getFilesSettings() const;
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings);
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings);
public:
    virtual bool getBuildLibrary() const;
    virtual void setBuildLibrary(bool buildLibrary);
public:
    virtual AError main();
public:
    virtual AError compile();
public:
    virtual void addSourceFile(APath const &path);
};

