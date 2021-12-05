/* DO NOT MODIFY, THIS FILE WAS GENERATED! */
#pragma once

#include <Foundation>
class OSLinkageOperation : public AOperation
{

public:
    typedef OSLinkageOperation This;
    typedef AOperation Super;
public: //aliases
private: //fields
    APathList sourceFiles;
    APath destinationPath;
public: //construction
    OSLinkageOperation() {}
    virtual ~OSLinkageOperation() {}
public:
    virtual APathList getSourceFiles() const;
    virtual void setSourceFiles(APathList sourceFiles);
public:
    virtual APath getDestinationPath() const;
    virtual void setDestinationPath(APath destinationPath);
};

