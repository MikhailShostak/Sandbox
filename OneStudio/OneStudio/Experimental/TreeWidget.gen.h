#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
template<typename Type>
class TreeWidget : public UI::TreeView<Type>, public UI::TreeAdapter<Type>
{
public:
    using This = UI::TreeWidget<Type>;
    using Super = UI::TreeView<Type>;
    Array<SharedReference<Type>> items;

    void onLoad(ALoadEvent& event)
    {
        Super::onLoad(event);
        This::setProxyAdapter(this);
    }

    SizeType getCountRootItems() const override { return items.size(); }
    Type* getRootItem(SizeType index) override { return items[index].get(); }
    SizeType getCountChildItems(Type* parentItem) const override { return parentItem->isExpanded ? parentItem->getItems().size() : 0; }
    Type* getChildItem(Type* parentItem, SizeType index) override { return parentItem->getItems()[index].get(); }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
