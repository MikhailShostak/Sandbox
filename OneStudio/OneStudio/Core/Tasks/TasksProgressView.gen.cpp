//CLASSGEN GENERATED REGION: Includes
#include "TasksProgressView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "TasksWidget.gen.h"
#include "MathClasses"
#include "ExperimentalDebug"
#include "Math"

//CLASSGEN END REGION
#include "TaskManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
TasksProgressView::TasksProgressView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_7_0;
    item_7_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_9_1;
    item_9_1.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_11_2;
    item_11_2.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_13_3;
    item_13_3.Alignment = Core::Alignment::Center;
    (*this).setData({item_7_0,item_9_1,item_11_2,item_13_3,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TasksProgressView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TasksProgressView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TasksProgressView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TasksProgressView");
    tasksGroupView = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
    {
        taskList = CreateShared<OneStudio::TasksWidget>([this](OneStudio::TasksWidget *v)
        {
        }
);
        (*taskList).setName("TaskList");
        {
        }
        (*taskList).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*v).body = taskList;
    }
);
    (*tasksGroupView).setName("TasksGroupView");
    {
    }
    (*tasksGroupView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).addView(tasksGroupView);
    commandsGroupPanel = CreateShared<UI::GroupPanel>([this](UI::GroupPanel *v)
    {
        SharedReference<UI::FlexBox> commandLineContainer = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
        {
        }
);
        (*commandLineContainer).setName("CommandLineContainer");
        {
        }
        UI::FlexBoxData item_0_0;
        UI::FlexBoxData item_1_1;
        UI::FlexBoxData item_2_2;
        (*commandLineContainer).setData({item_0_0,item_1_1,item_2_2,});
        (*commandLineContainer).setSpacing(0.000000);
        Math::Offsets padding_4;
        padding_4.Top = 1.000000;
        padding_4.Right = 1.000000;
        padding_4.Bottom = 1.000000;
        padding_4.Left = 1.000000;
        (*commandLineContainer).setPadding(padding_4);
        commandLineField = CreateShared<UI::TextField>([this](UI::TextField *v)
        {
        }
);
        (*commandLineField).setName("CommandLineField");
        {
        }
        (*commandLineContainer).addView(commandLineField);
        commandLineRunButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
        {
        }
);
        (*commandLineRunButton).setName("CommandLineRunButton");
        {
            (*commandLineRunButton).OnClick = [this]()            {
                return executeCommand();
            };
;
        }
        (*commandLineRunButton).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*commandLineRunButton).setText("Run");
        (*commandLineContainer).addView(commandLineRunButton);
        (*v).body = commandLineContainer;
    }
);
    (*commandsGroupPanel).setName("CommandsGroupPanel");
    {
    }
    (*this).addView(commandsGroupPanel);
}
//CLASSGEN END REGION
void TasksProgressView::executeCommand()
{
//     TaskManager::getThisInstance().getMainWorker().run_async_task([this]() -> async_void {
//         co_await TaskManager::getThisInstance().getMainWorker().schedule();
//         String command = this->commandLineField->getText();
//         auto task = TaskManager::getThisInstance().startTask().as<OneStudio::Task>();
//         task->setTitle(command);
//         task->action = [command](OneStudio::Task &task) -> async_void
//         {
//             task.log.append(Str::Format("Command: {}", command));
//             //co_await taskmanager.AsyncWorkers.schedule();
//             boost::process::ipstream pipe;
//             auto process = OS::Process::Open(command.toUtf8(), boost::process::std_out > pipe);
// 
//             std::string line;
//             while (process.running() && std::getline(pipe, line) && !line.empty())
//             {
//                 co_await TaskManager::getThisInstance().getMainWorker().schedule();
//                 task.log.append(line);
//                 co_await TaskManager::getThisInstance().getAsyncWorkers().schedule();
//             }
// 
//             process.wait();
//             task.error_code = process.exit_code();
//             co_return;
//         };
//         task->start();
//         co_return;
//     }());
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
