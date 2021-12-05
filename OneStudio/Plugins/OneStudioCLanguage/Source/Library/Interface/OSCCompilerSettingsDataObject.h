/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <AData>


class OSCCompilerSettingsDataObject : public ADataObject
{
public:
    typedef OSCCompilerSettingsDataObject This;
    typedef ADataObject Super;
    typedef class OSCCompilerSettingsDataObjectEntity Entity;
    struct Data
    {
        String compiler;
        String includeFlag;
        String includePathFlag;
        String defineFlag;
        String outputFileFlag;
        String compilationFlag;
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
    const String &getCompiler() const;
    void setCompiler(const String &compiler);
    void setCompiler(String &&compiler);
    void fetchCompiler();
private:
    void commitCompiler();
public:
    const String &getIncludeFlag() const;
    void setIncludeFlag(const String &includeFlag);
    void setIncludeFlag(String &&includeFlag);
    void fetchIncludeFlag();
private:
    void commitIncludeFlag();
public:
    const String &getIncludePathFlag() const;
    void setIncludePathFlag(const String &includePathFlag);
    void setIncludePathFlag(String &&includePathFlag);
    void fetchIncludePathFlag();
private:
    void commitIncludePathFlag();
public:
    const String &getDefineFlag() const;
    void setDefineFlag(const String &defineFlag);
    void setDefineFlag(String &&defineFlag);
    void fetchDefineFlag();
private:
    void commitDefineFlag();
public:
    const String &getOutputFileFlag() const;
    void setOutputFileFlag(const String &outputFileFlag);
    void setOutputFileFlag(String &&outputFileFlag);
    void fetchOutputFileFlag();
private:
    void commitOutputFileFlag();
public:
    const String &getCompilationFlag() const;
    void setCompilationFlag(const String &compilationFlag);
    void setCompilationFlag(String &&compilationFlag);
    void fetchCompilationFlag();
private:
    void commitCompilationFlag();
public:
    const String &getFlags() const;
    void setFlags(const String &flags);
    void setFlags(String &&flags);
    void fetchFlags();
private:
    void commitFlags();
};

class OSCCompilerSettingsDataObjectEntity : public ADataEntity
{
    using ADataEntity::ADataEntity;
    static String CompilerFieldName;
    static String IncludeFlagFieldName;
    static String IncludePathFlagFieldName;
    static String DefineFlagFieldName;
    static String OutputFileFlagFieldName;
    static String CompilationFlagFieldName;
    static String FlagsFieldName;
public:
    typedef OSCCompilerSettingsDataObject DataType;
    static const String &getCompilerFieldName();
    typedef StringDataField<DataType, CompilerFieldName, &OSCCompilerSettingsDataObject::getCompiler, &OSCCompilerSettingsDataObject::setCompiler> CompilerField;
    static const String &getIncludeFlagFieldName();
    typedef StringDataField<DataType, IncludeFlagFieldName, &OSCCompilerSettingsDataObject::getIncludeFlag, &OSCCompilerSettingsDataObject::setIncludeFlag> IncludeFlagField;
    static const String &getIncludePathFlagFieldName();
    typedef StringDataField<DataType, IncludePathFlagFieldName, &OSCCompilerSettingsDataObject::getIncludePathFlag, &OSCCompilerSettingsDataObject::setIncludePathFlag> IncludePathFlagField;
    static const String &getDefineFlagFieldName();
    typedef StringDataField<DataType, DefineFlagFieldName, &OSCCompilerSettingsDataObject::getDefineFlag, &OSCCompilerSettingsDataObject::setDefineFlag> DefineFlagField;
    static const String &getOutputFileFlagFieldName();
    typedef StringDataField<DataType, OutputFileFlagFieldName, &OSCCompilerSettingsDataObject::getOutputFileFlag, &OSCCompilerSettingsDataObject::setOutputFileFlag> OutputFileFlagField;
    static const String &getCompilationFlagFieldName();
    typedef StringDataField<DataType, CompilationFlagFieldName, &OSCCompilerSettingsDataObject::getCompilationFlag, &OSCCompilerSettingsDataObject::setCompilationFlag> CompilationFlagField;
    static const String &getFlagsFieldName();
    typedef StringDataField<DataType, FlagsFieldName, &OSCCompilerSettingsDataObject::getFlags, &OSCCompilerSettingsDataObject::setFlags> FlagsField;
    static const Array<String> &getStaticProperties();
    const Array<String> &getProperties() const override;
};

