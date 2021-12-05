/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCLinkageSettingsDataObject : public ADataObject
{
public:
    typedef OSCLinkageSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCLinkageSettingsDataObjectEntity Entity;
    struct Data
    {
        String libraryPaths;
        String libraries;
        String frameworks;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getLibraryPaths() const;
    void setLibraryPaths(const String &libraryPaths);
    void setLibraryPaths(String &&libraryPaths);
    void fetchLibraryPaths();
private:
    void commitLibraryPaths();
public:
    const String &getLibraries() const;
    void setLibraries(const String &libraries);
    void setLibraries(String &&libraries);
    void fetchLibraries();
private:
    void commitLibraries();
public:
    const String &getFrameworks() const;
    void setFrameworks(const String &frameworks);
    void setFrameworks(String &&frameworks);
    void fetchFrameworks();
private:
    void commitFrameworks();
};

class OSCLinkageSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String LibraryPathsFieldName;
    static String LibrariesFieldName;
    static String FrameworksFieldName;
public:
    typedef OSCLinkageSettingsDataObject DataType;
    static const String &getLibraryPathsFieldName();
    typedef StringDataField<DataType, LibraryPathsFieldName, &OSCLinkageSettingsDataObject::getLibraryPaths, &OSCLinkageSettingsDataObject::setLibraryPaths> LibraryPathsField;
    static const String &getLibrariesFieldName();
    typedef StringDataField<DataType, LibrariesFieldName, &OSCLinkageSettingsDataObject::getLibraries, &OSCLinkageSettingsDataObject::setLibraries> LibrariesField;
    static const String &getFrameworksFieldName();
    typedef StringDataField<DataType, FrameworksFieldName, &OSCLinkageSettingsDataObject::getFrameworks, &OSCLinkageSettingsDataObject::setFrameworks> FrameworksField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

