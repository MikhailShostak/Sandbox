inline APathList OSUnixLinkingOperation::getSourcePaths() const
{
    return this->sourcePaths;

}

inline void OSUnixLinkingOperation::setSourcePaths(const APathList &sourcePaths)
{
    this->sourcePaths = sourcePaths;

}

inline void OSUnixLinkingOperation::setSourcePaths(APathList &&sourcePaths)
{
    this->sourcePaths = std::move(sourcePaths);

}

inline APath OSUnixLinkingOperation::getDestinationPath() const
{
    return this->destinationPath;

}

inline void OSUnixLinkingOperation::setDestinationPath(const APath &destinationPath)
{
    this->destinationPath = destinationPath;

}

inline void OSUnixLinkingOperation::setDestinationPath(APath &&destinationPath)
{
    this->destinationPath = std::move(destinationPath);

}

inline const OSUnixLinkingSettingsDataObject::Data &OSUnixLinkingOperation::getSettings() const
{
    return this->settings;

}

inline void OSUnixLinkingOperation::setSettings(const OSUnixLinkingSettingsDataObject::Data &settings)
{
    this->settings = settings;

}

