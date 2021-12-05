//CLASSGEN GENERATED REGION: Includes
#include "GraphEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GraphEditor::GraphEditor()
{
    UI::SplitViewLayoutData item_46_0;
    (*this).setData({item_46_0,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GraphEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void GraphEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
UnorderedDictionary<String, LegacyClassGen::GraphData> GraphEditor::getGraphs() const
{
    return this->Graphs;
}
void GraphEditor::setGraphs(UnorderedDictionary<String, LegacyClassGen::GraphData> const &Graphs)
{
    this->Graphs = Graphs;
}
void GraphEditor::setGraphs(UnorderedDictionary<String, LegacyClassGen::GraphData> &&Graphs)
{
    this->Graphs = std::move(Graphs);
}
APair<String, LegacyClassGen::GraphData> GraphEditor::getCurrentGraph() const
{
    return this->CurrentGraph;
}
void GraphEditor::setCurrentGraph(APair<String, LegacyClassGen::GraphData> const &CurrentGraph)
{
    this->CurrentGraph = CurrentGraph;
}
void GraphEditor::setCurrentGraph(APair<String, LegacyClassGen::GraphData> &&CurrentGraph)
{
    this->CurrentGraph = std::move(CurrentGraph);
}
void GraphEditor::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("GraphEditor");
    gridView = CreateShared<UI::GridView>([this](UI::GridView *v)
    {
        SharedReference<UI::GraphView> root = CreateShared<UI::GraphView>([this](UI::GraphView *v)
        {
        }
);
        (*root).setName("Root");
        {
        }
        (*root).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*root).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*root).setAlwaysShowVerticalShadow(true);
        (*root).setAlwaysShowHorizontalShadow(true);
        (*root).setContentFit(UI::ContentFit::HalfPaddings);
        (*v).root = root;
    }
);
    (*gridView).setName("GridView");
    {
    }
    (*gridView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*gridView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).addView(gridView);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
