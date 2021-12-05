#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"
#include "Foundation"

#include "Foundation"
#include "ExperimentalDebug"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class RecentFilesView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef RecentFilesView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
protected:
    Text Title;
public:
    RecentFilesView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Text getTitle() const;
    void setTitle(Text const &Title);
    void setTitle(Text &&Title);
    SharedReference<UI::GroupPanel> pinnedFilesPanel;
    SharedReference<UI::GroupPanel> recentFilesPanel;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event) override
    {
        Super::onLoad(event);
        pinnedFilesPanel->headerLabel->setText("Pinned Files");
        recentFilesPanel->headerLabel->setText("Recent Files");
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
