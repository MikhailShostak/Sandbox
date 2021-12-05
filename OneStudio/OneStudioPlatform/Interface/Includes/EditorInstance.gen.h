#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include "Includes/FileSystemItem.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class EditorInstance
{
public:
    virtual ~EditorInstance() {}

    virtual void indexFile(const SharedReference<OSFileSystemItem> &item) {}
    virtual SharedReference<UI::View> loadFile(const SharedReference<OSFileSystemItem> &item, const String &identifier) = 0;
    virtual bool saveFile(const SharedReference<OSFileSystemItem> &item) = 0;
    virtual void closeFile(const SharedReference<OSFileSystemItem> &item) = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
