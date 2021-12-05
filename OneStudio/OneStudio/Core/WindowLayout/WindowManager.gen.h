#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "WindowLayout.gen.h"
#include "Foundation"
#include "Experimental"
#include "ToolbarItem.gen.h"

//CLASSGEN END REGION
#include "Outliner.gen.h"
#include "ToolbarItem.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class WindowManager : public Serializable, public Core::ApplicationComponent2
//CLASSGEN END REGION
, public ApplicationComponent
, public AbstractSingleton<WindowManager>
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef WindowManager This;
    typedef Serializable Super;
    typedef std::tuple<ApplicationComponent> Interfaces;
protected:
    OneStudio::WindowLayout WindowLayout;
Array<Core::CommandShortcut> Shortcuts;
Array<Text> CurrentToolbarCommands;
Array<OneStudio::ToolbarItem> AvailableToolbarCommands;
public:
    WindowManager();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    OneStudio::WindowLayout getWindowLayout() const;
    void setWindowLayout(OneStudio::WindowLayout const &WindowLayout);
    void setWindowLayout(OneStudio::WindowLayout &&WindowLayout);
    Array<Core::CommandShortcut> getShortcuts() const;
    void setShortcuts(Array<Core::CommandShortcut> const &Shortcuts);
    void setShortcuts(Array<Core::CommandShortcut> &&Shortcuts);
    Array<Text> getCurrentToolbarCommands() const;
    void setCurrentToolbarCommands(Array<Text> const &CurrentToolbarCommands);
    void setCurrentToolbarCommands(Array<Text> &&CurrentToolbarCommands);
    Array<OneStudio::ToolbarItem> getAvailableToolbarCommands() const;
    void setAvailableToolbarCommands(Array<OneStudio::ToolbarItem> const &AvailableToolbarCommands);
    void setAvailableToolbarCommands(Array<OneStudio::ToolbarItem> &&AvailableToolbarCommands);
//CLASSGEN END REGION
    class MainView *mainView = nullptr;
    SharedReference<UI::Outliner> outliner;
    UnorderedDictionary<String, SharedReference<UI::View>> windows;

    ADelegate<void()> onToolbarUpdated;

    static WindowManager &getThisInstance() { return getInstanceAs<WindowManager>(); }

    void onLoad() override;
    void onApplicationStart(AApplication const &application) override;

    void loadWindowLayout();
    void saveWindowLayout();

    void loadShortcuts();
    void saveShortcuts();

    void registerWindow(const String &identifier, const SharedReference<UI::View> &view);
    void unregisterWindows();

    Array<UI::DockViewArea> getAreas(const Array<DockEntry> &dockEntries);

    void registerToolbarCommand(const OneStudio::ToolbarItem &toolbarItem);
    void unregisterToolbarCommand(const OneStudio::ToolbarItem &toolbarItem);
    void unregisterToolbarCommands();

    void FocusFile(const SharedReference<OneStudio::FileInstance> &item);
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
