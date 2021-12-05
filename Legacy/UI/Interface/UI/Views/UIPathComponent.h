#pragma once

#include "Includes/TreeView.gen.h"

namespace UI
{

struct PathEntryTreeItem
{
    APath path;
    Array<PathEntryTreeItem> items;
    bool isExpanded = false;
};

class PathComponent : public TreeAdapter<PathEntryTreeItem>
{
public:
    Array<PathEntryTreeItem> items;

    TreeView<PathEntryTreeItem> *view = nullptr;
    SizeType getCountRootItems() const override { return items.size(); }
    PathEntryTreeItem *getRootItem(SizeType index) override { return &items[index]; }
    SizeType getCountChildItems(PathEntryTreeItem *parentItem) const override { return parentItem->isExpanded ? parentItem->items.size() : 0; }
    PathEntryTreeItem *getChildItem(PathEntryTreeItem *parentItem, SizeType index) override { return &parentItem->items[index]; }
    SharedReference<View> provideViewForItem(const AObject &sender, SizeType depth, PathEntryTreeItem *item) override
    {
        DefaultTreeItemView *itemView = new DefaultTreeItemView(depth, item->path.isRoot() ? item->path.toString() : item->path.name(), hasContent(item));
        itemView->expandButton->setText(item->isExpanded ? "-" : "+");
        itemView->expandButton->eventChannel.registerDelegate<TapGestureEvent>([this, itemView, item](TapGestureEvent &event) {
            loadContent(item);
            if (item->isExpanded)
            {
                item->isExpanded = false;
                itemView->expandButton->setText("+");
            }
            else
            {
                item->isExpanded = true;
                itemView->expandButton->setText("-");
            }
            UIApplication::getOperationDispatcher().addDelegate([this, item]() {
                view->notifyUpdateChildren(item);
                return AError::getEmptyError();
            }, true);
        });
        return SharedReference<View>(itemView);
    }

    bool hasContent(PathEntryTreeItem *parentItem) const
    {
        if (APathInfo(parentItem->path).isDirectory())
        {
            ADirectory directory(parentItem->path);
            ADirectoryIterator it = directory.begin();
            ++it;
            ++it;
            return it != directory.end();
        }

        return false;
    }

    void loadContent(PathEntryTreeItem *parentItem)
    {
        if (!parentItem->items.empty())
        {
            return;
        }

        parentItem->items.clear();

        APathInfo info(parentItem->path);
        if (info.isDirectory())
        {
            ADirectory dir(info);
            ADirectoryIterator it = dir.begin();
            ++it;
            ++it;
            for (; it != dir.end(); ++it)
            {
                parentItem->items.push_back({ it.path() });
            }
        }
    }
};

}
