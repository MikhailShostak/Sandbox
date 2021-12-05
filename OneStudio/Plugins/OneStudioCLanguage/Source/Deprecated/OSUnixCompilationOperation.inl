inline APath OSUnixCompilationOperation::getDestinationFile() const
{
	return this->destinationFile;

}

inline const OSUnixCompilationSettingsDataObject::Data &OSUnixCompilationOperation::getSettings() const
{
	return this->settings;

}

inline void OSUnixCompilationOperation::setSettings(const OSUnixCompilationSettingsDataObject::Data &settings)
{
	this->settings = settings;

}

