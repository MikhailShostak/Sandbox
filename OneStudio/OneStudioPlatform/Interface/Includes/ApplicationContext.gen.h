#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include <Foundation>
#include "Includes/AbstractSingleton.gen.h"
#include "Includes/Task.gen.h"
#include "Includes/FileSystemObserver.gen.h"
#include "Includes/FileTemplate.gen.h"

class OSPlugin;
class OSOutliner;
class OSControlVersionSystem;
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
class ApplicationContext : public AbstractSingleton<ApplicationContext>
{
public:
    virtual APath getDeveloperDirectory() const = 0;
    virtual APath getLibraryDirectory() const = 0;

    virtual bool registerCommand(const String &command, const std::function<void(const Array<String> &arguments)> &callback) = 0;
    virtual bool registerOutliner(const SharedReference<OSOutliner> &outliner) = 0;
    virtual bool registerControlVersionSystem(const SharedReference<OSControlVersionSystem> &cvs) = 0;
    virtual bool registerToolBarItem(const String &identifier, SharedReference<UI::View> const &view) = 0;
    virtual bool registerWindow(const String &title, SharedReference<UI::View> const &view) = 0;

    virtual void showProperties(UI::View *view) = 0;

    virtual void print(const String &text) = 0;
    virtual void log(const String &text, const String &file = String(), const String &indication = String()) = 0;
    virtual void warning(const String &text, const String &file = String(), const String &indication = String()) = 0;
    virtual void error(const String &text, const String &file = String(), const String &indication = String()) = 0;

    //minor fixes
    virtual void loadExtension(const Path &path) = 0;
    virtual void unloadExtension(const String &package) = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
