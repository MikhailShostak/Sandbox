//        Author: Insane Team
//          File: OSUnixCompilationSettingsDataObject.h
// Creation date: 01/15/17 08:15:35
//     Copyright: Insane Team, 2016. All rights reseved.

#pragma once

#include <AData>
#include <AFoundation>

//       Class: OSUnixCompilationSettingsDataObject
//        Base: ADataObject
//        Link: 
// Description: 

class OSUnixCompilationSettingsDataObject : public ADataObject
{
public:
    typedef OSUnixCompilationSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSUnixCompilationSettingsDataObjectEntity Entity;

    struct Data
    {
        String includes;
        String flags;
        String includePaths;
        String defines;
        String compiler;
    };

private:
    Data data;

public:
    static const Entity &getStaticEntity();
    const ADataEntity &getEntity() const override;
    AVariant getDataProperty(const String &name) const override;
    void fetch() override;

public:
    const String &getIncludes() const;
    void setIncludes(const String &includes);
    void setIncludes(String &&includes);
    void fetchIncludes();
private:
    void commitIncludes();

public:
    const String &getFlags() const;
    void setFlags(const String &flags);
    void setFlags(String &&flags);
    void fetchFlags();
private:
    void commitFlags();

public:
    const String &getIncludePaths() const;
    void setIncludePaths(const String &includePaths);
    void setIncludePaths(String &&includePaths);
    void fetchIncludePaths();
private:
    void commitIncludePaths();

public:
    const String &getDefines() const;
    void setDefines(const String &defines);
    void setDefines(String &&defines);
    void fetchDefines();
private:
    void commitDefines();

public:
    const String &getCompiler() const;
    void setCompiler(const String &compiler);
    void setCompiler(String &&compiler);
    void fetchCompiler();
private:
    void commitCompiler();
};

class OSUnixCompilationSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;

    static String IncludesFieldName;
    static String FlagsFieldName;
    static String IncludePathsFieldName;
    static String DefinesFieldName;
    static String CompilerFieldName;

public:
    typedef OSUnixCompilationSettingsDataObject DataType;

    static const String &getIncludesFieldName();
    typedef StringDataField<DataType, IncludesFieldName, &OSUnixCompilationSettingsDataObject::getIncludes, &OSUnixCompilationSettingsDataObject::setIncludes> IncludesField;

    static const String &getFlagsFieldName();
    typedef StringDataField<DataType, FlagsFieldName, &OSUnixCompilationSettingsDataObject::getFlags, &OSUnixCompilationSettingsDataObject::setFlags> FlagsField;

    static const String &getIncludePathsFieldName();
    typedef StringDataField<DataType, IncludePathsFieldName, &OSUnixCompilationSettingsDataObject::getIncludePaths, &OSUnixCompilationSettingsDataObject::setIncludePaths> IncludePathsField;

    static const String &getDefinesFieldName();
    typedef StringDataField<DataType, DefinesFieldName, &OSUnixCompilationSettingsDataObject::getDefines, &OSUnixCompilationSettingsDataObject::setDefines> DefinesField;

    static const String &getCompilerFieldName();
    typedef StringDataField<DataType, CompilerFieldName, &OSUnixCompilationSettingsDataObject::getCompiler, &OSUnixCompilationSettingsDataObject::setCompiler> CompilerField;

    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

