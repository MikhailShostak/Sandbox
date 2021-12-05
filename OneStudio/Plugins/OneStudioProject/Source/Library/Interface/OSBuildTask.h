#pragma once

#include <Data>

#include "ATableAdapter.h"
#include "OSPTask.h"
#include "OSSettings.h"
#include "OSBuildingSettingsDataObject.h"

#include "ProjectData/GeneralSettings.gen.h"

class OSProject;

class OSSettingsDataInstance : public AFileDataInstance<AJSONDataStorage>
{
    bool rootSettings = false;
public:

    /*ADelegate<void(OSSettingsDataInstance *)> onCreateDelegate;
    ADelegate<void(OSSettingsDataInstance *)> onLoadDelegate;
    ADelegate<void(OSSettingsDataInstance *)> onSaveDelegate;*/

    void setRootSettings(bool rootSettings)
    {
        this->rootSettings = rootSettings;
    }

    bool isRootSettings() const
    {
        return rootSettings;
    }

    void onCreate() override
    {
        onInitialize();
        /*if (onCreateDelegate)
        {
            onCreateDelegate(this);
        }*/
    }

    void onLoad() override
    {
        if(!onCache())
        {
            onInitialize();
        }
        /*if (onLoadDelegate)
        {
            onLoadDelegate(this);
        }*/
    }

    /*void onSave() override
    {
        if (onSaveDelegate)
        {
            onSaveDelegate(this);
        }
    }*/

    virtual void onInitialize() {}
    virtual bool onCache() { return false; }

};

class OSBuildSettingsDataInstance : public OneStudioProject::GeneralSettings, public OSSettingsDataInstance
{

    SharedReference<OSBuildingSettingsDataObject> settings;
public:

    using Super = OSSettingsDataInstance;

    const SharedReference<OSBuildingSettingsDataObject> &getBuildingSettings() const
    {
        return settings;
    }

    void onInitialize() override
    {
        settings = getDataContext()->create<OSBuildingSettingsDataObject>();
        if(isRootSettings())
        {
            settings->setProductName("$(TargetName)");
            settings->setSourcePaths("$(ProjectDirectory)/Source");
            settings->setBuildingDirectory("$(ProjectDirectory)/Build");
            settings->setDestinationDirectory("$(ProjectDirectory)/Product");
        }
    }

    bool onCache()
    {
        settings = getDataContext()->fetchFirst<OSBuildingSettingsDataObject>();
        return bool(settings);
    }
};

class OSBuildTaskSettings : public OSTemplateSettings<OSBuildSettingsDataInstance>
{

public:

    String DebugName = "Undefined";

    SizeType getGroupsCount() const override
    {
        return 1;
    }

    String getGroupTitle(size_t groupIndex) const override
    {
        if(groupIndex != 0)
        {
            return String();
        }

        return "Building Settings";
    }

    size_t getRowsCount(size_t groupIndex) const override
    {
        return 4;
    }

    size_t getColumnsCount(size_t groupIndex) const override
    {
        return 2;
    }

    ItemType getItem(size_t groupIndex, size_t rowIndex, size_t columnIndex) const override
    {
        if(groupIndex != 0 || rowIndex >= 4)
        {
            return String();
        }

        if (columnIndex >= 100000)
        {
            columnIndex -= 100000;
            switch (rowIndex)
            {
            case 0:
                return columnIndex == 0 ? OSBuildingSettingsDataObjectEntity::getProductNameFieldName() : getData()->getBuildingSettings()->getProductName();
            case 1:
                return columnIndex == 0 ? OSBuildingSettingsDataObjectEntity::getSourcePathsFieldName() : getData()->getBuildingSettings()->getSourcePaths();
            case 2:
                return columnIndex == 0 ? OSBuildingSettingsDataObjectEntity::getBuildingDirectoryFieldName() : getData()->getBuildingSettings()->getBuildingDirectory();
            case 3:
                return columnIndex == 0 ? OSBuildingSettingsDataObjectEntity::getDestinationDirectoryFieldName() : getData()->getBuildingSettings()->getDestinationDirectory();
            default:
                return String();
            }
        }

        static const char *CompilerSettingsLabels[] = {
            "ProductName",
            "SourcePaths",
            "BuildingDirectory",
            "DestinationDirectory",
        };

        return columnIndex == 0 ? CompilerSettingsLabels[rowIndex] : (&getData()->BuildingSettings.ProductName)[rowIndex];
    }

    void onItemChange(size_t groupIndex, size_t rowIndex, size_t columnIndex, const ItemType &item) override
    {
        if(groupIndex != 0 || rowIndex >= 4 || columnIndex >= 2)
        {
            return;
        }

        (&getData()->BuildingSettings.ProductName)[rowIndex] = item;
    }
};

template<typename SettingsDataInstanceType>
class OSTemplateBuildTask : public OneStudioProject::Task
{

    SharedReference<SettingsDataInstanceType> settings = createNew<SettingsDataInstanceType>();

public:

    const SharedReference<OSBuildSettingsDataInstance> &getBuildSettings() const
    {
        return settings.template as<OSBuildSettingsDataInstance>();
    }

    const SharedReference<SettingsDataInstanceType> &getTaskSettings() const
    {
        return settings;
    }

};
