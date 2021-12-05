#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"

//CLASSGEN END REGION
#include "ExtensionLibrary.gen.h"
#include "ApplicationManager.gen.h"

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DeveloperLibraryView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ListView::AdapterType
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DeveloperLibraryView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    DeveloperLibraryView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION

    SharedReference<UI::TextField> libraryPath = CreateShared<UI::TextField>();
    SharedReference<UI::ListView> packageList = CreateShared<UI::ListView>();

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        if (!libraryPath->getParent()) // HACK: This initialization should be in the constructor
        {
            libraryPath->setText(OneStudio::ApplicationManager::getThisInstance().getDeveloperLibrary().getLibraryPath());
            packageList->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
            packageList->setAdapter(this);

            addView(libraryPath);
            addView(packageList);

            setData({ {}, {} });
            setDirection(UI::Direction::Vertical);
        }

        packageList->notifyUpdateAllItems();
    }

    Array<SharedReference<UI::View>>::size_type getCountItems(const AObject &sender) const override { return ApplicationManager::getThisInstance().getDeveloperLibrary().getPackages().size(); }
    SharedReference<UI::View> provideViewForItem(const AObject &sender, Array<SharedReference<UI::View>>::size_type index) override
    {
        auto packages = ApplicationManager::getThisInstance().getDeveloperLibrary().getPackages(); //TODO: optimize
        const PackageInfo &package = packages[index];
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(package.PackagePath.name() + " (" + package.Version + ")");
        return v;
    }

    void onItemTapped(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index)
    {
        auto packages = ApplicationManager::getThisInstance().getDeveloperLibrary().getPackages(); //TODO: optimize
        const PackageInfo &package = packages[index];

        ALogMessage("", "execute: explorer /select,\"%s\"", package.PackagePath);
        //AProcess("explorer", { "/select,\"" + package.PackagePath.toString() + "\"" }).execute();
        system(String("explorer /select," + package.PackagePath.toString()).data()); //TODO: do not use system
    }

    /*virtual bool canAddItem() const
    {
        return true;
    }

    virtual bool requestAddItem()
    {
        ApplicationManager::getThisInstance().getDeveloperLibrary().data.append("New Item");
        return true;
    }

    virtual bool canRemoveItem(Array<SharedReference<UI::View>>::SizeType index) const
    {
        return ApplicationManager::getThisInstance().getDeveloperLibrary().data.size() > 0;
    }

    virtual bool requestRemoveItem(Array<SharedReference<UI::View>>::SizeType index)
    {
        ApplicationManager::getThisInstance().getDeveloperLibrary().data.erase(index);
        return true;
    }*/
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
