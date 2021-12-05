/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
#include <OneStudioProjectLibrary>
#include "OSCArchiverSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.h"
#include "OSLinkageOperation.h"
class OSCArchivationOperation : public OSLinkageOperation
{

public:
    typedef OSCArchivationOperation This;
    typedef OSLinkageOperation Super;
public: //aliases
private: //fields
    OSCArchiverSettingsDataObject::Data archiverSettings;
    OSCFilesSettingsDataObject::Data filesSettings;
public: //construction
    OSCArchivationOperation() {}
    virtual ~OSCArchivationOperation() {}
public:
    virtual OSCArchiverSettingsDataObject::Data const &getArchiverSettings() const;
    virtual void setArchiverSettings(OSCArchiverSettingsDataObject::Data const &archiverSettings);
    virtual void setArchiverSettings(OSCArchiverSettingsDataObject::Data &&archiverSettings);
public:
    virtual OSCFilesSettingsDataObject::Data const &getFilesSettings() const;
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data const &filesSettings);
    virtual void setFilesSettings(OSCFilesSettingsDataObject::Data &&filesSettings);
public:
    virtual AError main();
};

