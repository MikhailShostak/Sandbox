/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCFilesSettingsDataObject : public ADataObject
{
public:
    typedef OSCFilesSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCFilesSettingsDataObjectEntity Entity;
    struct Data
    {
        String objectFileName;
        String staticLibraryFileName;
        String dynamicLibraryFileName;
        String applicationFileName;
        String debugSymbolsFileName;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getObjectFileName() const;
    void setObjectFileName(const String &objectFileName);
    void setObjectFileName(String &&objectFileName);
    void fetchObjectFileName();
private:
    void commitObjectFileName();
public:
    const String &getStaticLibraryFileName() const;
    void setStaticLibraryFileName(const String &staticLibraryFileName);
    void setStaticLibraryFileName(String &&staticLibraryFileName);
    void fetchStaticLibraryFileName();
private:
    void commitStaticLibraryFileName();
public:
    const String &getDynamicLibraryFileName() const;
    void setDynamicLibraryFileName(const String &dynamicLibraryFileName);
    void setDynamicLibraryFileName(String &&dynamicLibraryFileName);
    void fetchDynamicLibraryFileName();
private:
    void commitDynamicLibraryFileName();
public:
    const String &getApplicationFileName() const;
    void setApplicationFileName(const String &applicationFileName);
    void setApplicationFileName(String &&applicationFileName);
    void fetchApplicationFileName();
private:
    void commitApplicationFileName();
public:
    const String &getDebugSymbolsFileName() const;
    void setDebugSymbolsFileName(const String &debugSymbolsFileName);
    void setDebugSymbolsFileName(String &&debugSymbolsFileName);
    void fetchDebugSymbolsFileName();
private:
    void commitDebugSymbolsFileName();
};

class OSCFilesSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String ObjectFileNameFieldName;
    static String StaticLibraryFileNameFieldName;
    static String DynamicLibraryFileNameFieldName;
    static String ApplicationFileNameFieldName;
    static String DebugSymbolsFileNameFieldName;
public:
    typedef OSCFilesSettingsDataObject DataType;
    static const String &getObjectFileNameFieldName();
    typedef StringDataField<DataType, ObjectFileNameFieldName, &OSCFilesSettingsDataObject::getObjectFileName, &OSCFilesSettingsDataObject::setObjectFileName> ObjectFileNameField;
    static const String &getStaticLibraryFileNameFieldName();
    typedef StringDataField<DataType, StaticLibraryFileNameFieldName, &OSCFilesSettingsDataObject::getStaticLibraryFileName, &OSCFilesSettingsDataObject::setStaticLibraryFileName> StaticLibraryFileNameField;
    static const String &getDynamicLibraryFileNameFieldName();
    typedef StringDataField<DataType, DynamicLibraryFileNameFieldName, &OSCFilesSettingsDataObject::getDynamicLibraryFileName, &OSCFilesSettingsDataObject::setDynamicLibraryFileName> DynamicLibraryFileNameField;
    static const String &getApplicationFileNameFieldName();
    typedef StringDataField<DataType, ApplicationFileNameFieldName, &OSCFilesSettingsDataObject::getApplicationFileName, &OSCFilesSettingsDataObject::setApplicationFileName> ApplicationFileNameField;
    static const String &getDebugSymbolsFileNameFieldName();
    typedef StringDataField<DataType, DebugSymbolsFileNameFieldName, &OSCFilesSettingsDataObject::getDebugSymbolsFileName, &OSCFilesSettingsDataObject::setDebugSymbolsFileName> DebugSymbolsFileNameField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

