#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
class OSFileSystemItem;
class OSFileSystemObserver
{
public:

    virtual ~OSFileSystemObserver() {}

    virtual void fileSystemItemInserted(const SharedReference<OSFileSystemItem>& item) {}
    virtual void fileSystemItemRemoved(const SharedReference<OSFileSystemItem>& item) {}
    virtual void fileSystemItemLoaded(const SharedReference<OSFileSystemItem>& item) {}
    virtual void fileSystemItemOpened(const SharedReference<OSFileSystemItem>& item, const String& identifier) {}

};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
