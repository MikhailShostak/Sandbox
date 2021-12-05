#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

//CLASSGEN END REGION
#include "OneStudioPlatform"

#include "TreeWidget.gen.h"
#include "CreateFileDialog.gen.h"
#include "RenameFileDialog.gen.h"
#include "FileManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
struct Outliner : public UI::TreeWidget<OSFileSystemItem>
{
    SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType depth, OSFileSystemItem *item) override
    {
        SharedReference<UI::DefaultExpandableItemView> itemView = CreateShared<UI::DefaultExpandableItemView>();
        WeakReference<UI::DefaultExpandableItemView> itemViewWeak = itemView;
        itemView->applyParameters(depth, item->getText(), item->getItems().size());
        if (item->isExpanded)
        {
            itemView->expandButton->setBackgroundImage(MinusButtonSmall);
        }
        else
        {
            itemView->expandButton->setBackgroundImage(PlusButtonSmall);
        }
        itemView->expandButton->eventChannel.registerDelegate([this, itemViewWeak, item](UI::TapGestureEvent& event) {
            SharedReference<UI::DefaultExpandableItemView> itemView = itemViewWeak.lock();
            if (item->isExpanded)
            {
                item->isExpanded = false;
                itemView->expandButton->setBackgroundImage(PlusButtonSmall);
                itemView->icon->setImage(::ClosedFolderIcon);
            }
            else
            {
                item->isExpanded = true;
                itemView->expandButton->setBackgroundImage(MinusButtonSmall);
                itemView->icon->setImage(::OpenedFolderIcon);
            }
            UIApplication::getOperationDispatcher().addDelegate([this, item]() {
                notifyUpdateChildren(item);
                return AError::getEmptyError();
            }, true);
        });

        static auto getNextPath = [](const APath& directory, const String& name) {

            APathInfo pathInfo(directory + name);
            if (!pathInfo.isExists())
            {
                return pathInfo.path();
            }

            for (size_t i = 2; i < std::numeric_limits<size_t>::max(); ++i)
            {
                APathInfo pathInfo(directory + (name + std::to_string(i)));
                if (!pathInfo.isExists())
                {
                    return pathInfo.path();
                }
            }

            return directory + (name + std::to_string(std::numeric_limits<size_t>::max()));
        };

        auto createNewItem = [this](OSFileSystemItem* parent, const APath& path, OSFileSystemItemFlags flags) {
            SharedReference<OSFileSystemItem> newItem = CreateShared<OSFileSystemItem>();
            newItem->setPath(path);
            newItem->setText(path.name());
            newItem->setFlags(flags);
            parent->addItem(newItem);
            if (parent->getParent())
            {
                notifyUpdateChildren(parent->getParent());
            }
            else
            {
                notifyUpdateChildren(parent);
            }
        };

        auto menu = CreateShared<UI::MenuView>();
        menu->addAction({ "Show in Explorer", [item](UI::TapGestureEvent& event) {
            system(String("explorer /select," + item->getPath().toString()).data()); //TODO: do not use system
        } });
        menu->addAction({ "Copy full path", [item](UI::TapGestureEvent& event) {
            Clipboard::setData(item->getPath().toString());
        } });
        if (APathInfo(item->getPath()).isDirectory())
        {
            menu->addAction({ "Create directory", [createNewItem, item](UI::TapGestureEvent& event) {
                APath newPath = getNextPath(item->getPath(), "NewDirectory");
                if (APathInfo(newPath).make())
                {
                    createNewItem(item, newPath, OSFileSystemItemFlags::Openable);
                }
            } });
            menu->addAction({ "Create empty file", [createNewItem, item](UI::TapGestureEvent& event) {
                AFile file;
                APath newPath = getNextPath(item->getPath(), "NewFile");
                if (file.open(newPath, AFileOpenMode::WriteBinary))
                {
                    file.close();
                    createNewItem(item, newPath, OSFileSystemItemFlags());
                }
            } });
            //TODO: implement file creation
            menu->addAction({ "Create ClassGen file...", [createNewItem, item](UI::TapGestureEvent& event) {
                static UI::Window newFileWindow;
                SharedReference<CreateFileDialog> view = CreateShared<CreateFileDialog>();
                WeakReference<CreateFileDialog> weakView = view;
                view->typeList->setElements({ "ApplicationFlow", "BasicType", "Class", "DataObject", "Enumeration", "Flags", "StateMachine", "Texture", "View", "Material", "Scene" });
                view->typeList->setCurrentIndex(2);
                WeakReference<UI::TextField> nameTextField = StaticCast<UI::TextField>(view->getViews()[5]);
                WeakReference<UI::TextField> namespaceTextField = StaticCast<UI::TextField>(view->getViews()[7]);
                view->createButton->eventChannel.registerDelegate([createNewItem, item, weakView](const UI::TapGestureEvent &event) {
                    SharedReference<CreateFileDialog> view = weakView.lock();
                    AJSONObject object;
                    object.insert("Type", view->typeList->getElements()[view->typeList->getCurrentIndex()]);

                    if (!view->namespaceTextField->getText().empty())
                    {
                        object.insert("Namespace", view->namespaceTextField->getText());
                    }

                    APath newPath = getNextPath(item->getPath(), view->nameTextField->getText());
                    if (AJSON::saveToFile(object, newPath))
                    {
                        createNewItem(item, newPath, OSFileSystemItemFlags());
                    }

                    newFileWindow.close();
                });

                view->cancelButton->eventChannel.registerDelegate([](const UI::TapGestureEvent& event) {
                    newFileWindow.close();
                });
                newFileWindow.setGeometry(Math::getCenteredRectangle({ 1920, 1080 }, view->getSize()));
                newFileWindow.setView(view);
                newFileWindow.show();
            } });
        }
        //TODO: implement file renaming in outliner
        menu->addAction({ "Rename...", [this, item](UI::TapGestureEvent& event) {
            static UI::Window renameFileWindow;
            SharedReference<UI::RenameFileDialog> view = CreateShared<UI::RenameFileDialog>();
            SharedReference<UI::TextField> newNameTextField = StaticCast<UI::TextField>(view->getViews()[1]);
            WeakReference<UI::TextField> newNameTextFieldWeak = newNameTextField;
            newNameTextField->setText(item->getText());
            SharedReference<UI::Button> renameButton = StaticCast<UI::Button>(view->getViews()[2]);
            renameButton->eventChannel.registerDelegate([this, item, newNameTextFieldWeak](const UI::TapGestureEvent &event) {
                SharedReference<UI::TextField> newNameTextField = newNameTextFieldWeak.lock();
                APath newPath = getNextPath(item->getPath().directory(), newNameTextField->getText());
                if (APathInfo(item->getPath()).rename(newPath))
                {
                    auto parent = item->getParent();
                    item->setPath(newPath);
                    item->setText(newPath.name());
                    notifyUpdateChildren(parent);
                }
                renameFileWindow.close();
            });
            SharedReference<UI::Button> closeButton = StaticCast<UI::Button>(view->getViews()[3]);
            closeButton->eventChannel.registerDelegate([item, newNameTextField](const UI::TapGestureEvent& event) {
                renameFileWindow.close();
            });
            renameFileWindow.setGeometry(Math::getCenteredRectangle({ 1920, 1080 }, view->getSize()));
            renameFileWindow.setView(view);
            renameFileWindow.show();
        } });
        menu->addAction({ "Remove", [this, item](UI::TapGestureEvent& event) {
            ALogMessage("", "Remove %s", item->getPath().toString());
            auto parent = item->getParent();
            if (APathInfo(item->getPath()).remove())
            {
                item->removeFromParent();
                notifyUpdateChildren(parent);
            }
        } });
        AttachMenuToView(itemView, menu);

        return itemView;
    }

    void onItemTapped(const AObject& sender, UI::TapGestureEvent& event, OSFileSystemItem* item)
    {
        //TODO: optimize
        auto it = std::find_if(item->getParent() ? item->getParent()->getItems().begin() : items.begin(), item->getParent() ? item->getParent()->getItems().end() : items.end(), [&](auto& i) { return i.get() == item; });

        OneStudio::FileManager::getThisInstance().openFileInEditor(*it);
    }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
