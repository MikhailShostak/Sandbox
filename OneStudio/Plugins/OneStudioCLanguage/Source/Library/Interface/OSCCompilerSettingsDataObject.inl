#pragma once

inline const ADataEntity &OSCCompilerSettingsDataObject::getEntity() const
{
    return getStaticEntity();
}

inline void OSCCompilerSettingsDataObject::fetch()
{
    this->fetchCompiler();
    this->fetchIncludeFlag();
    this->fetchIncludePathFlag();
    this->fetchDefineFlag();
    this->fetchOutputFileFlag();
    this->fetchCompilationFlag();
    this->fetchFlags();
}

inline const String &OSCCompilerSettingsDataObject::getCompiler() const
{
    return this->data.compiler;
}

inline void OSCCompilerSettingsDataObject::setCompiler(const String &compiler)
{
    this->data.compiler = compiler;
    this->commitCompiler();
}

inline void OSCCompilerSettingsDataObject::setCompiler(String &&compiler)
{
    this->data.compiler = std::move(compiler);
    this->commitCompiler();
}

inline void OSCCompilerSettingsDataObject::fetchCompiler()
{
    this->getContext()->fetchValue<Entity::CompilerField>(this, this->data.compiler);
}

inline void OSCCompilerSettingsDataObject::commitCompiler()
{
    this->getContext()->commitValue<Entity::CompilerField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getIncludeFlag() const
{
    return this->data.includeFlag;
}

inline void OSCCompilerSettingsDataObject::setIncludeFlag(const String &includeFlag)
{
    this->data.includeFlag = includeFlag;
    this->commitIncludeFlag();
}

inline void OSCCompilerSettingsDataObject::setIncludeFlag(String &&includeFlag)
{
    this->data.includeFlag = std::move(includeFlag);
    this->commitIncludeFlag();
}

inline void OSCCompilerSettingsDataObject::fetchIncludeFlag()
{
    this->getContext()->fetchValue<Entity::IncludeFlagField>(this, this->data.includeFlag);
}

inline void OSCCompilerSettingsDataObject::commitIncludeFlag()
{
    this->getContext()->commitValue<Entity::IncludeFlagField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getIncludePathFlag() const
{
    return this->data.includePathFlag;
}

inline void OSCCompilerSettingsDataObject::setIncludePathFlag(const String &includePathFlag)
{
    this->data.includePathFlag = includePathFlag;
    this->commitIncludePathFlag();
}

inline void OSCCompilerSettingsDataObject::setIncludePathFlag(String &&includePathFlag)
{
    this->data.includePathFlag = std::move(includePathFlag);
    this->commitIncludePathFlag();
}

inline void OSCCompilerSettingsDataObject::fetchIncludePathFlag()
{
    this->getContext()->fetchValue<Entity::IncludePathFlagField>(this, this->data.includePathFlag);
}

inline void OSCCompilerSettingsDataObject::commitIncludePathFlag()
{
    this->getContext()->commitValue<Entity::IncludePathFlagField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getDefineFlag() const
{
    return this->data.defineFlag;
}

inline void OSCCompilerSettingsDataObject::setDefineFlag(const String &defineFlag)
{
    this->data.defineFlag = defineFlag;
    this->commitDefineFlag();
}

inline void OSCCompilerSettingsDataObject::setDefineFlag(String &&defineFlag)
{
    this->data.defineFlag = std::move(defineFlag);
    this->commitDefineFlag();
}

inline void OSCCompilerSettingsDataObject::fetchDefineFlag()
{
    this->getContext()->fetchValue<Entity::DefineFlagField>(this, this->data.defineFlag);
}

inline void OSCCompilerSettingsDataObject::commitDefineFlag()
{
    this->getContext()->commitValue<Entity::DefineFlagField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getOutputFileFlag() const
{
    return this->data.outputFileFlag;
}

inline void OSCCompilerSettingsDataObject::setOutputFileFlag(const String &outputFileFlag)
{
    this->data.outputFileFlag = outputFileFlag;
    this->commitOutputFileFlag();
}

inline void OSCCompilerSettingsDataObject::setOutputFileFlag(String &&outputFileFlag)
{
    this->data.outputFileFlag = std::move(outputFileFlag);
    this->commitOutputFileFlag();
}

inline void OSCCompilerSettingsDataObject::fetchOutputFileFlag()
{
    this->getContext()->fetchValue<Entity::OutputFileFlagField>(this, this->data.outputFileFlag);
}

inline void OSCCompilerSettingsDataObject::commitOutputFileFlag()
{
    this->getContext()->commitValue<Entity::OutputFileFlagField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getCompilationFlag() const
{
    return this->data.compilationFlag;
}

inline void OSCCompilerSettingsDataObject::setCompilationFlag(const String &compilationFlag)
{
    this->data.compilationFlag = compilationFlag;
    this->commitCompilationFlag();
}

inline void OSCCompilerSettingsDataObject::setCompilationFlag(String &&compilationFlag)
{
    this->data.compilationFlag = std::move(compilationFlag);
    this->commitCompilationFlag();
}

inline void OSCCompilerSettingsDataObject::fetchCompilationFlag()
{
    this->getContext()->fetchValue<Entity::CompilationFlagField>(this, this->data.compilationFlag);
}

inline void OSCCompilerSettingsDataObject::commitCompilationFlag()
{
    this->getContext()->commitValue<Entity::CompilationFlagField>(this);
}

inline const String &OSCCompilerSettingsDataObject::getFlags() const
{
    return this->data.flags;
}

inline void OSCCompilerSettingsDataObject::setFlags(const String &flags)
{
    this->data.flags = flags;
    this->commitFlags();
}

inline void OSCCompilerSettingsDataObject::setFlags(String &&flags)
{
    this->data.flags = std::move(flags);
    this->commitFlags();
}

inline void OSCCompilerSettingsDataObject::fetchFlags()
{
    this->getContext()->fetchValue<Entity::FlagsField>(this, this->data.flags);
}

inline void OSCCompilerSettingsDataObject::commitFlags()
{
    this->getContext()->commitValue<Entity::FlagsField>(this);
}

