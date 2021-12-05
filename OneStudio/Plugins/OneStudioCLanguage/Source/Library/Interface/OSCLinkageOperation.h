/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include <OneStudioProjectLibrary>
#include "OSCLinkageSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.h"
#include "OSCLinkerSettingsDataObject.h"
#include "OSLinkageOperation.h"
class OSCLinkageOperation : public OSLinkageOperation
{

public:
    typedef OSCLinkageOperation This;
    typedef OSLinkageOperation Super;
public: //aliases
private: //fields
    OSCLinkageSettingsDataObject::Data linkageSettings;
    bool buildLibrary;
    OSCFilesSettingsDataObject::Data filesSettings;
    OSCLinkerSettingsDataObject::Data linkerSettings;
public: //construction
    OSCLinkageOperation() {}
    virtual ~OSCLinkageOperation() {}
public:
    virtual OSCLinkageSettingsDataObject::Data const &getLinkageSettings() const;
    virtual void setLinkageSettings(OSCLinkageSettingsDataObject::Data const &linkageSettings);
    virtual void setLinkageSettings(OSCLinkageSettingsDataObject::Data &&linkageSettings);
public:
    virtual bool getBuildLibrary() const;
    virtual void setBuildLibrary(bool buildLibrary);
public:
    virtual OSCFilesSettingsDataObject::Data const &getFilesSettings() const;
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings);
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings);
public:
    virtual OSCLinkerSettingsDataObject::Data const &getLinkerSettings() const;
    virtual void setLinkerSettings(OSCLinkerSettingsDataObject::Data const &linkerSettings);
    virtual void setLinkerSettings(OSCLinkerSettingsDataObject::Data &&linkerSettings);
public:
    virtual AError main();
};

