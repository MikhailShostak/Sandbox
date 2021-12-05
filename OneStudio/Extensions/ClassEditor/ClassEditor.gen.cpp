//CLASSGEN GENERATED REGION: Includes
#include "ClassEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ClassGenExtensions"
#include "MathClasses"
#include "ExperimentalDebug"
#include "Math"
#include "ClassGenLibraryDebug"

//CLASSGEN END REGION
// 
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ClassEditor::ClassEditor()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_28_0;
    UI::FlexBoxData item_29_1;
    (*this).setData({item_28_0,item_29_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ClassEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ClassEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ClassEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ClassEditor");
    logicEditor = CreateShared<LegacyClassGen::LogicEditor>([this](LegacyClassGen::LogicEditor *v)
    {
    }
);
    (*logicEditor).setName("LogicEditor");
    {
    }
    (*logicEditor).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*this).addView(logicEditor);
    SharedReference<UI::ScrollView> scrollView = CreateShared<UI::ScrollView>([this](UI::ScrollView *v)
    {
        contentView = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
        {
        }
);
        (*contentView).setName("ContentView");
        {
        }
        (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*contentView).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
        UI::FlexBoxData item_20_0;
        UI::FlexBoxData item_21_1;
        UI::FlexBoxData item_22_2;
        UI::FlexBoxData item_23_3;
        UI::FlexBoxData item_24_4;
        (*contentView).setData({item_20_0,item_21_1,item_22_2,item_23_3,item_24_4,});
        (*contentView).setDirection(UI::Direction::Vertical);
        (*contentView).setSpacing(8.000000);
        classDetailsPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
        {
            classDetails = CreateShared<UI::GroupView>([this](UI::GroupView *v)
            {
            }
);
            (*classDetails).setName("ClassDetails");
            {
            }
            (*classDetails).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
            (*classDetails).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
            (*v).body = classDetails;
        }
);
        (*classDetailsPanel).setName("ClassDetailsPanel");
        {
        }
        (*contentView).addView(classDetailsPanel);
        detailsPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
        {
            details = CreateShared<UI::PageView>([this](UI::PageView *v)
            {
            }
);
            (*details).setName("Details");
            {
            }
            (*details).setAffectsParentLayout(true);
            UI::OverlayData item_25_0;
            UI::OverlayData item_26_1;
            UI::OverlayData item_27_2;
            (*details).setData({item_25_0,item_26_1,item_27_2,});
            propertyDetails = CreateShared<LegacyClassGen::PropertyDetailsView>([this](LegacyClassGen::PropertyDetailsView *v)
            {
            }
);
            (*propertyDetails).setName("PropertyDetails");
            {
            }
            (*propertyDetails).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
            (*propertyDetails).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
            (*propertyDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
            (*propertyDetails).setAffectsParentLayout(true);
            (*details).addView(propertyDetails);
            eventDetails = CreateShared<LegacyClassGen::EventDetailsView>([this](LegacyClassGen::EventDetailsView *v)
            {
            }
);
            (*eventDetails).setName("EventDetails");
            {
            }
            (*eventDetails).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
            (*eventDetails).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
            (*eventDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
            (*eventDetails).setAffectsParentLayout(true);
            (*details).addView(eventDetails);
            functionDetails = CreateShared<LegacyClassGen::FunctionDetailsView>([this](LegacyClassGen::FunctionDetailsView *v)
            {
            }
);
            (*functionDetails).setName("FunctionDetails");
            {
            }
            (*functionDetails).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
            (*functionDetails).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
            (*functionDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
            (*functionDetails).setAffectsParentLayout(true);
            (*details).addView(functionDetails);
            (*v).body = details;
        }
);
        (*detailsPanel).setName("DetailsPanel");
        {
        }
        (*detailsPanel).setVisibility(UI::Visibility::SelfHidden|UI::Visibility::ChildrenHidden);
        (*detailsPanel).setAffectsParentLayout(true);
        (*contentView).addView(detailsPanel);
        dataPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
        {
            defaultValuesEditor = CreateShared<LegacyClassGen::ObjectEditor>([this](LegacyClassGen::ObjectEditor *v)
            {
            }
);
            (*defaultValuesEditor).setName("DefaultValuesEditor");
            {
            }
            (*defaultValuesEditor).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
            (*defaultValuesEditor).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
            (*v).body = defaultValuesEditor;
        }
);
        (*dataPanel).setName("DataPanel");
        {
        }
        (*contentView).addView(dataPanel);
        (*v).contentView = contentView;
    }
);
    (*scrollView).setName("ScrollView");
    {
    }
    (*scrollView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*scrollView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*scrollView).setAffectsParentLayout(true);
    (*this).addView(scrollView);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
