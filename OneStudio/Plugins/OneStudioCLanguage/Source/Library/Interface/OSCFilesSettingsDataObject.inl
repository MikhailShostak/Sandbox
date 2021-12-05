#pragma once

inline const ADataEntity &OSCFilesSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCFilesSettingsDataObject::fetch()
{
    this->fetchObjectFileName();
    this->fetchStaticLibraryFileName();
    this->fetchDynamicLibraryFileName();
    this->fetchApplicationFileName();
    this->fetchDebugSymbolsFileName();
}

inline const String &OSCFilesSettingsDataObject::getObjectFileName() const
{
    return this->data.objectFileName;
}

inline void OSCFilesSettingsDataObject::setObjectFileName(const String &objectFileName)
{
    this->data.objectFileName = objectFileName;
    this->commitObjectFileName();
}

inline void OSCFilesSettingsDataObject::setObjectFileName(String &&objectFileName)
{
    this->data.objectFileName = std::move(objectFileName);
    this->commitObjectFileName();
}

inline void OSCFilesSettingsDataObject::fetchObjectFileName()
{
    this->getContext()->fetchValue<Entity::ObjectFileNameField>(this, this->data.objectFileName);
}

inline void OSCFilesSettingsDataObject::commitObjectFileName()
{
    this->getContext()->commitValue<Entity::ObjectFileNameField>(this);
}

inline const String &OSCFilesSettingsDataObject::getStaticLibraryFileName() const
{
    return this->data.staticLibraryFileName;
}

inline void OSCFilesSettingsDataObject::setStaticLibraryFileName(const String &staticLibraryFileName)
{
    this->data.staticLibraryFileName = staticLibraryFileName;
    this->commitStaticLibraryFileName();
}

inline void OSCFilesSettingsDataObject::setStaticLibraryFileName(String &&staticLibraryFileName)
{
    this->data.staticLibraryFileName = std::move(staticLibraryFileName);
    this->commitStaticLibraryFileName();
}

inline void OSCFilesSettingsDataObject::fetchStaticLibraryFileName()
{
    this->getContext()->fetchValue<Entity::StaticLibraryFileNameField>(this, this->data.staticLibraryFileName);
}

inline void OSCFilesSettingsDataObject::commitStaticLibraryFileName()
{
    this->getContext()->commitValue<Entity::StaticLibraryFileNameField>(this);
}

inline const String &OSCFilesSettingsDataObject::getDynamicLibraryFileName() const
{
    return this->data.dynamicLibraryFileName;
}

inline void OSCFilesSettingsDataObject::setDynamicLibraryFileName(const String &dynamicLibraryFileName)
{
    this->data.dynamicLibraryFileName = dynamicLibraryFileName;
    this->commitDynamicLibraryFileName();
}

inline void OSCFilesSettingsDataObject::setDynamicLibraryFileName(String &&dynamicLibraryFileName)
{
    this->data.dynamicLibraryFileName = std::move(dynamicLibraryFileName);
    this->commitDynamicLibraryFileName();
}

inline void OSCFilesSettingsDataObject::fetchDynamicLibraryFileName()
{
    this->getContext()->fetchValue<Entity::DynamicLibraryFileNameField>(this, this->data.dynamicLibraryFileName);
}

inline void OSCFilesSettingsDataObject::commitDynamicLibraryFileName()
{
    this->getContext()->commitValue<Entity::DynamicLibraryFileNameField>(this);
}

inline const String &OSCFilesSettingsDataObject::getApplicationFileName() const
{
    return this->data.applicationFileName;
}

inline void OSCFilesSettingsDataObject::setApplicationFileName(const String &applicationFileName)
{
    this->data.applicationFileName = applicationFileName;
    this->commitApplicationFileName();
}

inline void OSCFilesSettingsDataObject::setApplicationFileName(String &&applicationFileName)
{
    this->data.applicationFileName = std::move(applicationFileName);
    this->commitApplicationFileName();
}

inline void OSCFilesSettingsDataObject::fetchApplicationFileName()
{
    this->getContext()->fetchValue<Entity::ApplicationFileNameField>(this, this->data.applicationFileName);
}

inline void OSCFilesSettingsDataObject::commitApplicationFileName()
{
    this->getContext()->commitValue<Entity::ApplicationFileNameField>(this);
}

inline const String &OSCFilesSettingsDataObject::getDebugSymbolsFileName() const
{
    return this->data.debugSymbolsFileName;
}

inline void OSCFilesSettingsDataObject::setDebugSymbolsFileName(const String &debugSymbolsFileName)
{
    this->data.debugSymbolsFileName = debugSymbolsFileName;
    this->commitDebugSymbolsFileName();
}

inline void OSCFilesSettingsDataObject::setDebugSymbolsFileName(String &&debugSymbolsFileName)
{
    this->data.debugSymbolsFileName = std::move(debugSymbolsFileName);
    this->commitDebugSymbolsFileName();
}

inline void OSCFilesSettingsDataObject::fetchDebugSymbolsFileName()
{
    this->getContext()->fetchValue<Entity::DebugSymbolsFileNameField>(this, this->data.debugSymbolsFileName);
}

inline void OSCFilesSettingsDataObject::commitDebugSymbolsFileName()
{
    this->getContext()->commitValue<Entity::DebugSymbolsFileNameField>(this);
}

