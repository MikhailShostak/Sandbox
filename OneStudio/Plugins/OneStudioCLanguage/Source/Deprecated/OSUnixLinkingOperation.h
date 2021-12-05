#pragma once

#include "AFoundation"

#include "OSUnixLinkingSettingsDataObject.h"

#include <AFoundation>

class OSUnixLinkingOperation: public AOperation
{

public:

	typedef OSUnixLinkingOperation This;
	typedef AOperation Super;


private:

	APathList sourcePaths;

	APath destinationPath;

    OSUnixLinkingSettingsDataObject::Data settings;

protected:

    AError main();

public:

    enum LinkingType
    {
        Application,
        StaticLibrary,
        SharedLibrary,
    };

    LinkingType type;

	/**
	 * Property: sourcePaths
	 * Type: APathList 
	 * Link: https://google.com
	 * Description: This is description for the sourcePaths property
	 */

	APathList getSourcePaths() const;
	void setSourcePaths(const APathList &sourcePaths);
	void setSourcePaths(APathList &&sourcePaths);

	/**
	 * Property: destinationPath
	 * Type: APath 
	 * Link: https://google.com
	 * Description: This is description for the destinationPath property
	 */

	APath getDestinationPath() const;
	void setDestinationPath(const APath &destinationPath);
	void setDestinationPath(APath &&destinationPath);

	/**
	 * Property: settings
	 * Type: SharedReference<OSUnixLinkingSettings> 
	 * Link: https://google.com
	 * Description: This is description for the settings property
	 */

    const OSUnixLinkingSettingsDataObject::Data &getSettings() const;
    void setSettings(const OSUnixLinkingSettingsDataObject::Data &settings);

};
