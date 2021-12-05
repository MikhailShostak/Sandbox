#pragma once

#include <OSTaskPlugin.h>

#include "OSCCompilerSettingsDataObject.h"
#include "OSCCompilerSettingsDataObject.inl"
#include "OSCCompilationSettingsDataObject.h"
#include "OSCCompilationSettingsDataObject.inl"
#include "OSCArchiverSettingsDataObject.h"
#include "OSCArchiverSettingsDataObject.inl"
#include "OSCLinkerSettingsDataObject.h"
#include "OSCLinkerSettingsDataObject.inl"
#include "OSCLinkageSettingsDataObject.h"
#include "OSCLinkageSettingsDataObject.inl"
#include "OSCFilesSettingsDataObject.h"
#include "OSCFilesSettingsDataObject.inl"

#include "Data/BuildingSettings.gen.h"

class OSUnixBuildingSettingsDataInstance : public OneStudioCLanguage::BuildingSettings, public OSSettingsDataInstance
{
    SharedReference<OSCCompilerSettingsDataObject> compilerSettings;
    SharedReference<OSCCompilationSettingsDataObject> compilationSettings;
    SharedReference<OSCArchiverSettingsDataObject> archiverSettings;
    SharedReference<OSCLinkerSettingsDataObject> linkerSettings;
    SharedReference<OSCLinkageSettingsDataObject> linkageSettings;
    SharedReference<OSCFilesSettingsDataObject> filesSettings;
public:

    SharedReference<OSCCompilerSettingsDataObject> getCompilerSettings() const
    {
        return compilerSettings;
    }

    SharedReference<OSCCompilationSettingsDataObject> getCompilationSettings() const
    {
        return compilationSettings;
    }

    SharedReference<OSCArchiverSettingsDataObject> getArchiverSettings() const
    {
        return archiverSettings;
    }

    SharedReference<OSCLinkerSettingsDataObject> getLinkerSettings() const
    {
        return linkerSettings;
    }

    SharedReference<OSCLinkageSettingsDataObject> getLinkageSettings() const
    {
        return linkageSettings;
    }

    SharedReference<OSCFilesSettingsDataObject> getFilesSettings() const
    {
        return filesSettings;
    }

    void onInitialize() override
    {
        if(!compilerSettings)
        {
            compilerSettings = getDataContext()->create<OSCCompilerSettingsDataObject>();
        }
        if(!compilationSettings)
        {
            compilationSettings = getDataContext()->create<OSCCompilationSettingsDataObject>();
        }
        if(!archiverSettings)
        {
            archiverSettings = getDataContext()->create<OSCArchiverSettingsDataObject>();
        }
        if(!linkerSettings)
        {
            linkerSettings = getDataContext()->create<OSCLinkerSettingsDataObject>();
        }
        if(!linkageSettings)
        {
            linkageSettings = getDataContext()->create<OSCLinkageSettingsDataObject>();
        }
        if(!filesSettings)
        {
            filesSettings = getDataContext()->create<OSCFilesSettingsDataObject>();
        }
    }

    bool onCache()
    {
        compilerSettings = getDataContext()->fetchFirst<OSCCompilerSettingsDataObject>();
        compilationSettings = getDataContext()->fetchFirst<OSCCompilationSettingsDataObject>();
        archiverSettings = getDataContext()->fetchFirst<OSCArchiverSettingsDataObject>();
        linkerSettings = getDataContext()->fetchFirst<OSCLinkerSettingsDataObject>();
        linkageSettings = getDataContext()->fetchFirst<OSCLinkageSettingsDataObject>();
        filesSettings = getDataContext()->fetchFirst<OSCFilesSettingsDataObject>();
        return compilerSettings && compilationSettings && archiverSettings && linkerSettings && linkageSettings && filesSettings;
    }
};

class OSCTaskSettings : public OSTemplateSettings<OSUnixBuildingSettingsDataInstance>
{

public:

    OSCCompilerSettingsDataObject::Data getResolvedCompilerSettings() const;
    OSCCompilationSettingsDataObject::Data getResolvedCompilationSettings() const;
    OSCArchiverSettingsDataObject::Data getResolvedArchiverSettings() const;
    OSCLinkerSettingsDataObject::Data getResolvedLinkerSettings() const;
    OSCLinkageSettingsDataObject::Data getResolvedLinkageSettings() const;
    OSCFilesSettingsDataObject::Data getResolvedFilesSettings() const;

    SizeType getGroupsCount() const override;
    String getGroupTitle(SizeType groupIndex) const override;

    SizeType getRowsCount(SizeType groupIndex) const override;
    SizeType getColumnsCount(SizeType groupIndex) const override;
    ItemType getItem(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const override;

    void onItemChange(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex, const ItemType &item) override;
};
