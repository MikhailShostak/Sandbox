#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "OneStudioPlatform"
#include "WorkspaceData.gen.h"
#include "Foundation"
#include "TypeData.gen.h"
#include "EditableFile.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class FileManager : public Core::ApplicationComponent2, public OneStudioPlatform::FileContext
//CLASSGEN END REGION
, public ApplicationComponent
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FileManager This;
    typedef Serializable Super;
    typedef std::tuple<ApplicationComponent, OneStudioPlatform::FileContext> Interfaces;
protected:
    OneStudio::WorkspaceData WorkspaceData;
Array<OneStudio::TypeData> Types;
Array<OneStudioPlatform::EditorData> Editors;
Array<OneStudio::EditableFile> OpenedFiles;
public:
    FileManager();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    OneStudio::WorkspaceData getWorkspaceData() const;
    void setWorkspaceData(OneStudio::WorkspaceData const &WorkspaceData);
    void setWorkspaceData(OneStudio::WorkspaceData &&WorkspaceData);
    Array<OneStudio::TypeData> getTypes() const;
    void setTypes(Array<OneStudio::TypeData> const &Types);
    void setTypes(Array<OneStudio::TypeData> &&Types);
    Array<OneStudioPlatform::EditorData> getEditors() const;
    void setEditors(Array<OneStudioPlatform::EditorData> const &Editors);
    void setEditors(Array<OneStudioPlatform::EditorData> &&Editors);
    Array<OneStudio::EditableFile> getOpenedFiles() const;
    void setOpenedFiles(Array<OneStudio::EditableFile> const &OpenedFiles);
    void setOpenedFiles(Array<OneStudio::EditableFile> &&OpenedFiles);
//CLASSGEN END REGION

    static FileManager &getThisInstance() { return getInstanceAs<FileManager>(); }

    void onLoad() override;
    void onApplicationStart(const AApplication &application) override;

    void loadWorkspace();
    void saveWorkspace();

    void registerEditor(const OneStudioPlatform::EditorData &editor) override;
    void unregisterEditor(const String &identifier);
    void unregisterEditors(const String &extension);
    void unregisterEditors();

    const OneStudio::TypeData &findTypeForPath(const Path &path) const;
    SharedReference<OneStudioPlatform::EditorInstance> findEditorForType(const OneStudio::TypeData &type) const;
    SharedReference<OneStudioPlatform::EditorInstance> findEditorForPath(const Path &path) const;

    SharedReference<OSFileSystemItem> findIndexedFile(const APath &path);
    const OneStudio::EditableFile *findOpenedFile(const APath &path) const;
    const OneStudio::EditableFile *findOpenedFile(const SharedReference<OSFileSystemItem> &file) const;
    const OneStudio::EditableFile *findOpenedFile(const EditableFile &file) const;

    void openPath(const Path &path, bool openInEditor = true);

    void newFile();
    void newFile(const Path &path);
    void openFile(const Path &path, bool openInEditor = true);

    void openDirectory(const APath &path);

    Array<SharedReference<OSFileSystemItem>> loadFileSystemEntries(const ADirectory &directory);

    void openFile(const OneStudio::EditableFile &file);
    void saveFile(const OneStudio::EditableFile &file);
    void saveAllFiles();
    void reloadFile(const OneStudio::EditableFile &file);
    void closeFile(const OneStudio::EditableFile &file);
    void markFileDirty(const OneStudio::EditableFile &file);

    void closeFiles();

    void pushRecentFile(const Path &path);

    ADelegate<void()> onTypesUpdated;
    ADelegate<void()> onEditorsUpdated;

    ADelegate<void(const OneStudio::EditableFile & file)> onFileOpened;
    ADelegate<void(const OneStudio::EditableFile & file)> onFileChanged;
    ADelegate<void(const OneStudio::EditableFile & file)> onFileSaved;
    ADelegate<void(const OneStudio::EditableFile & file)> onFileClosed;

    void registerFileTemplate(const String &group, const SharedReference<OneStudioPlatform::FileTemplate> &fileTemplate) override { }

    void addObserver(OSFileSystemObserver *const &observer) override {}
    void removeObserver(OSFileSystemObserver *const &observer) override {}

    SharedReference<OSFileSystemItem> findFileSystemItem(const String &name, const bool &recursively = true) override { return nullptr; }
    void insertFileSystemItem(const SharedReference<OSFileSystemItem> &item) override {}
    void removeFileSystemItem(const SharedReference<OSFileSystemItem> &item) override {}
    void loadFileSystemItem(const SharedReference<OSFileSystemItem> &item) override { indexFileInEditor(item); }
    void openFileSystenItem(const SharedReference<OSFileSystemItem> &item, const String &identifier) override {}

    void indexFileInEditor(const SharedReference<OSFileSystemItem> &item);
    void openFileInEditor(const SharedReference<OSFileSystemItem> &item);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
