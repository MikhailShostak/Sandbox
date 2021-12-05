//CLASSGEN GENERATED REGION: Includes
#include "FileManager.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "WindowManager.gen.h"
#include "MainView.gen.h"

#include "FindFilePopup.gen.h"
#include "FindSymbolPopup.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
Math::IntegerVector getDesktopSize()
{
    return Math::IntegerVector{ 1920, 1080 };
}

Array<SharedReference<OSFileSystemItem>> IndexedFiles;

SharedReference<OSFileSystemItem> findOpenedFile(const APath &path, const Array<SharedReference<OSFileSystemItem>> &items)
{
    for (auto &item : items)
    {
        if (item->getPath() == path)
        {
            return item;
        }

        if (auto childItem = findOpenedFile(path, item->getItems()))
        {
            return childItem;
        }
    }

    return nullptr;
}
//CLASSGEN GENERATED REGION: ClassImplementation
FileManager::FileManager()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FileManager::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FileManager::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
OneStudio::WorkspaceData FileManager::getWorkspaceData() const
{
    return this->WorkspaceData;
}
void FileManager::setWorkspaceData(OneStudio::WorkspaceData const &WorkspaceData)
{
    this->WorkspaceData = WorkspaceData;
}
void FileManager::setWorkspaceData(OneStudio::WorkspaceData &&WorkspaceData)
{
    this->WorkspaceData = std::move(WorkspaceData);
}
Array<OneStudio::TypeData> FileManager::getTypes() const
{
    return this->Types;
}
void FileManager::setTypes(Array<OneStudio::TypeData> const &Types)
{
    this->Types = Types;
}
void FileManager::setTypes(Array<OneStudio::TypeData> &&Types)
{
    this->Types = std::move(Types);
}
Array<OneStudioPlatform::EditorData> FileManager::getEditors() const
{
    return this->Editors;
}
void FileManager::setEditors(Array<OneStudioPlatform::EditorData> const &Editors)
{
    this->Editors = Editors;
}
void FileManager::setEditors(Array<OneStudioPlatform::EditorData> &&Editors)
{
    this->Editors = std::move(Editors);
}
Array<OneStudio::EditableFile> FileManager::getOpenedFiles() const
{
    return this->OpenedFiles;
}
void FileManager::setOpenedFiles(Array<OneStudio::EditableFile> const &OpenedFiles)
{
    this->OpenedFiles = OpenedFiles;
}
void FileManager::setOpenedFiles(Array<OneStudio::EditableFile> &&OpenedFiles)
{
    this->OpenedFiles = std::move(OpenedFiles);
}
//CLASSGEN END REGION

void FileManager::onApplicationStart(const AApplication &application)
{
    onLoad();
}

void FileManager::onLoad()
{
    Console::getInstance().addCommand("New", [this](const Array<String> &arguments) {
        if (arguments.empty())
        {
            return;
        }

        APath path(arguments[0]);
        APathInfo(path.directory()).make();
        AFile(path, AFileOpenMode::WriteBinary);
        ALogMessage("", "File created at \"%s\"", path.resolveWithDirectory(APath::workingDirectory()));

        SharedReference<OSFileSystemItem> item = CreateShared<OSFileSystemItem>();
        item->setText(path.name());
        item->setPath(path);

        openFileInEditor(item);

        WindowManager::getThisInstance().outliner->items.push_back(item);
        WindowManager::getThisInstance().outliner->notifyUpdateAllItems();
    });
    Console::getInstance().addCommand("Open", [this](const Array<String> &arguments) {
        if (arguments.empty())
        {
            return;
        }

        openPath(Path(arguments[0]));
    });

    Console::getInstance().addCommand("Save", [this](const Array<String> &arguments) {
        APath path = arguments[0];
        if (auto file = findOpenedFile(path))
        {
            saveFile(*file);
        }
    });

    Console::getInstance().addCommand("SaveAs", [](const Array<String> &arguments) {

    });

    Console::getInstance().addCommand("SaveAll", [this](const Array<String> &arguments) {
        saveAllFiles();
    });

    Console::getInstance().addCommand("Close", [](const Array<String> &arguments) {

    });

    Console::getInstance().addCommand("MarkDirty", [this](const Array<String> &arguments) {
        APath path = arguments[0];
        if (auto file = findOpenedFile(path))
        {
            markFileDirty(*file);
            ALogMessage("", "Marked as dirty %s", path);
        }
    });

    Console::getInstance().addCommand("Find.File", [this](const Array<String> &arguments) {
        static SharedReference<UI::FindFilePopup> popup = CreateShared<UI::FindFilePopup>();
        static SharedReference<UI::Window> window;
        if (!window)
        {
            window = CreateShared<UI::Window>();
            window->setFlags(WindowFlags::Dialog);
            window->setGeometry(Math::getCenteredRectangle(getDesktopSize(), Math::IntegerVector{ 1440, 800 }));
            window->setView(popup);

            struct FindController : public UI::LabelListController<Path>
            {
                String getTitle(const AObject &sender, const ItemType &item) const override { return item.toString(); }
                ItemType createNewItem(const AObject &sender) const override { return ItemType(); }
            };

            static SharedReference<FindController> c = CreateShared<FindController>();
            popup->list->setAdapter(c.get());

            popup->searchField->eventChannel.registerDelegate([&](UI::TextEditedEvent &event) {
                Array<String> keywords;
                boost::split(keywords, event.getText(), boost::is_any_of(" "));
                c->data.clear();
                auto files = IndexedFiles;
                size_t limit = 20;
                for (size_t i = 0; i < files.size() && c->data.size() < limit; ++i)
                {
                    auto name = files[i]->getPath().name();
                    for (auto &keyword : keywords)
                    {
                        if (name.find_first_of(keyword) == -1)
                        {
                            break;
                        }

                        c->data.push_back(files[i]->getPath());
                    }
                }
                popup->list->notifyUpdateAllItems();
            });

            StaticCast<UI::Button>(popup->footer)->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                window->hide();
            });
        }
        window->setVisible(!window->getVisible());
        window->setFocus(*popup->searchField);
    });

    Console::getInstance().addCommand("Find.Symbol", [this](const Array<String> &arguments) {
        static SharedReference<UI::FindSymbolPopup> popup = CreateShared<UI::FindSymbolPopup>();
        static SharedReference<UI::Window> window;
        if (!window)
        {
            window = CreateShared<UI::Window>();
            window->setFlags(WindowFlags::Dialog);
            window->setGeometry(Math::getCenteredRectangle(getDesktopSize(), Math::IntegerVector{ 1440, 800 }));
            window->setView(popup);

            struct FindController : public UI::LabelListController<Path>
            {
                String getTitle(const AObject &sender, const ItemType &item) const override { return item.toString(); }
                ItemType createNewItem(const AObject &sender) const override { return ItemType(); }
            };

            static SharedReference<FindController> c = CreateShared<FindController>();
            popup->list->setAdapter(c.get());

            popup->searchField->eventChannel.registerDelegate([&](UI::TextEditedEvent &event) {
                Array<String> keywords;
                boost::split(keywords, event.getText(), boost::is_any_of(" "));
                c->data.clear();
                auto files = IndexedFiles;
                size_t limit = 20;
                for (size_t i = 0; i < files.size() && c->data.size() < limit; ++i)
                {
                    auto name = files[i]->getPath().name();
                    for (auto &keyword : keywords)
                    {
                        if (name.find_first_of(keyword) == -1)
                        {
                            break;
                        }

                        c->data.push_back(files[i]->getPath());
                    }
                }
                popup->list->notifyUpdateAllItems();
            });

            StaticCast<UI::Button>(popup->footer)->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                window->hide();
            });
        }
        window->setVisible(!window->getVisible());
        window->setFocus(*popup->searchField);
    });
}

/*void FileManager::loadTypes()
{
    //this->WorkspaceData.deserialize(AJSON::valueFromFile(APath::applicationDirectory() + "Types.json").toObject());
}

void FileManager::saveTypes()
{
    //AJSON::saveToFile(toJSONValue(this->WorkspaceData), APath::applicationDirectory() + "Types.json");
}*/

void FileManager::loadWorkspace()
{
    this->WorkspaceData.deserialize(AJSON::valueFromFile(APath::applicationDirectory() + "WorkspaceData.json").toObject());

    //HACK: see FileManager::closeFile, it rewrites OpenedFiles
    Array<Path> paths = this->WorkspaceData.OpenedFiles;

    //HACK: openPath adds WorkspaceData.OpenedFiles so we need to clear them...
    this->WorkspaceData.OpenedFiles.clear();
    for (const Path &p : paths)
    {
        openPath(p, false);
    }

    //HACK: see FileManager::closeFile, it rewrites OpenedFiles
    paths = this->WorkspaceData.OpenedEditors;
    for (const Path &p : paths)
    {
        openPath(p, true);
    }
}

void FileManager::saveWorkspace()
{
    AJSON::saveToFile(toJSONValue(this->WorkspaceData), APath::applicationDirectory() + "WorkspaceData.json");
}

void FileManager::registerEditor(const OneStudioPlatform::EditorData& editor)
{
    Editors.push_back(editor);
}

void FileManager::unregisterEditor(const String &identifier)
{

}

void FileManager::unregisterEditors(const String &extension)
{

}

void FileManager::unregisterEditors()
{
    Editors.clear();
}

const OneStudio::TypeData &FileManager::findTypeForPath(const Path &path) const
{
    for (const OneStudio::TypeData &type : Types)
    {
        if (ranges::find(type.Extensions, path.extension()) != type.Extensions.end())
        {
            return type;
        }
    }

    return Types[0];
}

SharedReference<OneStudioPlatform::EditorInstance> FileManager::findEditorForType(const OneStudio::TypeData &type) const
{
    for (const OneStudioPlatform::EditorData &editor : Editors)
    {
        if (editor.Identifier == type.AssociatedEditor)
        {
            return editor.Instance;
        }
    }

    return nullptr;
}

SharedReference<OneStudioPlatform::EditorInstance> FileManager::findEditorForPath(const Path &path) const
{
    return findEditorForType(findTypeForPath(path));
}

SharedReference<OSFileSystemItem> FileManager::findIndexedFile(const APath &path)
{
    auto it = std::find_if(IndexedFiles.begin(), IndexedFiles.end(), [&](auto &f) { return f->getPath() == path; });
    if (it == IndexedFiles.end())
    {
        return nullptr;
    }

    return *it;
}

const OneStudio::EditableFile *FileManager::findOpenedFile(const APath &path) const
{
    auto it = std::find_if(OpenedFiles.begin(), OpenedFiles.end(), [&](auto &f) { return f.FileInstance->getPath() == path; });
    if (it == OpenedFiles.end())
    {
        return nullptr;
    }

    return &*it;
}

const OneStudio::EditableFile *FileManager::findOpenedFile(const SharedReference<OSFileSystemItem> &file) const
{
    auto it = std::find_if(OpenedFiles.begin(), OpenedFiles.end(), [&](auto &f) { return f.FileInstance == file; });
    if (it == OpenedFiles.end())
    {
        return nullptr;
    }

    return &*it;
}

const OneStudio::EditableFile *FileManager::findOpenedFile(const EditableFile &file) const
{
    return findOpenedFile(file.FileInstance);
}

void FileManager::newFile()
{
    newFile("NewFile.txt");
}

void FileManager::newFile(const Path &path)
{
    AFile file;
    if (file.open(path, AFileOpenMode::WriteBinary))
    {
        file.close();
    }
    openFile(path);
}

void FileManager::openFile(const Path &path, bool openInEditor)
{
    if(!APathInfo(path).isExists())
    {
        return;
    }

    SharedReference<OSFileSystemItem> item = OneStudio::findOpenedFile(path, WindowManager::getThisInstance().outliner->items);

    if (!item)
    {
        item = CreateShared<OSFileSystemItem>();
        item->setText(path.name());
        item->setPath(path);

        ALogMessage("", "Load Directory: %s", path);
        this->WorkspaceData.OpenedFiles.push_back(path.toString());

        WindowManager::getThisInstance().outliner->items.push_back(item);
        WindowManager::getThisInstance().outliner->notifyUpdateAllItems();
    }

    if (openInEditor)
    {
        openFileInEditor(item);
    }
}

void FileManager::openFile(const OneStudio::EditableFile &file)
{
    if(!APathInfo(file.FileInstance->getPath()).isExists())
    {
        return;
    }
    ALogMessage("", "Open File: %s", file.FileInstance->getPath().toString());
    OpenedFiles.push_back(file);
    onFileOpened(file);

    //TODO: optimize
    this->WorkspaceData.OpenedEditors.clear();
    this->WorkspaceData.OpenedEditors.reserve(OpenedFiles.size());
    for (EditableFile &file : OpenedFiles)
    {
        this->WorkspaceData.OpenedEditors.push_back(file.FileInstance->getPath().toString());
    }
}

void FileManager::saveFile(const OneStudio::EditableFile &file)
{
    file.EditorInstance->saveFile(file.FileInstance);
    onFileSaved(file);
}

void FileManager::saveAllFiles()
{
    for (OneStudio::EditableFile &openedFile : getOpenedFiles())
    {
        saveFile(openedFile);
    }
}

void FileManager::reloadFile(const OneStudio::EditableFile &file)
{
    onFileClosed(file);
    onFileOpened(file);
}

void FileManager::closeFile(const OneStudio::EditableFile &file)
{
    auto it = std::find_if(OpenedFiles.begin(), OpenedFiles.end(), [&](auto &f) { return f.FileInstance == file.FileInstance; });
    if (it == OpenedFiles.end())
    {
        return;
    }

    onFileClosed(file);
    OpenedFiles.erase(it);
    file.EditorInstance->closeFile(file.FileInstance);

    //TODO: optimize
    this->WorkspaceData.OpenedEditors.clear();
    this->WorkspaceData.OpenedEditors.reserve(OpenedFiles.size());
    for (EditableFile &file : OpenedFiles)
    {
        this->WorkspaceData.OpenedEditors.push_back(file.FileInstance->getPath().toString());
    }
}

void FileManager::markFileDirty(const OneStudio::EditableFile &file)
{
    onFileChanged(file);
}

void FileManager::closeFiles()
{
    OpenedFiles.clear();
}

void FileManager::pushRecentFile(const Path &path)
{
    //ArrayUtils::Remove(this->WorkspaceData.RecentFiles, path);
    if (ArrayUtils::Contains(this->WorkspaceData.RecentFiles, path))
    {
        this->WorkspaceData.RecentFiles.erase(ranges::find(this->WorkspaceData.RecentFiles, path));
    }
    if (this->WorkspaceData.RecentFiles.size() > 4)
    {
        this->WorkspaceData.RecentFiles.resize(4);
    }
    this->WorkspaceData.RecentFiles.insert(this->WorkspaceData.RecentFiles.begin(), path);
}

Array<SharedReference<OSFileSystemItem>> FileManager::loadFileSystemEntries(const ADirectory &directory)
{
    Array<SharedReference<OSFileSystemItem>> fileSystemItems;
    for (auto &entry : directory)
    {
        if (entry == "" || entry == "." || entry == "..")
        {
            continue;
        }
        SharedReference<OSFileSystemItem> fileSystemItem = CreateShared<OSFileSystemItem>();
        fileSystemItem->setText(entry);
        //fileSystemItem->setImage(QFileIconProvider().icon(QFileInfo((directory.path() + entry).toString().toUtf8().data())));

        APathInfo pathInfo(directory.path() + entry);
        fileSystemItem->setPath(pathInfo.path());
        if (pathInfo.isDirectory())
        {
            fileSystemItem->setItems(loadFileSystemEntries(ADirectory(pathInfo)));
        }
        else if (pathInfo.isFile()) {
            //TODO
            /*QObject::connect(fileSystemItem.data(), &OSFileSystemItem::selected, [this, pathInfo](){

            });*/
        }
        loadFileSystemItem(fileSystemItem);
        fileSystemItems.push_back(fileSystemItem);
    }
    return fileSystemItems;
}

void FileManager::openPath(const Path &path, bool openInEditor)
{
    if (APathInfo(path).isDirectory())
    {
        openDirectory(path);
    }
    else
    {
        openFile(path, openInEditor);
    }
}

void FileManager::openDirectory(const APath &path)
{
    if(!APathInfo(path).isExists())
    {
        return;
    }
    
    SharedReference<OSFileSystemItem> item = OneStudio::findOpenedFile(path, WindowManager::getThisInstance().outliner->items);

    if (item)
    {
        return;
    }

    item = CreateShared<OSFileSystemItem>();
    item->setText(path.name());
    item->setPath(path);
    //projectEntryItem->setImage(QFileIconProvider().icon(QFileInfo((entryPathInfo.path()).toString().toUtf8().data())));
    item->setItems(loadFileSystemEntries(path));
    loadFileSystemItem(item);

    ALogMessage("", "Load Directory: %s", path);
    this->WorkspaceData.OpenedFiles.push_back(path.toString());

    WindowManager::getThisInstance().outliner->items.push_back(item);
    WindowManager::getThisInstance().outliner->notifyUpdateAllItems();
}

void FileManager::indexFileInEditor(const SharedReference<OSFileSystemItem> &item)
{
    if (std::find_if(IndexedFiles.begin(), IndexedFiles.end(), [&](auto &i) { return i->getPath() == item->getPath(); }) == IndexedFiles.end())
    {
        IndexedFiles.push_back(item);
    }

    if (SharedReference<OneStudioPlatform::EditorInstance> editor = findEditorForPath(item->getPath()))
    {
        editor->indexFile(item);
    }
}

void FileManager::openFileInEditor(const SharedReference<OSFileSystemItem> &item)
{
    auto openedFiles = getOpenedFiles();
    auto it = ranges::find_if(openedFiles, [&](const OneStudio::EditableFile &file) {
        return file.FileInstance == item;
    });

    if (it != openedFiles.end())
    {
        return;
    }

    if (SharedReference<OneStudioPlatform::EditorInstance> editor = findEditorForPath(item->getPath()))
    {
        editor->indexFile(item);
        auto editorView = editor->loadFile(item, String());
        if (!editorView)
        {
            auto label = CreateShared<UI::Label>();
            label->setText("Not Loaded");
            label->setTextAlign(Core::TextAlign::Center);
            editorView = label;
        }
        openFile(OneStudio::EditableFile{ item, editor, editorView });
    }

    if (APathInfo(item->getPath()).isFile())
    {
        pushRecentFile(item->getPath());
        saveWorkspace();
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
