#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include <Foundation>
#include "Includes/AbstractSingleton.gen.h"
#include "Includes/FileSystemObserver.gen.h"
#include "Includes/FileTemplate.gen.h"
#include "Includes/EditorData.gen.h"

class OSFileSystemItem;
namespace UI
{
class View;
class Menu;
}
class AEventDispatcher;
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class FileContext : public AbstractSingleton<FileContext>
{
public:
    virtual void registerFileTemplate(const String &group, const SharedReference<OneStudioPlatform::FileTemplate> &fileTemplate) = 0;
    virtual void registerEditor(const OneStudioPlatform::EditorData &editor) = 0;
    virtual void unregisterEditor(const String &identifier) = 0;
    virtual void unregisterEditors(const String &extension) = 0;

    virtual void addObserver(OSFileSystemObserver * const &observer) = 0;
    virtual void removeObserver(OSFileSystemObserver * const &observer) = 0;

    virtual SharedReference<OSFileSystemItem> findFileSystemItem(const String &name, const bool &recursively = true) = 0;
    virtual void insertFileSystemItem(const SharedReference<OSFileSystemItem> &item) = 0;
    virtual void removeFileSystemItem(const SharedReference<OSFileSystemItem> &item) = 0;
    virtual void loadFileSystemItem(const SharedReference<OSFileSystemItem> &item) = 0;
    virtual void openFileSystenItem(const SharedReference<OSFileSystemItem> &item, const String &identifier) = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
