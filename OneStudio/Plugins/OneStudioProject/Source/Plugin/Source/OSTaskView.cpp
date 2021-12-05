#include "OSTaskView.h"

namespace UI
{

OSTaskView::OSTaskView()
{
    //ui->setupUi(this);
}

OSTaskView::~OSTaskView()
{
    //delete ui;
}

String OSTaskView::getTitle() const
{
    return String();
    //return ui->titleLabel->text().toUtf8().data();
}

void OSTaskView::setTitle(const String &title)
{
    //ui->titleLabel->setText(title.toUtf8().data());
}

String OSTaskView::getPlaceholder() const
{
    return this->placeholder;
}

void OSTaskView::setPlaceholder(const String &placeholder)
{
    this->placeholder = placeholder;
    updateTasks();
}

void OSTaskView::updateTasksList()
{
    views.clear();
    /*ui->addTaskComboBox->clear();
    ui->addTaskComboBox->addItem(getPlaceholder().toUtf8().data());
    for(auto &task : tasks)
    {
        ui->addTaskComboBox->addItem(task->getName().toUtf8().data());
    }*/
    updateTasks();
}

void OSTaskView::updateTasks()
{
    /*views.clear();

    if(!target || !tasks)
    {
        return;
    }

    auto taskDataObjects = target->findTasks(getStepType());
    std::sort(taskDataObjects.begin(), taskDataObjects.end(), [](const SharedReference<OSTaskDataObject> &a, const SharedReference<OSTaskDataObject> &b) {
            return a->getIndex() < b->getIndex();
    });
    for(auto &task : taskDataObjects)
    {
        auto view = createTaskView(task);
        views.append(view);
        ui->verticalLayout->insertWidget(ui->verticalLayout->count() - 1, view.data());
    }*/
}

SharedReference<OSTaskItemView> OSTaskView::createTaskView(const SharedReference<OSTaskDataObject> &taskData)
{
    /*for(auto &task : tasks)
    {
        if(task->getPackage() == taskData->getPackage()) {
            return createTaskView(taskData, task);
        }
    }*/
    return nullptr;
}

SharedReference<OSTaskItemView> OSTaskView::createTaskView(const SharedReference<OSTaskDataObject> &taskData, OSTargetTask *task)
{
    /*auto view = createNew<OSTaskItemView>();
    view->setTarget(target);
    view->setTaskData(taskData);
    view->setTask(task);
    view->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(view, &OSTaskItemView::up, [this, view](){
        auto index = ui->verticalLayout->layout()->indexOf(view);
        if(index > 1)
        {
            ui->verticalLayout->insertWidget(index - 1, view);

            int itemIndex = index - 1;
            int newIndex = itemIndex - 1;

            views[itemIndex]->getTaskData()->setIndex(newIndex);
            views[newIndex]->getTaskData()->setIndex(itemIndex);

            auto movedView = views[itemIndex];
            views[itemIndex] = views[newIndex];
            views[newIndex] = movedView;
        }
    });
    QObject::connect(view, &OSTaskItemView::down, [this, view](){
        auto index = ui->verticalLayout->layout()->indexOf(view);
        if(index < ui->verticalLayout->layout()->count() - 2)
        {
            ui->verticalLayout->insertWidget(index + 1, view);

            int itemIndex = index - 1;
            int newIndex = itemIndex + 1;

            views[itemIndex]->getTaskData()->setIndex(newIndex);
            views[newIndex]->getTaskData()->setIndex(itemIndex);

            auto movedView = views[itemIndex];
            views[itemIndex] = views[newIndex];
            views[newIndex] = movedView;
        }
    });
    QObject::connect(view, &OSTaskItemView::remove, [this, view](){
        view->setParent(nullptr);
        view->close();
        this->target->removeTask(view->getTaskData());
        this->target->save();
        for(auto it = this->views.begin(); it != this->views.end(); ++it)
        {
            if(it->data() == view) {
                this->views.erase(it);
                break;
            }
        }
    });*/
    return nullptr;
}

void OSTaskView::addTask(int index)
{
    /*if(!target || index == 0 || index == -1)
    {
        return;
    }

    auto &task = getTasks().at(index - 1);

    auto taskData = target->createTask();
    taskData->setIndex(views.size());
    taskData->setPackage(task->getPackage());
    taskData->setStepType(stepType);

    auto view = createTaskView(taskData, task);
    view->setContentVisible(true);
    views.append(view);
    ui->verticalLayout->insertWidget(ui->verticalLayout->count() - 1, view.data());

    ui->addTaskComboBox->setCurrentIndex(0);*/
}

}
