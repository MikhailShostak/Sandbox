//CLASSGEN GENERATED REGION: Includes
#include "NodeSearchView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include "FunctionManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
NodeSearchView::NodeSearchView()
{
    UI::FlexBoxData item_58_0;
    UI::FlexBoxData item_59_1;
    UI::FlexBoxData item_60_2;
    (*this).setData({item_58_0,item_59_1,item_60_2,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(4.000000);
    Math::Offsets padding_63;
    padding_63.Top = 4.000000;
    padding_63.Right = 4.000000;
    padding_63.Bottom = 4.000000;
    padding_63.Left = 4.000000;
    (*this).setPadding(padding_63);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NodeSearchView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void NodeSearchView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NodeSearchView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("NodeSearchView");
    searchField = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*searchField).setName("SearchField");
    {
    }
    (*searchField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).addView(searchField);
    searchResults = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*searchResults).setName("SearchResults");
    {
        (*searchResults).CountItems = [this]()        {
            return FoundFunctions.size();
        };
;
        (*searchResults).Item = [this](SizeInteger const& Index) -> SharedReference<UI::View>         {
            auto instance = CreateShared<UI::Label>();
            instance->setText(FoundFunctions[Index].Identifier);
            return instance;
        };
;
    }
    Math::IntegerVector size_49;
    size_49.X = 300.000000;
    size_49.Y = 300.000000;
    (*searchResults).setSize(size_49);
    (*searchResults).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*searchResults).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*searchResults).setAffectsParentLayout(true);
    (*this).addView(searchResults);
    addButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*addButton).setName("AddButton");
    {
    }
    (*addButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*addButton).setText("Add");
    (*this).addView(addButton);
}
//CLASSGEN END REGION
void NodeSearchView::setType(const SharedReference<LegacyClassGen::BaseCGType> &type)
{
    AvailableFunctions.clear();
    LegacyClassGen::FunctionManager::getInstance().Index();
    AvailableFunctions = LegacyClassGen::FunctionManager::getInstance().Cache;
}

void NodeSearchView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    //LegacyClassGen::
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
