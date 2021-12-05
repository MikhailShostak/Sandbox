//CLASSGEN GENERATED REGION: Includes
#include "WindowManager.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "NewFileView.gen.h"
#include "OpenFileView.gen.h"
#include "SettingsView.gen.h"
#include "MainView.gen.h"
#include "ApplicationManager.gen.h"
#include "TaskManager.gen.h"
#include "RecentFilesView.gen.h"
#include "MainViewAsset.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
WindowManager::WindowManager()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void WindowManager::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void WindowManager::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
OneStudio::WindowLayout WindowManager::getWindowLayout() const
{
    return this->WindowLayout;
}
void WindowManager::setWindowLayout(OneStudio::WindowLayout const &WindowLayout)
{
    this->WindowLayout = WindowLayout;
}
void WindowManager::setWindowLayout(OneStudio::WindowLayout &&WindowLayout)
{
    this->WindowLayout = std::move(WindowLayout);
}
Array<Core::CommandShortcut> WindowManager::getShortcuts() const
{
    return this->Shortcuts;
}
void WindowManager::setShortcuts(Array<Core::CommandShortcut> const &Shortcuts)
{
    this->Shortcuts = Shortcuts;
}
void WindowManager::setShortcuts(Array<Core::CommandShortcut> &&Shortcuts)
{
    this->Shortcuts = std::move(Shortcuts);
}
Array<Text> WindowManager::getCurrentToolbarCommands() const
{
    return this->CurrentToolbarCommands;
}
void WindowManager::setCurrentToolbarCommands(Array<Text> const &CurrentToolbarCommands)
{
    this->CurrentToolbarCommands = CurrentToolbarCommands;
}
void WindowManager::setCurrentToolbarCommands(Array<Text> &&CurrentToolbarCommands)
{
    this->CurrentToolbarCommands = std::move(CurrentToolbarCommands);
}
Array<OneStudio::ToolbarItem> WindowManager::getAvailableToolbarCommands() const
{
    return this->AvailableToolbarCommands;
}
void WindowManager::setAvailableToolbarCommands(Array<OneStudio::ToolbarItem> const &AvailableToolbarCommands)
{
    this->AvailableToolbarCommands = AvailableToolbarCommands;
}
void WindowManager::setAvailableToolbarCommands(Array<OneStudio::ToolbarItem> &&AvailableToolbarCommands)
{
    this->AvailableToolbarCommands = std::move(AvailableToolbarCommands);
}
//CLASSGEN END REGION
void WindowManager::registerWindow(const String &identifier, const SharedReference<UI::View> &view)
{
    windows[identifier] = view;
}

void WindowManager::unregisterWindows()
{
    windows.clear();
}

Array<UI::DockViewArea> WindowManager::getAreas(const Array<DockEntry> &dockEntries) {
    Array<UI::DockViewArea> areas;
    for (const DockEntry &dockEntry : dockEntries)
    {
        Array<UI::DockViewTab> tabs;
        for (const String &id : dockEntry.WindowIdentifiers)
        {
            tabs.push_back({ id, windows[id] });
        }
        areas.push_back(UI::DockViewArea{ tabs });
    }
    return areas;
}

void WindowManager::FocusFile(const SharedReference<OneStudio::FileInstance> &item)
{
    OneStudio::FileInstance *parent = item->getParent();
    while (parent)
    {
        parent->isExpanded = true;
        parent = parent->getParent();
    }
    outliner->notifyUpdateAllItems(); //TODO: check if it's better to update specified items
}

void WindowManager::onApplicationStart(AApplication const &application)
{
    onLoad();
}

void WindowManager::onLoad()
{
    if(!mainView)
    {
        mainView = OneStudio::MainViewAsset_Asset.load().get();
    }
    Console::getInstance().addCommand("Show", [this](const Array<String> &arguments) {
        APath path = arguments[0];
        UIApplication::getOperationDispatcher().addDelegate([this, path]() {
            if (auto file = OneStudio::FileManager::getThisInstance().findIndexedFile(path))
            {
                FocusFile(file);
            }
            return AError::getEmptyError();
        }, true);
    });
    outliner = CreateShared<UI::Outliner>();
    registerWindow("Outliner", outliner);
    auto recentFilesView = CreateShared<OneStudio::RecentFilesView>();
    registerWindow("RecentFiles", recentFilesView);
    registerWindow("Tasks", TaskManager::getThisInstance().view);
    registerWindow("TaskLog", TaskManager::getThisInstance().logView);

    for (const Core::CommandShortcut &shortcut : OneStudio::WindowManager::getThisInstance().getShortcuts())
    {
        mainView->getOwner()->getWindow()->Shortcuts.push_back({ shortcut, [shortcut]() {
            String cmd = shortcut.Command;
            if (!shortcut.Arguments.empty())
            {
                cmd += " " + boost::join(shortcut.Arguments, " ");
            }
            Console::getInstance().applyCommand(cmd);
        } });
    }

    outliner->setSizePolicy(UI::SizePolicy::Expanded);

    mainView->contentView->SharedTabAllocator = [this](const UI::DockViewTab &tabData) {
        SharedReference<UI::DockView::InternalNode::SharedTab> tab = CreateShared<UI::DockView::InternalNode::SharedTab>();
        if (tabData.data.isValue<OneStudio::EditableFile>())
        {
            OneStudio::EditableFile openedFile = tabData.data.asValue<OneStudio::EditableFile>();

            WeakReference<UI::DockView::InternalNode::SharedTab> itemView = tab;

            auto closeFileCallback = [this, itemView, openedFile](UI::TapGestureEvent &event) {
                OneStudio::FileManager::getThisInstance().closeFile(openedFile);
            };
            tab->closeButton->eventChannel.registerDelegate(closeFileCallback);

            auto menu = CreateShared<UI::MenuView>();
            menu->addAction({ "Show in Explorer", [this, itemView, openedFile](UI::TapGestureEvent &event) {
                SharedReference<OneStudio::FileInstance> item = openedFile.FileInstance;
                system(String("explorer /select," + item->getPath().toString()).data()); //TODO: do not use system
            } });
            menu->addAction({ "Show in Content Browser", [this, itemView, openedFile](UI::TapGestureEvent &event) {
                SharedReference<OneStudio::FileInstance> item = openedFile.FileInstance;
                FocusFile(item);
            } });
            menu->addAction({ "Copy full path", [this, itemView, openedFile](UI::TapGestureEvent &event) {
                SharedReference<OneStudio::FileInstance> item = openedFile.FileInstance;
                Clipboard::setData(item->getPath().toString());
            } });
            menu->addAction({ "Reload", [this, itemView, openedFile](UI::TapGestureEvent &event) {
                OneStudio::FileManager::getThisInstance().reloadFile(openedFile);
            } });
            menu->addAction({ "Save", [this, itemView, openedFile](UI::TapGestureEvent &event) {
                OneStudio::FileManager::getThisInstance().saveFile(openedFile);
            } });
            menu->addAction({ "Close", closeFileCallback });
            UI::AttachMenuToView(tab, menu);
        }

        return tab;
    };

    OneStudio::FileManager::getThisInstance().onFileOpened = [this](const OneStudio::EditableFile &file) {
        UIApplication::getOperationDispatcher().addDelegate([this, file]() {
            auto areas = mainView->contentView->getAreas();
            if (areas.size() == 1)
            {
                areas.push_back({});
            }
            UI::DockViewTab tabData{ file.FileInstance->getText(), file.EditorView };
            tabData.data = file;
            areas[1].Tabs.push_back(tabData);
            mainView->contentView->setAreas(areas);
            return AError::getEmptyError();
        }, true);
    };

    OneStudio::FileManager::getThisInstance().onFileClosed = [this](const OneStudio::EditableFile &file) {
        UIApplication::getOperationDispatcher().addDelegate([this, file]() {
            auto areas = mainView->contentView->getAreas();
            for (UI::DockViewArea &area : areas)
            {
                size_t tabIndex = 0;
                for (UI::DockViewTab &tab : area.Tabs)
                {
                    if (tab.data.isValue<EditableFile>() && tab.data.asValue<EditableFile>().EditorView == file.EditorView)
                    {
                        //TODO: Add API for DockView
                        {
                            UI::DockView::InternalNode::InternalTabView *tabView = dynamic_cast<UI::DockView::InternalNode::InternalTabView *>(tab.ContentView->getParent()->getParent());

                            //TODO: Add API for TabView
                            {
                                //TODO: Add API for PageView
                                {
                                    tab.ContentView->removeFromParent();
                                    Array<UI::OverlayData> data;
                                    data.resize(tabView->pages->getData().size());
                                    tabView->pages->setData(data);
                                    tabView->pages->setCurrentPage(tabView->pages->getViews().size() > 0 ? Math::getMin(tabView->pages->getViews().size() - 1, tabView->pages->getCurrentPage()) : 0);
                                }

                                auto tabsData = tabView->getTabs();
                                tabsData.erase(tabsData.begin() + tabIndex);
                                tabView->setTabs(tabsData);
                                tabView->tabs->notifyRemoveItems(tabIndex);
                            }
                        }

                        area.Tabs.erase(area.Tabs.begin() + tabIndex);
                        mainView->contentView->setAreas(areas);

                        ALogMessage("", "Editor instance removed");
                        return AError::getEmptyError();
                    }
                    ++tabIndex;
                }
            }

            return AError::getEmptyError();
        }, true);
    };

    OneStudio::FileManager::getThisInstance().onFileSaved = [this](const OneStudio::EditableFile &file) {
        UIApplication::getOperationDispatcher().addDelegate([this, file]() {
            auto areas = mainView->contentView->getAreas();
            for (UI::DockViewArea &area : areas)
            {
                size_t tabIndex = 0;
                for (UI::DockViewTab &tab : area.Tabs)
                {
                    if (tab.data.isValue<EditableFile>() && tab.data.asValue<EditableFile>().EditorView == file.EditorView)
                    {
                        //TODO: Add API for DockView
                        {
                            UI::DockView::InternalNode::InternalTabView *tabView = dynamic_cast<UI::DockView::InternalNode::InternalTabView *>(tab.ContentView->getParent()->getParent());

                            //TODO: Add API for TabView
                            {
                                tabView->tabViews[tabIndex]->title->setText(area.Tabs[tabIndex].Title);
                            }
                        }
                        return AError::getEmptyError();
                    }
                    ++tabIndex;
                }
            }

            return AError::getEmptyError();
        }, true);
    };

    OneStudio::FileManager::getThisInstance().onFileChanged = [this](const OneStudio::EditableFile &file) {
        UIApplication::getOperationDispatcher().addDelegate([this, file]() {
            auto areas = mainView->contentView->getAreas();
            for (UI::DockViewArea &area : areas)
            {
                size_t tabIndex = 0;
                for (UI::DockViewTab &tab : area.Tabs)
                {
                    if (tab.data.isValue<EditableFile>() && tab.data.asValue<EditableFile>().EditorView == file.EditorView)
                    {
                        //TODO: Add API for DockView
                        {
                            UI::DockView::InternalNode::InternalTabView *tabView = dynamic_cast<UI::DockView::InternalNode::InternalTabView *>(tab.ContentView->getParent()->getParent());

                            //TODO: Add API for TabView
                            {
                                tabView->tabViews[tabIndex]->title->setText(area.Tabs[tabIndex].Title + "*");
                            }
                        }
                        return AError::getEmptyError();
                    }
                    ++tabIndex;
                }
            }
            return AError::getEmptyError();
        }, true);
    };

    onToolbarUpdated = [this]() {
        mainView->toolbar->removeAllViews();
        Array<OneStudio::ToolbarItem> toolbarItems = getAvailableToolbarCommands();
        Array<Text> identifiers = getCurrentToolbarCommands();
        for (const Text &identifier : identifiers)
        {
            auto it = std::find_if(toolbarItems.begin(), toolbarItems.end(), [&](auto &toolbarItem) { return toolbarItem.getIdentifier() == identifier; });
            if (it != toolbarItems.end())
            {
                mainView->toolbar->addView(it->getView());
            }
        }
        Array<UI::FlexBoxData> data;
        data.resize(toolbarItems.size());
        mainView->toolbar->setData(data);
    };
}

void WindowManager::loadWindowLayout()
{
    this->WindowLayout.deserialize(AJSON::valueFromFile(APath::applicationDirectory() + "WindowLayout.json").toObject());
    if (this->WindowLayout.ToolbarItems.empty())
    {
        this->WindowLayout.ToolbarItems = { "NewFile", "OpenFile", "Settings" };
    }
    setCurrentToolbarCommands(this->WindowLayout.ToolbarItems);
    onToolbarUpdated();

    if (WindowLayout.DockEntries.empty())
    {
        DockEntry d1;
        d1.WindowIdentifiers = { "Outliner", "Tasks" };
        DockEntry d2;
        d1.WindowIdentifiers = { "RecentFiles" };
        WindowLayout.DockEntries.push_back(d1);
        WindowLayout.DockEntries.push_back(d2);
    }

    Array<UI::DockViewArea> areas = getAreas(WindowLayout.DockEntries);
    mainView->contentView->setAreas(areas);
}

void WindowManager::saveWindowLayout()
{
    AJSON::saveToFile(toJSONValue(this->WindowLayout), APath::applicationDirectory() + "WindowLayout.json");
}

void WindowManager::loadShortcuts()
{
    fromJSONValue(AJSON::valueFromFile(APath::applicationDirectory() + "Shortcuts.json"), this->Shortcuts);
}

void WindowManager::saveShortcuts()
{
    AJSON::saveToFile(toJSONValue(this->Shortcuts), APath::applicationDirectory() + "Shortcuts.json");
}

void WindowManager::registerToolbarCommand(const OneStudio::ToolbarItem &toolbarItem)
{
    this->AvailableToolbarCommands.push_back(toolbarItem);
}

void WindowManager::unregisterToolbarCommand(const OneStudio::ToolbarItem &toolbarItem)
{

}

void WindowManager::unregisterToolbarCommands()
{
    this->CurrentToolbarCommands.clear();
    this->AvailableToolbarCommands.clear();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
