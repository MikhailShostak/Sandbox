//CLASSGEN GENERATED REGION: Includes
#include "ViewEditorView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ExperimentalDebug"
#include "MathClasses"
#include "Math"
#include "ClassGenExtensions"
#include "ClassGenLibraryDebug"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ViewEditorView::ViewEditorView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::SplitViewLayoutData item_12_0;
    UI::SplitViewLayoutData item_13_1;
    UI::SplitViewLayoutData item_14_2;
    (*this).setData({item_12_0,item_13_1,item_14_2,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ViewEditorView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ViewEditorView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ViewEditorView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ViewEditorView");
    SharedReference<UI::FlexBox> uIFlexBox = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*uIFlexBox).setName("UIFlexBox");
    {
    }
    UI::FlexBoxData item_0_0;
    UI::FlexBoxData item_1_1;
    UI::FlexBoxData item_2_2;
    UI::FlexBoxData item_3_3;
    (*uIFlexBox).setData({item_0_0,item_1_1,item_2_2,item_3_3,});
    (*uIFlexBox).setDirection(UI::Direction::Vertical);
    (*uIFlexBox).setSpacing(4.000000);
    viewsGroupPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
    {
        outliner = CreateShared<UI::TreeView<LegacyClassGen::ViewNode>>([this](UI::TreeView<LegacyClassGen::ViewNode> *v)
        {
        }
);
        (*outliner).setName("Outliner");
        {
        }
        (*v).body = outliner;
    }
);
    (*viewsGroupPanel).setName("ViewsGroupPanel");
    {
    }
    (*viewsGroupPanel).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*uIFlexBox).addView(viewsGroupPanel);
    testButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*testButton).setName("TestButton");
    {
    }
    (*testButton).setText("Test");
    (*uIFlexBox).addView(testButton);
    (*this).addView(uIFlexBox);
    SharedReference<UI::FlexBox> content = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*content).setName("Content");
    {
    }
    (*content).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_4_0;
    UI::FlexBoxData item_5_1;
    (*content).setData({item_4_0,item_5_1,});
    (*content).setDirection(UI::Direction::Vertical);
    SharedReference<UI::FlexBox> toolbar = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*toolbar).setName("Toolbar");
    {
    }
    UI::FlexBoxData item_6_0;
    UI::FlexBoxData item_7_1;
    UI::FlexBoxData item_8_2;
    UI::FlexBoxData item_9_3;
    (*toolbar).setData({item_6_0,item_7_1,item_8_2,item_9_3,});
    snapToGridSwitcher = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*snapToGridSwitcher).setName("SnapToGridSwitcher");
    {
    }
    (*snapToGridSwitcher).setText("Snap");
    (*toolbar).addView(snapToGridSwitcher);
    gridSwitcher = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*gridSwitcher).setName("GridSwitcher");
    {
    }
    (*gridSwitcher).setText("Grid");
    (*toolbar).addView(gridSwitcher);
    checkSwitcher = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*checkSwitcher).setName("CheckSwitcher");
    {
    }
    (*checkSwitcher).setText("Check");
    (*toolbar).addView(checkSwitcher);
    (*content).addView(toolbar);
    gridView = CreateShared<UI::GridView>([this](UI::GridView *v)
    {
        graph = CreateShared<UI::ScrollView>([this](UI::ScrollView *v)
        {
        }
);
        (*graph).setName("Graph");
        {
        }
        (*graph).setAlwaysShowVerticalShadow(true);
        (*graph).setAlwaysShowHorizontalShadow(true);
        (*graph).setContentFit(UI::ContentFit::HalfPaddings);
        (*v).root = graph;
    }
);
    (*gridView).setName("GridView");
    {
    }
    (*gridView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*content).addView(gridView);
    (*this).addView(content);
    SharedReference<UI::Overlay> uIOverlay = CreateShared<UI::Overlay>([this](UI::Overlay *v)
    {
    }
);
    (*uIOverlay).setName("UIOverlay");
    {
    }
    (*uIOverlay).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*uIOverlay).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::OverlayData item_10_0;
    UI::OverlayData item_11_1;
    (*uIOverlay).setData({item_10_0,item_11_1,});
    propertiesView = CreateShared<LegacyClassGen::ViewPropertiesEditor>([this](LegacyClassGen::ViewPropertiesEditor *v)
    {
    }
);
    (*propertiesView).setName("PropertiesView");
    {
    }
    (*propertiesView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*propertiesView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*uIOverlay).addView(propertiesView);
    classEditor = CreateShared<LegacyClassGen::ClassEditor>([this](LegacyClassGen::ClassEditor *v)
    {
    }
);
    (*classEditor).setName("ClassEditor");
    {
    }
    (*classEditor).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*classEditor).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*uIOverlay).addView(classEditor);
    (*this).addView(uIOverlay);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
