
inline AOperationArray OSUnixBuildingOperation::getCompilationOperations() const
{
    return this->compilationOperations;

}

inline void OSUnixBuildingOperation::setCompilationOperations(const AOperationArray &compilationOperations)
{
    this->compilationOperations = compilationOperations;
}

inline void OSUnixBuildingOperation::setCompilationOperations(AOperationArray &&compilationOperations)
{
    this->compilationOperations = std::move(compilationOperations);

}

inline const OSUnixCompilationSettingsDataObject::Data &OSUnixBuildingOperation::getCompilationSettings() const
{
    return this->compilationSettings;

}

inline void OSUnixBuildingOperation::setCompilationSettings(const OSUnixCompilationSettingsDataObject::Data &compilationSettings)
{
    this->compilationSettings = compilationSettings;

}

inline const OSUnixLinkingSettingsDataObject::Data &OSUnixBuildingOperation::getLinkingSettings() const
{
    return this->linkingSettings;

}

inline void OSUnixBuildingOperation::setLinkingSettings(const OSUnixLinkingSettingsDataObject::Data &linkingSettings)
{
    this->linkingSettings = linkingSettings;
}

inline APathList OSUnixBuildingOperation::getObjectFiles() const
{
    return this->objectFiles;

}

