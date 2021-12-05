#pragma once

#include <OneStudioProjectLibrary>

#include "OSUnixCompilationSettingsDataObject.h"
#include "OSUnixLinkingSettingsDataObject.h"
#include "OSUnixLinkingOperation.h"

class OSUnixBuildingOperation: public OSBuildingOperation
{

public:

        typedef OSUnixBuildingOperation This;
        typedef OSBuildingOperation Super;


private:
        AOperationArray compilationOperations;

        OSUnixCompilationSettingsDataObject::Data compilationSettings;
        OSUnixLinkingSettingsDataObject::Data linkingSettings;

        APathList objectFiles;
protected:

        AError main();
private:

        void addSourceFile(const APath &path);
        AError compile();


private:

        /**
         * Property: compilationOperations
         * Type: AOperationArray
         * Link: https://google.com
         * Description: This is description for the compilationOperations property
         */

        AOperationArray getCompilationOperations() const;
        void setCompilationOperations(const AOperationArray &compilationOperations);
        void setCompilationOperations(AOperationArray &&compilationOperations);

public:

        OSUnixLinkingOperation::LinkingType type;

        /**
         * Property: compilationSettings
         * Type: SharedReference<OSUnixCompilationSettings>
         * Link: https://google.com
         * Description: This is description for the compilationSettings property
         */

        const OSUnixCompilationSettingsDataObject::Data &getCompilationSettings() const;
        void setCompilationSettings(const OSUnixCompilationSettingsDataObject::Data &compilationSettings);

        /**
         * Property: linkingSettings
         * Type: SharedReference<OSUnixLinkingSettings>
         * Link: https://google.com
         * Description: This is description for the linkingSettings property
         */

        const OSUnixLinkingSettingsDataObject::Data &getLinkingSettings() const;
        void setLinkingSettings(const OSUnixLinkingSettingsDataObject::Data &linkingSettings);

        /**
         * Property: objectFiles
         * Type: APathList
         * Link: https://google.com
         * Description: This is description for the objectFiles property
         */

        APathList getObjectFiles() const;

};
