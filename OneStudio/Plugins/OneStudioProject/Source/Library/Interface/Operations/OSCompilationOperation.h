#pragma once

#include <Foundation>

class OSCompilationOperation: public AOperation
{

public:

	typedef OSCompilationOperation This;
	typedef AOperation Super;


private:

	APath sourceFile;

	APath destinationDirectory;


public:

	/**
	 * Property: sourceFile
	 * Type: APath 
	 * Link: https://google.com
	 * Description: This is description for the sourceFile property
	 */

	APath getSourceFile() const;
	void setSourceFile(const APath &sourceFile);
	void setSourceFile(APath &&sourceFile);

	/**
	 * Property: destinationDirectory
	 * Type: APath 
	 * Link: https://google.com
	 * Description: This is description for the destinationDirectory property
	 */

	APath getDestinationDirectory() const;
	void setDestinationDirectory(const APath &destinationDirectory);
	void setDestinationDirectory(APath &&destinationDirectory);

};
