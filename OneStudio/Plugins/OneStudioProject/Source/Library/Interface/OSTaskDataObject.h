/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Data>


class OSTaskDataObject : public ADataObject
{
public:
    typedef OSTaskDataObject This;
    typedef ADataObject Super;
    typedef class OSTaskDataObjectEntity Entity;
    struct Data
    {
        String package;
        uint64_t index;
        String stepType;
        String description;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getPackage() const;
    void setPackage(const String &package);
    void setPackage(String &&package);
    void fetchPackage();
private:
    void commitPackage();
public:
    uint64_t getIndex() const;
    void setIndex(uint64_t index);
    void fetchIndex();
private:
    void commitIndex();
public:
    const String &getStepType() const;
    void setStepType(const String &stepType);
    void setStepType(String &&stepType);
    void fetchStepType();
private:
    void commitStepType();
public:
    const String &getDescription() const;
    void setDescription(const String &description);
    void setDescription(String &&description);
    void fetchDescription();
private:
    void commitDescription();
};

class OSTaskDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String PackageFieldName;
    static String IndexFieldName;
    static String StepTypeFieldName;
    static String DescriptionFieldName;
public:
    typedef OSTaskDataObject DataType;
    static const String &getPackageFieldName();
    typedef StringDataField<DataType, PackageFieldName, &OSTaskDataObject::getPackage, &OSTaskDataObject::setPackage> PackageField;
    static const String &getIndexFieldName();
    typedef ANumberDataField<DataType, uint64_t, IndexFieldName, &OSTaskDataObject::getIndex, &OSTaskDataObject::setIndex> IndexField;
    static const String &getStepTypeFieldName();
    typedef StringDataField<DataType, StepTypeFieldName, &OSTaskDataObject::getStepType, &OSTaskDataObject::setStepType> StepTypeField;
    static const String &getDescriptionFieldName();
    typedef StringDataField<DataType, DescriptionFieldName, &OSTaskDataObject::getDescription, &OSTaskDataObject::setDescription> DescriptionField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

