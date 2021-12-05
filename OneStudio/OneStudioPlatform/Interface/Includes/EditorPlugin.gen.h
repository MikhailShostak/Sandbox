#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION

#include "Includes/ApplicationContext.gen.h"
#include "Includes/FileContext.gen.h"
#include "Includes/FileSystemItem.gen.h"
#include "Includes/OSPlugin.gen.h"

template<typename EditorType>
class OSTemplateEditorPlugin : public OSPlugin
{

    SharedReference<EditorType> editor;

public:

    using This = OSTemplateEditorPlugin<EditorType>;
    using Super = OSPlugin;

    SharedReference<EditorType> getEditor() const
    {
        return editor;
    }

    void load(const Map<String, OSPluginContext *> &dependentPlugins) override
    {
        Super::load(dependentPlugins);
        editor = CreateShared<EditorType>();
        OneStudioPlatform::FileContext::getInstance().registerEditor({getIdentifier(), getSupportedTypes(), getEditor()});
    }

    void unload() override
    {
        editor = nullptr;
    }

    virtual String getIdentifier() const = 0;
    virtual Array<String> getSupportedTypes() const = 0;

    virtual SharedReference<OSFileSystemItem> getFileSystemEntryForFile(const APath &path) const
    {
        auto *item = Create<OSFileSystemItem>();
        item->setText(path.name());
        item->setPath(path);
        return item;
    }

};

//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
