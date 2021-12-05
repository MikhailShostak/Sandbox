/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCCompilationSettingsDataObject : public ADataObject
{
public:
    typedef OSCCompilationSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCCompilationSettingsDataObjectEntity Entity;
    struct Data
    {
        String defines;
        String includes;
        String includePaths;
    };
private:
    Data data;
public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;
public:
    const String &getDefines() const;
    void setDefines(const String &defines);
    void setDefines(String &&defines);
    void fetchDefines();
private:
    void commitDefines();
public:
    const String &getIncludes() const;
    void setIncludes(const String &includes);
    void setIncludes(String &&includes);
    void fetchIncludes();
private:
    void commitIncludes();
public:
    const String &getIncludePaths() const;
    void setIncludePaths(const String &includePaths);
    void setIncludePaths(String &&includePaths);
    void fetchIncludePaths();
private:
    void commitIncludePaths();
};

class OSCCompilationSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String DefinesFieldName;
    static String IncludesFieldName;
    static String IncludePathsFieldName;
public:
    typedef OSCCompilationSettingsDataObject DataType;
    static const String &getDefinesFieldName();
    typedef StringDataField<DataType, DefinesFieldName, &OSCCompilationSettingsDataObject::getDefines, &OSCCompilationSettingsDataObject::setDefines> DefinesField;
    static const String &getIncludesFieldName();
    typedef StringDataField<DataType, IncludesFieldName, &OSCCompilationSettingsDataObject::getIncludes, &OSCCompilationSettingsDataObject::setIncludes> IncludesField;
    static const String &getIncludePathsFieldName();
    typedef StringDataField<DataType, IncludePathsFieldName, &OSCCompilationSettingsDataObject::getIncludePaths, &OSCCompilationSettingsDataObject::setIncludePaths> IncludePathsField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

