#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "OneStudioPlatform"
#include "Foundation"
#include "SettingsEntry.gen.h"
#include "DeveloperLibrary.gen.h"

//CLASSGEN END REGION
#include <Experimental>

#include "CreateFileDialog.gen.h"
#include "RenameFileDialog.gen.h"

#include "DeveloperLibrary.gen.h"

#include "WorkspaceData.gen.h"

#include "Task.gen.h"
#include "TreeWidget.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationManager : public Core::ApplicationComponent2, public OneStudioPlatform::ApplicationContext
//CLASSGEN END REGION
, public ApplicationComponent
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationManager This;
    typedef Serializable Super;
    typedef std::tuple<ApplicationComponent, OneStudioPlatform::ApplicationContext> Interfaces;
protected:
    Array<OneStudio::SettingsEntry> Entries;
OneStudio::DeveloperLibrary DeveloperLibrary;
public:
    ApplicationManager();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<OneStudio::SettingsEntry> getEntries() const;
    void setEntries(Array<OneStudio::SettingsEntry> const &Entries);
    void setEntries(Array<OneStudio::SettingsEntry> &&Entries);
    OneStudio::DeveloperLibrary getDeveloperLibrary() const;
    void setDeveloperLibrary(OneStudio::DeveloperLibrary const &DeveloperLibrary);
    void setDeveloperLibrary(OneStudio::DeveloperLibrary &&DeveloperLibrary);
//CLASSGEN END REGION
    void loadDeveloperLibrary();

    void load();
    void save();

public:

    void onLoad() override;
    void onUnload() override;
    virtual void onApplicationStart(AApplication const &application);
    virtual void onApplicationFinish(AApplication const &application);

    static ApplicationManager& getThisInstance() { return getInstanceAs<ApplicationManager>(); }

    APath getDeveloperDirectory() const override { return APath::getUserDirectory() + "Developer"; }
    APath getLibraryDirectory() const override { return getDeveloperDirectory() + "Library"; }

    bool registerCommand(const String& command, const std::function<void(const Array<String> & arguments)>& callback) override;
    bool registerOutliner(const SharedReference<OSOutliner>& outliner) override;
    bool registerControlVersionSystem(const SharedReference<OSControlVersionSystem>& cvs) override;
    bool registerToolBarItem(const String& identifier, SharedReference<UI::View> const& view) override;
    bool registerWindow(const String& identifier, SharedReference<UI::View> const& view) override;

    Array<SharedReference<AApplicationPlugin<OSPlugin>>> plugins;
    void loadExtension(const Path &path) override;
    void unloadExtension(const String &package) override;

    void showProperties(UI::View* view) override;

    void print(const String& text) override;
    void log(const String& text, const String& file = String(), const String& indication = String()) override;
    void warning(const String& text, const String& file = String(), const String& indication = String()) override;
    void error(const String& text, const String& file = String(), const String& indication = String()) override;
    
    void loadConsole(OneStudio::Task &task);
    void loadSettings(OneStudio::Task &task);
    void loadToolbar(OneStudio::Task &task);
    void loadExtensions(OneStudio::Task &task);
    void loadMIMETypes(OneStudio::Task &task);
    void loadWorkspace(OneStudio::Task &task);
    void indexLibrary(OneStudio::Task &task);
    void printConsoleCommands(OneStudio::Task &task);
    void applyConsoleCommands(OneStudio::Task &task);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
