//CLASSGEN GENERATED REGION: Includes
#include "RecentFilesView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ExperimentalDebug"
#include "MathClasses"
#include "Math"

//CLASSGEN END REGION
#include "FileManager.gen.h"
#include <Experimental>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
RecentFilesView::RecentFilesView()
{
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    UI::FlexBoxData item_2_2;
    UI::FlexBoxData item_3_3;
    (*this).setData({item_0_0,item_1_1,item_2_2,item_3_3,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(4.000000);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void RecentFilesView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Title", toJSONValue(Title));
}
void RecentFilesView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Text RecentFilesView::getTitle() const
{
    return this->Title;
}
void RecentFilesView::setTitle(Text const &Title)
{
    this->Title = Title;
}
void RecentFilesView::setTitle(Text &&Title)
{
    this->Title = std::move(Title);
}
void RecentFilesView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("RecentFilesView");
    pinnedFilesPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
    {
        SharedReference<UI::ListView> pinnedFilesList = CreateShared<UI::ListView>([this](UI::ListView *v)
        {
        }
);
        (*pinnedFilesList).setName("PinnedFilesList");
        {
            (*pinnedFilesList).CountItems = [this]()            {
                return FileManager::getThisInstance().getWorkspaceData().PinnedFiles.size();
            };
;
            (*pinnedFilesList).Item = [this](SizeInteger const& Index) -> SharedReference<UI::View>             {
                auto instance = CreateShared<UI::DefaultTextItemView>();
                instance->setText(FileManager::getThisInstance().getWorkspaceData().PinnedFiles[Index]);
                return instance;
            };
;
            (*pinnedFilesList).OnItemTapped = [this](UI::TapGestureEvent const& Event, SizeInteger const& Index)            {
                return FileManager::getThisInstance().openFile(FileManager::getThisInstance().getWorkspaceData().PinnedFiles[Index]);
            };
;
        }
        (*pinnedFilesList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
        (*v).body = pinnedFilesList;
    }
);
    (*pinnedFilesPanel).setName("PinnedFilesPanel");
    {
    }
    (*this).addView(pinnedFilesPanel);
    recentFilesPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
    {
        SharedReference<UI::ListView> recentFilesList = CreateShared<UI::ListView>([this](UI::ListView *v)
        {
        }
);
        (*recentFilesList).setName("RecentFilesList");
        {
            (*recentFilesList).CountItems = [this]()            {
                return FileManager::getThisInstance().getWorkspaceData().RecentFiles.size();
            };
;
            (*recentFilesList).Item = [this](SizeInteger const& Index) -> SharedReference<UI::View>             {
                auto instance = CreateShared<UI::DefaultTextItemView>();
                instance->setText(FileManager::getThisInstance().getWorkspaceData().RecentFiles[Index]);
                return instance;
            };
;
            (*recentFilesList).OnItemTapped = [this](UI::TapGestureEvent const& Event, SizeInteger const& Index)            {
                return FileManager::getThisInstance().openFile(FileManager::getThisInstance().getWorkspaceData().RecentFiles[Index]);
            };
;
        }
        (*recentFilesList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
        (*v).body = recentFilesList;
    }
);
    (*recentFilesPanel).setName("RecentFilesPanel");
    {
    }
    (*this).addView(recentFilesPanel);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
