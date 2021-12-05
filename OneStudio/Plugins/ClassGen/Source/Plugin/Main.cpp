#include "LanguageFunctions.h"
#include "System.pch.hpp"

#include "Main.h"

#include <ClassGenLibrary>

#include "Classes.h"

#include "ClassDataInstance.h"
//#include "ClassEditor.gen.h"
//#include "ScriptEditor.gen.h"
//#include "EnumerationEditor.gen.h"
//#include "ViewEditorView.gen.h"
//#include "TextureEditor.h"
//#include "MaterialEditor.h"
//#include "SceneEditor.h"
//#include "ApplicationFlowEditor.h"
#include "ExtensionEditor.gen.h"

//#include "FieldEditor.h"

#include "Includes/PropertyAttributes.gen.h"
#include "ClassRepository.h"
//#include "ClassSuggestionsComponent.h"
//#include "EmbeddedObjectFieldEditor.gen.h"

namespace Log
{

template<typename FormatType, typename ...Args>
inline String Format(FormatType &&format, Args &&...args)
{
	auto now = std::chrono::system_clock::now();
	return Str::Format("[{:%Y-%m-%d %H:%M:%S}.{}] {}\r\n", now, std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() % 1000, Str::Format(format, std::forward<Args>(args)...));

	/*std::cout << Str::Format("[{:%Y-%m-%d %H:%M:%S}.{}] {}\r\n",
		now,
		std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() % 1000,
		Str::Format(format, std::forward<Args>(args)...)
	);*/
}

}
namespace LegacyClassGen
{

/*class ViewEditorView : public Editor
{
public:
    void onCreate(const SharedReference<ClassInfo> &data) override
    {
        SharedReference<WidgetEditorView> v = view.as<WidgetEditorView>();
        dataInstance->view = v;
        v->setRootNode(v->Deserialize(dataInstance->json));
    }

    void save() override
    {
        dataInstance->json = dataInstance->view->Serialize(dataInstance->view->getRootNode());
    }
};*/

class TypeTreeItem
{
public:
    String title;
    bool expanded = false;

    Array<SharedReference<TypeTreeItem>> types;
};

thread_local void *CurrentExtension = nullptr;

class ClassGenEditor : public OSFileDataInstanceEditor<ClassDataInstance, UI::Overlay>, public UI::TreeAdapter<TypeTreeItem>, public LegacyClassGen::Context
{
    Array<SharedReference<AApplicationPlugin<LegacyClassGen::TypeExtension>>> extensions;
    UnorderedDictionary<size_t, MetaObject *> editors;

    UnorderedDictionary<void *, Array<MetaObject *>> registeredEditors;
    UnorderedDictionary<void *, Array<MetaObject *>> registeredTypes;
    //AFactoryMap<size_t, Editor> editors;

    SharedReference<UI::Window> classOutlinerWindow;
    Array<SharedReference<TypeTreeItem>> types;
public:

    AFactoryMap<String, FieldEditor> fieldEditorsForTypes;
    AFactoryMap<String, FieldEditor> fieldEditorsForInstances;

    UnorderedDictionary<String, APair<void *, MetaObject *>> dfieldEditorsForTypes;
    UnorderedDictionary<String, APair<void *, MetaObject *>> dfieldEditorsForInstances;

    static ClassGenEditor &getThisInstance() { return getInstanceAs<ClassGenEditor>(); }

    Array<APair<String, Path>> outdatedFiles;
    Array<APair<String, Path>> unloadedFiles;

    void registerType(MetaObject &type, const String &name, CGTypeGroup group) override
    {
        if (!CurrentExtension)
        {
            return;
        }

        Log::Print("registerType()");

        ClassManager::getInstance().registerType(type, name, group);

        registeredTypes[CurrentExtension].push_back(&type);
    }

    void registerEditor(MetaObject &editor, MetaObject &type) override
    {
        if (!CurrentExtension)
        {
            return;
        }

        Log::Print("registerEditor()");

        editors[type.hash] = &editor;

        registeredEditors[CurrentExtension].push_back(&editor);
    }

    void registerFieldEditorForTypes(class MetaObject &editor, const String &name) override
    {
        dfieldEditorsForTypes.insert({ name, { CurrentExtension, &editor } });
    }

    void registerFieldEditorForInstances(class MetaObject &editor, const String &name) override
    {
        dfieldEditorsForInstances.insert({ name, { CurrentExtension, &editor } });
    }

    void registerPropertyTypeEditor(class MetaObject &editor, const String &name) override
    {
        dfieldEditorsForTypes.insert({ name, { CurrentExtension, &editor } });
    }

    void registerPropertyInstanceEditor(class MetaObject &editor, const String &name) override
    {
        dfieldEditorsForInstances.insert({ name, { CurrentExtension, &editor } });
    }

    SharedReference<FieldEditor> createFieldEditor(const UnorderedDictionary<String, APair<void *, MetaObject *>> &fieldEditors, const String &name)
    {
        MetaObject *editorMetaObject = fieldEditors.at(name).second;
        SharedReference<FieldEditor> editor = SharedReference<FieldEditor>(DynamicCast<FieldEditor>(editorMetaObject->constructor()));
        return editor;
    }

    SharedReference<FieldEditor> createFieldEditorForType(const String &name)
    {
        SharedReference<FieldEditor> f = createFieldEditor(dfieldEditorsForTypes, name);
        if(f)
        {
            return f;
        }
        return fieldEditorsForTypes.createShared(name);
    }

    SharedReference<FieldEditor> createFieldEditorForInstance(const String &name)
    {
        SharedReference<FieldEditor> f = createFieldEditor(dfieldEditorsForInstances, name);
        if(f)
        {
            return f;
        }
        return fieldEditorsForInstances.createShared(name);
    }

    //extern AFactoryMap<String, FieldEditor> fieldEditorsForTypes;
    //extern AFactoryMap<String, FieldEditor> fieldEditorsForInstances;

    bool canCreateEditorForType(const String &name) override { return dfieldEditorsForTypes.find(name) != dfieldEditorsForTypes.end(); }
    bool canCreateEditorForInstance(const String &name) override { return dfieldEditorsForInstances.find(name) != dfieldEditorsForInstances.end(); }

    SharedReference<FieldEditor> createFieldEditor(const LegacyClassGen::TypeInfo &typeInfo, const SharedReference<LegacyClassGen::BaseCGType> &type) override
    {
        SharedReference<FieldEditor> propertyEditor;

        SharedReference<LegacyClassGen::BaseCGType> t = type;
        //TODO: optimize
        if (canCreateEditorForInstance(typeInfo.Name))
        {
            propertyEditor = createFieldEditorForInstance(typeInfo.Name);
        }
        else
        {
            if (!type)
            {
                auto it = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeInfo.Name);
                if (it != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
                {
                    t = it->second;
                }
            }
            if (t)
            {
                String typeType;
                t->data.read("Type", typeType);
                if (canCreateEditorForType(typeType))
                {
                    propertyEditor = createFieldEditorForType(typeType);
                }
            }
        }

        if (propertyEditor == nullptr)
        {
            //Unimplemented placeholder
            propertyEditor = createFieldEditorForType("Class");
        }

        propertyEditor->setType(t, typeInfo);
        return propertyEditor;
    }

    APair<SharedReference<FieldEditor>, SharedReference<UI::View>> createFieldEditorAndView(const String &title, const LegacyClassGen::TypeInfo &typeInfo, const SharedReference<LegacyClassGen::BaseCGType> &type) override
    {
        SharedReference<UI::FlexBox> container = CreateShared<UI::FlexBox>();
        auto label = CreateShared<UI::DefaultIconItemView>();
        label->icon->setImage(::CloseButtonSmall);
        label->setText(title);
        label->setName(title + "_" + (type ? type->getDefaultType(true) : typeInfo.Name) + "_LabelView");
        label->icon->setExpanded(false);
        container->addView(label);

        SharedReference<FieldEditor> propertyEditor = createFieldEditor(typeInfo, type);
        auto propertyEditorPtr = propertyEditor.get();
        auto labelPtr = label.get();
        propertyEditor->onValueUpdated = [labelPtr, propertyEditorPtr]() {
            labelPtr->icon->setExpanded(propertyEditorPtr->isChanged);
        };

        label->icon->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
        label->icon->eventChannel.registerDelegate([propertyEditorPtr](UI::TapGestureEvent &event) {
            propertyEditorPtr->notifyValueReset();
        });

        SharedReference<UI::View> propertyView = DynamicCast<UI::View>(propertyEditor);
        propertyView->setName(title + "_" + (type ? type->getDefaultType(true) : typeInfo.Name) + "_ValueView");
        container->addView(propertyView);

        container->setData({ {}, {} });

        return { propertyEditor, container };
    }

    void loadExtension(OneStudioPlatform::Task &task, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr)
    {
//        task.Log(Log::Format("Setup toolchain"));
//         return;
//         Array<APair<std::string, AJSONObject>> settings_list = {
//             //{ "{DeveloperSettings}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/ClangToolchain.json").toObject()},
//             { "{Toolchain}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/Toolchain.json").toObject() },
//             { "{ToolchainSettings}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/ClangToolchain.json").toObject() },
//             { "{WindowsSettings}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/Platforms/WindowsToolchain.json").toObject() },
//             { "{ProjectSettigns}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/ClangToolchain-project.json").toObject() },
//             { "{ClassGenSettigns}", AJSON::valueFromFile("C:/Users/mikhail.shostak/Developer/Toolchains/ClangToolchain-classgen.json").toObject() },
//         };
// 
//         AJSONObject d = merge_data_nodes_recursively(settings_list | rngv::values | rngv::reverse);
// 
//         CppToolchainOperation toolchain;
//         toolchain.Settings = deserialize<BuildSystem::BuildingSettings>(d);
//         toolchain.SourceEntries = {
//             type->path.directory().toString()
//         };
//         toolchain.BuildDirectory = type->path.directory().toString() + "/__cache__";
//         toolchain.ProductDirectory = type->path.directory().toString() + "/__cache__";
//         toolchain.ProductName = type->path.baseName();
//         toolchain.FrameworkDirectory = "D:/Projects/Toolchain/Frameworks";
//         if(!toolchain.Settings.LinkageSettings.Frameworks.empty())
//         {
//             toolchain.Settings.LinkageSettings.Frameworks.append(";");
//         }
//         toolchain.Settings.LinkageSettings.Frameworks.append("ClassGenLibrary");
// 
//         /*String pdb = type->path.directory().toString() + "\\__cache__\\" + (type->path.baseName() + ".pdb");
//         String str = getNextName(type->path.baseName(), [&](const auto &v) {
//             return !APathInfo(type->path.directory().toString() + "\\__cache__\\" + (v + ".pdb")).isExists();
//         });
//         str = type->path.directory().toString() + "\\__cache__\\" + (str + ".pdb");
//         MoveFileW(LPCWSTR(pdb.data()), LPCWSTR(str.data()));
//         MoveFileExW(LPCWSTR(str.data()), NULL, MOVEFILE_DELAY_UNTIL_REBOOT);*/
// 
//         Array<String> dependencies;
//         if (type->data.read("Dependencies", dependencies))
//         {
//             std::string ext_dir = "C:/Users/mikhail.shostak/Developer/Library/ClassGenExtensions/";
//             for (const auto &dep : dependencies)
//             {
//                 std::string dep_dir = ext_dir + dep;
//                 const auto &directories = ADirectory(dep_dir.data()).findRecursively(String(), AFindFilter::AllDirectories);
//                 for (const auto &subdir : directories)
//                 {
//                     toolchain.Settings.CompilerSettings.Compiler += " -I" + subdir.path().toString();
//                 }
//                 toolchain.Settings.CompilerSettings.Compiler += " -I" + dep_dir;
//                 toolchain.SourceEntries.push_back(dep_dir);
//             }
//         }
// 
//         toolchain.Settings.CompilerSettings.Compiler += " -working-directory " + type->path.directory().toString() + "/__cache__";
//         toolchain.Settings.LinkerSettings.Linker += " -working-directory " + type->path.directory().toString() + "/__cache__";

        //co_await OneStudioPlatform::TaskContext::getInstance().getMainWorker().schedule();
        System::Path libraryPath = System::Path("D:/Projects/CMake/Sandbox/.build/Debug-x86_64/bin/LegacyExtensions/ClassGenExtensions") / (type->path.baseName() + ".dll");
        // toolchain.GetDynamicLibraryOutputFile().string();

        task.Log(Log::Format("Unload"));
        auto output = APath(String(libraryPath.string()));
        auto it = ranges::find_if(extensions, [&](const auto &v) { return v->getPath() == APath(output); });
        if (it != extensions.end())
        {
            task.Log(Log::Format("{} already loaded!", output));
            
            void *ptr = it->get();
            auto &re = registeredEditors[ptr];
            for (const auto &e : re)
            {
                auto i = rng::find_if(editors, [&](const auto &v) { return v.second == e; });
                if (i != editors.end())
                {
                    editors.erase(i);
                }
            }
            registeredEditors.erase(ptr);

            auto &rt = registeredTypes[ptr];
            for (const auto &t : rt)
            {
                ClassManager::getInstance().unregisterType(*t);
            }
            registeredTypes.erase(ptr);

            //it->getInstance()->unload();
            (*it)->unload();
            extensions.erase(it);
        }
        
        task.Log(Log::Format("Compile"));
        //co_await OneStudioPlatform::TaskContext::getInstance().getMainWorker().schedule();
        //co_await toolchain.CreateDynamicLibrary();
        //cppcoro::sync_wait(toolchain.CreateDynamicLibrary());
        task.Log(Log::Format("Archive"));
        //cppcoro::sync_wait(toolchain.Archive());
        task.Log(Log::Format("Load"));

        SharedReference<AApplicationPlugin<LegacyClassGen::TypeExtension>> e = CreateShared<AApplicationPlugin<LegacyClassGen::TypeExtension>>();
        e->setPath(libraryPath.string());
        if (e->load())
        {
            //co_await OneStudioPlatform::TaskContext::getInstance().getMainWorker().schedule();
            task.Log(Log::Format("Initialize"));
            CurrentExtension = e.get();
            e->getInstance()->load();
            CurrentExtension = nullptr;
            extensions.push_back(e);
            task.Log(Log::Format("Reload files unloaded files"));
            //co_await OneStudioPlatform::TaskContext::getInstance().getMainWorker().schedule();
            for (const APair<String, Path> &f : unloadedFiles)
            {
                LegacyClassGen::ClassManager::getInstance().load(f.second, f.first);
            }
            unloadedFiles.clear();
            task.Log(Log::Format("Finished"));
        }
        else
        {
            task.Log(Log::Format("Failed"));
        }
        //co_return;
        //Console::getInstance().applyCommand("LoadExtension " + type->path.directory().toString() + "/" + (toolchain.ProductName + ".dll"));
    }

    SharedReference<UI::TreeView<TypeTreeItem>> classOutlinerView;

    /*virtual SizeType getCountRootItems() const = 0;
    virtual TreeItemType *getRootItem(SizeType index) = 0;
    //virtual bool hasContent(TreeItemType *parentItem) const = 0;
    //virtual void loadContent(TreeItemType *parentItem) {}
    virtual SizeType getCountChildItems(TreeItemType *parentItem) const = 0;
    virtual TreeItemType *getChildItem(TreeItemType *parentItem, SizeType index) = 0;
    virtual SharedReference<View> provideViewForItem(const AObject &sender, SizeType depth, TreeItemType *item) = 0;*/

    //UI::SizeType getCountItems(const AObject &sender) const override { return types.size(); }
    //SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override { return Create<UI::Label>(types[index]); }

    virtual UI::SizeType getCountRootItems() const { return types.size(); }
    virtual TypeTreeItem *getRootItem(UI::SizeType index) { return types[index].get(); }
    virtual UI::SizeType getCountChildItems(TypeTreeItem *parentItem) const { return parentItem->expanded ? parentItem->types.size() : 0; }
    virtual TypeTreeItem *getChildItem(TypeTreeItem *parentItem, UI::SizeType index) { return parentItem->types[index].get(); }
    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType depth, TypeTreeItem *item)
    {
        UI::DefaultExpandableItemView *treeItem = Create<UI::DefaultExpandableItemView>();
        treeItem->applyParameters(depth, item->title, item->types.size() > 0);
        treeItem->expandButton->eventChannel.registerDelegate([this, item, treeItem](UI::TapGestureEvent &event) {
            treeItem->setItemExpanded(item->expanded = !item->expanded);
            classOutlinerView->notifyUpdateChildren(item);
        });
        return SharedReference<UI::View>(treeItem);
    }

    void registerStaticTypes();

    ClassGenEditor()
    {
        RegisterMetaClasses2();

        SharedReference<TypeTreeItem> libraryItem = CreateShared<TypeTreeItem>();
        libraryItem->title = "Library";
        types.push_back(libraryItem);

        SharedReference<TypeTreeItem> localItem = CreateShared<TypeTreeItem>();
        localItem->title = "Local";
        types.push_back(localItem);

        SharedReference<TypeTreeItem> localRootItem = CreateShared<TypeTreeItem>();
        localRootItem->title = ".";
        localItem->types.push_back(localRootItem);

        classOutlinerView = CreateShared<UI::TreeView<TypeTreeItem>>();
        classOutlinerView->setProxyAdapter(this);

        registerStaticTypes();

        ClassManager::getInstance().typeLoaded = [&](const SharedReference<BaseCGType> &type) {
            Array<String> segments = Str::Split(type->getDefaultType(), ".");
            
            SharedReference<TypeTreeItem> item = CreateShared<TypeTreeItem>();
            item->title = segments[0];

            Array<SharedReference<TypeTreeItem>> &types = [&]() -> Array<SharedReference<TypeTreeItem>> & {
                if (!type->package.empty())
                {
                    auto &libraryTypes = this->types[0]->types;
                    auto it = std::find_if(libraryTypes.begin(), libraryTypes.end(), [&](auto &i) {
                        return i->title == type->package;
                    });

                    if (it != libraryTypes.end())
                    {
                        return (*it)->types;
                    }
                    else
                    {
                        SharedReference<TypeTreeItem> libraryItem = CreateShared<TypeTreeItem>();
                        libraryItem->title = type->package;
                        libraryTypes.push_back(libraryItem);

                        SharedReference<TypeTreeItem> libraryRootItem = CreateShared<TypeTreeItem>();
                        libraryRootItem->title = ".";
                        libraryItem->types.push_back(libraryRootItem);
                        classOutlinerView->notifyUpdateChildren(this->types[0].get());

                        return libraryItem->types;
                    }
                }
                else
                {
                    return this->types[1]->types;
                }
            }();

            if (segments.size() == 1)
            {
                types[0]->types.push_back(item);
                classOutlinerView->notifyUpdateChildren(types[0].get());
            }
            else
            {
                SharedReference<TypeTreeItem> child = CreateShared<TypeTreeItem>();
                segments.erase(segments.begin());
                child->title = Str::Join(segments, ".");

                auto it = ranges::find_if(types, [&](auto &i) {
                    return i->title == item->title;
                });

                if (it != types.end())
                {
                    (*it)->types.push_back(child);
                    classOutlinerView->notifyUpdateChildren(it->get());
                }
                else
                {
                    item->types.push_back(child);
                    types.push_back(item);
                    classOutlinerView->notifyUpdateAllItems();
                }
            }
        };
		ClassManager::getInstance().typeUnloaded = [&](const SharedReference<BaseCGType> &type) {
            outdateFile(type);
        };
    }

public:

    void outdateFile(const SharedReference<BaseCGType> &type)
    {
        auto &data = ClassRepository::getInstance().indexedTypes;
        auto it = rng::find_if(data, [&](auto &v) { return v.second->type == type; });
        if (it != data.end())
        {
            outdatedFiles.push_back({ type->package, type->path });
            data.erase(it);
        }
        unloadedFiles.push_back({ type->package, type->path });
    }

    void indexFile(const Path &path)
    {
        /*auto it = rng::find_if(ClassRepository::getInstance().indexedTypes, [&](const auto &v) { return v == item->; });
        if (it != ClassRepository::getInstance().indexedTypes.end())
        {
            Log::Print("Reindex!");
        }*/

        SharedReference<ClassDataInstance> instance = CreateShared<ClassDataInstance>();
        instance->setPath(path);
        if (!instance->load())
        {
            return;
        }

        String namespaceName;
        instance->type->data.read("Namespace", namespaceName);
        String name = instance->path.baseName();
        String fullName = !namespaceName.empty() ? namespaceName + "." + name : name;
        ClassRepository::getInstance().indexedTypes[fullName] = instance;
        ALogMessage("ClassGen", "[ClassGen] File indexed: %s", fullName);

        String type;
        instance->type->data.read("Type", type);
        if (type == "Extension")
        {
            WeakReference<LegacyClassGen::BaseCGType> t = instance->type;
            auto task = OneStudioPlatform::TaskContext::getInstance().startTask();
            task->setTitle("Load Extension: " + instance->type->path.baseName());
            /*task->setAction([this, t](OneStudioPlatform::Task &task)->async_void{
                co_await OneStudioPlatform::TaskContext::getInstance().getMainWorker().schedule();
                co_await loadExtension(task, t);
                co_return;
            });*/
            loadExtension(*task, t.lock());
            task->start();
        }
    }

    void indexFile(const SharedReference<OSFileSystemItem> &item) override
    {
        indexFile(item->getPath());
    }

    void onCreate(const SharedReference<ClassDataInstance> &instance, const SharedReference<OSFileSystemItem> &item) override
    {

    }

    void onLoad(const SharedReference<ClassDataInstance> &instance, const SharedReference<OSFileSystemItem> &item, const SharedReference<UI::View> &view, const String &identifier) override
    {
        SharedReference<UI::Overlay> overlay = StaticCast<UI::Overlay>(view);

        MetaObject *editorMetaObject = editors.at(AMeta::getDynamicTypeHash(*instance->type.get()));
        SharedReference<Editor> editor = SharedReference<Editor>(DynamicCast<Editor>(editorMetaObject->constructor()));
        //SharedReference<Editor> editor = editors.createShared(AMeta::getDynamicTypeHash(*instance->type.data()));

        SharedReference<BaseCGType> t = instance->type;
        SharedReference<UI::TextButton> generateButton = CreateShared<UI::TextButton>();
        generateButton->setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        generateButton->setVerticalSizePolicy(UI::SizePolicy::Fixed);
        generateButton->setSize({ 100, 20 });
        generateButton->setText("Generate");
        generateButton->eventChannel.registerDelegate([t](UI::TapGestureEvent &event) {
            t->generate();
        });
        overlay->addView(generateButton);

        SharedReference<UI::View> editorView = DynamicCast<UI::View>(editor);
        //editorView->constructHierarchy();
        editorView->setSizePolicy(UI::SizePolicy::Expanded);
        overlay->setSizePolicy(UI::SizePolicy::Expanded);
        overlay->addView(editorView);
        overlay->setData({
            { {}, Core::Alignment::Center, Core::Alignment::Start, },
            { { 20 }, },
        });

        APath itemPath = item->getPath();
        editor->onChanged = [itemPath]() {
            Console::getInstance().applyCommand(fmt::format("MarkDirty {}", itemPath));
            ALogMessage("ClassGen", "[ClassGen] File changed %s", itemPath);
        };
        instance->bind(editor);
    }

    void onSave(const SharedReference<ClassDataInstance> &instance, const SharedReference<OSFileSystemItem> &item) override
    {

    }
};

}

namespace LegacyClassGen
{

void ClassGenEditor::registerStaticTypes()
{
    auto &mom = MetaObjectManager::getInstance();
    editors = {
        { AMeta::getStaticTypeHash<ExtensionCGType>(), mom.findMetaObject("ClassGen.ExtensionEditor") },
        //{ AMeta::getStaticTypeHash<ApplicationFlowCGType>(), mom.findMetaObject("UI.ApplicationFlowEditor") },
            //{ AMeta::getStaticTypeHash<ClassCGType>(), mom.findMetaObject("ClassGen.ClassEditor") },
        //{ AMeta::getStaticTypeHash<ScriptCGType>(), mom.findMetaObject("ClassGen.ScriptEditor") },
            //{ AMeta::getStaticTypeHash<ViewCGType>(), mom.findMetaObject("ClassGen.ViewEditorView") },
        //{ AMeta::getStaticTypeHash<MaterialCGType>(), mom.findMetaObject("UI.MaterialEditor") },
        { AMeta::getStaticTypeHash<SceneCGType>(), mom.findMetaObject("UI.SceneEditor") },
            //{ AMeta::getStaticTypeHash<EnumerationCGType>(), mom.findMetaObject("ClassGen.EnumerationEditor") },
            //{ AMeta::getStaticTypeHash<FlagsCGType>(), mom.findMetaObject("ClassGen.EnumerationEditor") },
            //{ AMeta::getStaticTypeHash<TextureCGType>(), mom.findMetaObject("UI.TextureEditor") },
    };
    //MetaObjectManager::getInstance().findMetaObject("");
}

}

void CGPrivatePlugin::load(const Map<String, OSPluginContext *> &dependentPlugins)
{
    //TODO: move to Static Run and link with GraphicsObjects
    glewExperimental = true;
    GLenum glewCompletionCode = glewInit();
    if (glewCompletionCode != GLEW_OK)
    {
        std::cout << glewGetErrorString(glewCompletionCode) << "\n";
        return;
    }
    Legacy::Graphics::API::glCheckErrors(true);

    SharedReference<LegacyClassGen::ClassGenEditor> editor = CreateShared<LegacyClassGen::ClassGenEditor>();
    const Path &libraryDirectory = OneStudioPlatform::ApplicationContext::getInstance().getLibraryDirectory();
    ADirectory libraryDirectoryHandle(libraryDirectory);
    for (const auto &e : std::filesystem::directory_iterator{ libraryDirectory.toString() })
    {
        const String &entry = e.path().string();
        ALogMessage("ClassGen", "[ClassGen] Index Library: \"%s\"", entry);
        const APathInfo &pathInfo = libraryDirectory + entry;
        //const String &package = entry;
        if (!pathInfo.isExists())
        {
            continue;
            //return AError(-1, fmt::format("Path doesn't exist: {}", pathInfo.path()));
        }

        if (pathInfo.isDirectory())
        {
            const auto &files = ADirectory(pathInfo).findRecursively("cg", AFindFilter::AllFiles);
            for (const auto &f : files)
            {
                AJSONValue v = AJSON::valueFromFile(f.path());
                if (v.isObject())
                {
                    String type;
                    v.asObject().read("Type", type);
                    if (type == "Extension")
                    {
                        editor->indexFile(f.path());
                    }
                }
            }
            //if (AError error = importFiles(files, package))
            //{
            //    return error;
            //}
        }
        else
        {
            //if (!load(pathInfo.path(), package))
            //{
            //    return AError(-1, fmt::format("Failed to load file: {}", pathInfo.path()));
            //}
        }
    }
    for (const auto &e : std::filesystem::directory_iterator{ libraryDirectory.toString() })
    {
        const String &entry = e.path().string();
        ALogMessage("ClassGen", "[ClassGen] Import Library: \"%s\"", entry);
        LegacyClassGen::ClassManager::getInstance().importPath(libraryDirectory + entry, entry);
    }

    OneStudioPlatform::ApplicationContext::getInstance().registerWindow("Classes", editor->classOutlinerView);
    OneStudioPlatform::FileContext::getInstance().registerEditor({ "ClassEditor", { "application/vnd.one-studio.class" }, editor });
    //OneStudioPlatform::ApplicationContext::getInstance().registerEditor("UIEditor", Create<UI::WidgetEditor>(), { "application/vnd.one-studio.ui" });
}

AApplicationPluginImplementation(OSPlugin, CGPrivatePlugin, 1, "1.0.0", "com.InsaneTeam.OneStudio.ClassGen")
