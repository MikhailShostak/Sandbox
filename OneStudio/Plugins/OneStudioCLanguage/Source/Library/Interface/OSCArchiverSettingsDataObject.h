/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCArchiverSettingsDataObject : public ADataObject
{
public:
    typedef OSCArchiverSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCArchiverSettingsDataObjectEntity Entity;
    struct Data
    {
        String archiver;
        String outputFileFlag;
        String flags;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getArchiver() const;
    void setArchiver(const String &archiver);
    void setArchiver(String &&archiver);
    void fetchArchiver();
private:
    void commitArchiver();
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
};

class OSCArchiverSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String ArchiverFieldName;
    static String OutputFileFlagFieldName;
    static String FlagsFieldName;
public:
    typedef OSCArchiverSettingsDataObject DataType;
    static const String &getArchiverFieldName();
    typedef StringDataField<DataType, ArchiverFieldName, &OSCArchiverSettingsDataObject::getArchiver, &OSCArchiverSettingsDataObject::setArchiver> ArchiverField;
    static const String &getOutputFileFlagFieldName();
    typedef StringDataField<DataType, OutputFileFlagFieldName, &OSCArchiverSettingsDataObject::getOutputFileFlag, &OSCArchiverSettingsDataObject::setOutputFileFlag> OutputFileFlagField;
    static const String &getFlagsFieldName();
    typedef StringDataField<DataType, FlagsFieldName, &OSCArchiverSettingsDataObject::getFlags, &OSCArchiverSettingsDataObject::setFlags> FlagsField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

