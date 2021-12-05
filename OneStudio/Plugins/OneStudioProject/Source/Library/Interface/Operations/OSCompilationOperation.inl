inline APath OSCompilationOperation::getSourceFile() const
{
	return this->sourceFile;

}

inline void OSCompilationOperation::setSourceFile(const APath &sourceFile)
{
	this->sourceFile = sourceFile;

}

inline void OSCompilationOperation::setSourceFile(APath &&sourceFile)
{
	this->sourceFile = std::move(sourceFile);

}

inline APath OSCompilationOperation::getDestinationDirectory() const
{
	return this->destinationDirectory;

}

inline void OSCompilationOperation::setDestinationDirectory(const APath &destinationDirectory)
{
	this->destinationDirectory = destinationDirectory;

}

inline void OSCompilationOperation::setDestinationDirectory(APath &&destinationDirectory)
{
	this->destinationDirectory = std::move(destinationDirectory);

}

