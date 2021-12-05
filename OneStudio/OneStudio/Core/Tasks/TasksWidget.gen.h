#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "TreeWidget.gen.h"
#include "Task.gen.h"

//CLASSGEN END REGION
#include <iomanip> //std::put_time
#include "OneStudioTextures.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class TasksWidget : public UI::TreeWidget<Task>
{
public:

    void updateItemView(UI::DefaultExpandableItemView *itemView, Task *item)
    {
        std::stringstream ss;
        time_t startTime = ASystemClock::to_time_t(item->startTime);
        ss << std::put_time(std::localtime(&startTime), "%F %T");

        switch (item->status)
        {
        case TaskStatus::Scheduled:
            itemView->icon->setColor(AColorName::Gray);
            break;
        case TaskStatus::Started:
            itemView->icon->setColor(AColorName::Green);
            break;
        case TaskStatus::Paused:
            itemView->icon->setColor(AColorName::Cyan);
            break;
        case TaskStatus::Canceled:
            itemView->icon->setColor(AColorName::Gray);
            break;
        case TaskStatus::Failed:
            itemView->icon->setColor(AColorName::Red);
            break;
        case TaskStatus::Completed:
            itemView->icon->setColor(AColorName::Green);
            break;
        }

        if(item->status == TaskStatus::Scheduled)
        {
            itemView->title->setText(fmt::format("[{}] {}", ss.str().data(), item->getTitle()));
        }
        else
        {
            auto ms = std::chrono::duration_cast<AMilliseconds>(item->endTime - item->startTime).count();
            itemView->title->setText(fmt::format("[{}] {} {} ms", ss.str().data(), item->getTitle(), ms));
        }
    }

    SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType depth, Task *item) override
    {
        SharedReference<UI::DefaultExpandableItemView> itemView = CreateShared<UI::DefaultExpandableItemView>();
        itemView->applyParameters(depth, item->getTitle(), item->getItems().size());
        WeakReference<UI::DefaultExpandableItemView> itemViewWeak = itemView;
        itemView->icon->setImage(SharedReference<Legacy::Graphics::Texture>(::Light));
        updateItemView(itemView.get(), item);
        item->onUpdated = [itemViewWeak, item, this]() {
            auto itemView = itemViewWeak.lock();
            if (!itemView)
            {
                return;
            }
            updateItemView(itemView.get(), item);
        };
        item->onSubtaskAdded = [itemViewWeak, item, this]() {
            auto itemView = itemViewWeak.lock();
            if (!itemView)
            {
                return;
            }
            itemView->setExpandable(true);
            itemView->icon->setImage(SharedReference<Legacy::Graphics::Texture>(::Light));
            this->notifyUpdateChildren(item);
        };
        if (item->isExpanded)
        {
            itemView->expandButton->setBackgroundImage(MinusButtonSmall);
        }
        else
        {
            itemView->expandButton->setBackgroundImage(PlusButtonSmall);
        }
        itemView->expandButton->eventChannel.registerDelegate([itemViewWeak, item, this](UI::TapGestureEvent &event) {
            auto itemView = itemViewWeak.lock();
            item->isExpanded = !item->isExpanded;
            if (item->isExpanded)
            {
                itemView->expandButton->setBackgroundImage(MinusButtonSmall);
            }
            else
            {
                itemView->expandButton->setBackgroundImage(PlusButtonSmall);
            }
            this->notifyUpdateChildren(item);
        });

        return itemView;
    }

};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
