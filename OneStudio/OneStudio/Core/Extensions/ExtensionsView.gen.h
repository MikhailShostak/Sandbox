#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"

//CLASSGEN END REGION
#include "ApplicationManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ExtensionsView : public UI::ListView
//CLASSGEN END REGION
, public UI::ListView::AdapterType
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ExtensionsView This;
    typedef UI::ListView Super;
    typedef void Interfaces;
public:
    ExtensionsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::ListView> extensionsList = CreateShared<UI::ListView>();

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        setAdapter(this); // HACK: This initialization should be in the constructor
        //notifyUpdateAllItems();
    }

    Array<SharedReference<UI::View>>::size_type getCountItems(const AObject &sender) const override { return ApplicationManager::getThisInstance().getDeveloperLibrary().pluginLibrary.getPlugins().size(); }
    SharedReference<UI::View> provideViewForItem(const AObject &sender, Array<SharedReference<UI::View>>::size_type index) override
    {
        auto extensions = ApplicationManager::getThisInstance().getDeveloperLibrary().pluginLibrary.getPlugins(); //TODO: optimize
        const SharedReference<AApplicationPlugin<OSPlugin>> &extension = extensions[index];
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(fmt::format("{} {} ({})", extension->getPackage(), extension->getVersionName(), extension->getVersionCode()));
        return v;
    }

    void onItemTapped(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index)
    {
        auto extensions = ApplicationManager::getThisInstance().getDeveloperLibrary().pluginLibrary.getPlugins(); //TODO: optimize
        const SharedReference<AApplicationPlugin<OSPlugin>> &extension = extensions[index];

        ALogMessage("", "execute: explorer.exe /select,%s", extension->getPath());
        //AProcess("explorer.exe", { "/select,", extension->getPath().toString() }).execute();
        system(String("explorer /select," + extension->getPath().toString()).data()); //TODO: do not use system
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
