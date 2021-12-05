//        Author: Insane Team
//          File: OSUnixLinkingSettingsDataObject.h
// Creation date: 01/15/17 08:15:35
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <AData>
#include <AFoundation>

//       Class: OSUnixLinkingSettingsDataObject
//        Base: ADataObject
//        Link: 
// Description: 

class OSUnixLinkingSettingsDataObject : public ADataObject
{
public:
    typedef OSUnixLinkingSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSUnixLinkingSettingsDataObjectEntity Entity;

    struct Data
    {
        String flags;
        String libraryPaths;
        String libraries;
        String linker;
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
    const String &getFlags() const;
    void setFlags(const String &flags);
    void setFlags(String &&flags);
    void fetchFlags();
private:
    void commitFlags();

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
    const String &getLinker() const;
    void setLinker(const String &linker);
    void setLinker(String &&linker);
    void fetchLinker();
private:
    void commitLinker();

public:
    const String &getFrameworks() const;
    void setFrameworks(const String &frameworks);
    void setFrameworks(String &&frameworks);
    void fetchFrameworks();
private:
    void commitFrameworks();
};

class OSUnixLinkingSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;

    static String FlagsFieldName;
    static String LibraryPathsFieldName;
    static String LibrariesFieldName;
    static String LinkerFieldName;
    static String FrameworksFieldName;

public:
    typedef OSUnixLinkingSettingsDataObject DataType;

    static const String &getFlagsFieldName();
    typedef StringDataField<DataType, FlagsFieldName, &OSUnixLinkingSettingsDataObject::getFlags, &OSUnixLinkingSettingsDataObject::setFlags> FlagsField;

    static const String &getLibraryPathsFieldName();
    typedef StringDataField<DataType, LibraryPathsFieldName, &OSUnixLinkingSettingsDataObject::getLibraryPaths, &OSUnixLinkingSettingsDataObject::setLibraryPaths> LibraryPathsField;

    static const String &getLibrariesFieldName();
    typedef StringDataField<DataType, LibrariesFieldName, &OSUnixLinkingSettingsDataObject::getLibraries, &OSUnixLinkingSettingsDataObject::setLibraries> LibrariesField;

    static const String &getLinkerFieldName();
    typedef StringDataField<DataType, LinkerFieldName, &OSUnixLinkingSettingsDataObject::getLinker, &OSUnixLinkingSettingsDataObject::setLinker> LinkerField;

    static const String &getFrameworksFieldName();
    typedef StringDataField<DataType, FrameworksFieldName, &OSUnixLinkingSettingsDataObject::getFrameworks, &OSUnixLinkingSettingsDataObject::setFrameworks> FrameworksField;

    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

