#pragma once

#include <Foundation>

#include "OSBuildingSettingsDataObject.h"

class OSBuildingOperation: public AOperation
{

public:

        typedef OSBuildingOperation This;
        typedef AOperation Super;


private:

        OSBuildingSettingsDataObject::Data buildingSettings;
protected:

        virtual void findFilesWithExtension(const Array<String> &extensions, const ADelegate<void(const APath &path)> &delegate);

public:

        APath workspaceDirectory;

        const OSBuildingSettingsDataObject::Data &getBuildingSettings() const;
        void setBuildingSettings(const OSBuildingSettingsDataObject::Data &buildingSettings);

};

template<typename Type>
inline void processRecursive(const String &path, Type &&callback)
{
    APair<String, StringHashMap<String>> data = parseAttributesFromArgument(path);
    callback(data.first);
    if (data.second.find("recursive") != data.second.end())
    {
        APathInfo info(data.first);
        if (info.isDirectory())
        {
            ADirectory dir(std::move(info));
            Array<APathInfo> subdirs = dir.findRecursively(AFindFilter::AllDirectories);
            for (const APathInfo &subdir : subdirs)
            {
                callback(subdir.path());
            }
        }
    }
}

inline APair<String, StringHashMap<String>> parseAttributesFromArgument(const String &argument)
{
    APair<String, StringHashMap<String>> data;
    Array<String> values = argument.split('@');

    if(!values)
    {
        return data;
    }

    data.first = values[0]; //main value of the argument
    if(values.size() > 1)
    {
        Array<String> attributes = values[1].split(',');
        for(const String &attribute : attributes)
        {
            Array<String> attributeValues = attribute.split('=');
            if(attributeValues)
            {
                data.second.insert({attributeValues[0], attributeValues.size() > 1 ? attributeValues[1]: String()});
            }
        }
    }
    return data;
}
