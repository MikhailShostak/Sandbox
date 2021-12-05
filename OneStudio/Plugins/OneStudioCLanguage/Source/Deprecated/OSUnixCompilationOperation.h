#pragma once

#include "OSUnixCompilationSettingsDataObject.h"

#include <OneStudioProjectLibrary>

class OSUnixCompilationOperation: public OSCompilationOperation
{

public:

	typedef OSUnixCompilationOperation This;
	typedef OSCompilationOperation Super;


private:

	APath destinationFile;

    OSUnixCompilationSettingsDataObject::Data settings;
protected:

    AError main();


public:

	/**
	 * Property: destinationFile
	 * Type: APath 
	 * Link: https://google.com
	 * Description: This is description for the destinationFile property
	 */

	APath getDestinationFile() const;

	/**
	 * Property: settings
	 * Type: SharedReference<OSUnixCompilationSettings> 
	 * Link: https://google.com
	 * Description: This is description for the settings property
	 */

    const OSUnixCompilationSettingsDataObject::Data &getSettings() const;
    void setSettings(const OSUnixCompilationSettingsDataObject::Data &settings);

};
