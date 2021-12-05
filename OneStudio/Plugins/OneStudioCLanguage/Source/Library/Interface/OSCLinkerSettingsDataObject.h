/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCLinkerSettingsDataObject : public ADataObject
{
public:
    typedef OSCLinkerSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCLinkerSettingsDataObjectEntity Entity;
    struct Data
    {
        String linker;
        String libraryFlag;
        String libraryPathFlag;
        String outputFileFlag;
        String flags;
        String applicationFlags;
        String libraryFlags;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getLinker() const;
    void setLinker(const String &linker);
    void setLinker(String &&linker);
    void fetchLinker();
private:
    void commitLinker();
public:
    const String &getLibraryFlag() const;
    void setLibraryFlag(const String &libraryFlag);
    void setLibraryFlag(String &&libraryFlag);
    void fetchLibraryFlag();
private:
    void commitLibraryFlag();
public:
    const String &getLibraryPathFlag() const;
    void setLibraryPathFlag(const String &libraryPathFlag);
    void setLibraryPathFlag(String &&libraryPathFlag);
    void fetchLibraryPathFlag();
private:
    void commitLibraryPathFlag();
public:
    const String &getOutputFileFlag() const;
    void setOutputFileFlag(const String &outputFileFlag);
    void setOutputFileFlag(String &&outputFileFlag);
    void fetchOutputFileFlag();
private:
    void commitOutputFileFlag();
public:
    const String &getFlags() const;
    void setFlags(const String &flags);
    void setFlags(String &&flags);
    void fetchFlags();
private:
    void commitFlags();
public:
    const String &getApplicationFlags() const;
    void setApplicationFlags(const String &applicationFlags);
    void setApplicationFlags(String &&applicationFlags);
    void fetchApplicationFlags();
private:
    void commitApplicationFlags();
public:
    const String &getLibraryFlags() const;
    void setLibraryFlags(const String &libraryFlags);
    void setLibraryFlags(String &&libraryFlags);
    void fetchLibraryFlags();
private:
    void commitLibraryFlags();
};

class OSCLinkerSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String LinkerFieldName;
    static String LibraryFlagFieldName;
    static String LibraryPathFlagFieldName;
    static String OutputFileFlagFieldName;
    static String FlagsFieldName;
    static String ApplicationFlagsFieldName;
    static String LibraryFlagsFieldName;
public:
    typedef OSCLinkerSettingsDataObject DataType;
    static const String &getLinkerFieldName();
    typedef StringDataField<DataType, LinkerFieldName, &OSCLinkerSettingsDataObject::getLinker, &OSCLinkerSettingsDataObject::setLinker> LinkerField;
    static const String &getLibraryFlagFieldName();
    typedef StringDataField<DataType, LibraryFlagFieldName, &OSCLinkerSettingsDataObject::getLibraryFlag, &OSCLinkerSettingsDataObject::setLibraryFlag> LibraryFlagField;
    static const String &getLibraryPathFlagFieldName();
    typedef StringDataField<DataType, LibraryPathFlagFieldName, &OSCLinkerSettingsDataObject::getLibraryPathFlag, &OSCLinkerSettingsDataObject::setLibraryPathFlag> LibraryPathFlagField;
    static const String &getOutputFileFlagFieldName();
    typedef StringDataField<DataType, OutputFileFlagFieldName, &OSCLinkerSettingsDataObject::getOutputFileFlag, &OSCLinkerSettingsDataObject::setOutputFileFlag> OutputFileFlagField;
    static const String &getFlagsFieldName();
    typedef StringDataField<DataType, FlagsFieldName, &OSCLinkerSettingsDataObject::getFlags, &OSCLinkerSettingsDataObject::setFlags> FlagsField;
    static const String &getApplicationFlagsFieldName();
    typedef StringDataField<DataType, ApplicationFlagsFieldName, &OSCLinkerSettingsDataObject::getApplicationFlags, &OSCLinkerSettingsDataObject::setApplicationFlags> ApplicationFlagsField;
    static const String &getLibraryFlagsFieldName();
    typedef StringDataField<DataType, LibraryFlagsFieldName, &OSCLinkerSettingsDataObject::getLibraryFlags, &OSCLinkerSettingsDataObject::setLibraryFlags> LibraryFlagsField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

