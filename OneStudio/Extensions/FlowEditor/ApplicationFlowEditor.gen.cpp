//CLASSGEN GENERATED REGION: Includes
#include "ApplicationFlowEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ExperimentalDebug"
#include "MathClasses"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationFlowEditor::ApplicationFlowEditor()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationFlowEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationFlowEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationFlowEditor::onHierarchyCreate()
{
    sidebarPages = CreateShared<UI::PageView>([this](UI::PageView *v)
    {
    }
);
    (*sidebarPages).setName("SidebarPages");
    {
    }
    UI::OverlayData item_0_0;
    UI::OverlayData item_1_1;
    UI::OverlayData item_2_2;
    UI::OverlayData item_3_3;
    (*sidebarPages).setData({item_0_0,item_1_1,item_2_2,item_3_3,});
    flowProperties = Create<LegacyClassGen::ApplicationFlowProperties>([this](LegacyClassGen::ApplicationFlowProperties *v)
    {
    }
);
    (*flowProperties).setName("FlowProperties");
    {
    }
    (*sidebarPages).addView(flowProperties);
    stateProperties = Create<LegacyClassGen::ApplicationStateProperties>([this](LegacyClassGen::ApplicationStateProperties *v)
    {
    }
);
    (*stateProperties).setName("StateProperties");
    {
    }
    (*sidebarPages).addView(stateProperties);
    transitionProperties = Create<LegacyClassGen::ApplicationTransitionProperties>([this](LegacyClassGen::ApplicationTransitionProperties *v)
    {
    }
);
    (*transitionProperties).setName("TransitionProperties");
    {
    }
    (*sidebarPages).addView(transitionProperties);
    objectEditor = Create<LegacyClassGen::ObjectEditor>([this](LegacyClassGen::ObjectEditor *v)
    {
    }
);
    (*objectEditor).setName("ObjectEditor");
    {
    }
    (*sidebarPages).addView(objectEditor);
    (*this).addView(sidebarPages);
    Super::onHierarchyCreate();
    setName("ApplicationFlowEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
