#include "OSBuildingOperation.h"

void OSBuildingOperation::findFilesWithExtension(const Array<String> &extensions, const ADelegate<void(const APath &file)> &delegate)
{
    for(auto stringPath : buildingSettings.sourcePaths.split(';'))
    {
        APath path = APath(stringPath).resolveWithDirectory(workspaceDirectory);
        APathInfo info(path);
        if(info.isDirectory())
        {
            ADirectory directory(path);
            for(auto &extension : extensions)
            {
                Array<APathInfo> result = directory.findRecursively(extension, AFindFilter::AllFiles);
                for(auto file : result)
                {
                    delegate(file.path());
                }
            }
        }
        else if(info.isFile())
        {
            for(auto &extension : extensions)
            {
                if(path.extension() == extension)
                {
                    delegate(path);
                }
            }
        }
    }
}
