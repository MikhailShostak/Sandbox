#pragma once

#include <type_traits>

#define DECLARE_NESTED_TYPE_CHECKS_TEMP(get_name, check_name, typedef_name)\
    template<typename Type> constexpr static std::false_type __## typedef_name ##_impl__(...);\
    template<typename Type> constexpr static typename Type::typedef_name __## typedef_name ##_impl__(Type*);\
    template<typename Type> struct get_name { using type = decltype(__## typedef_name ##_impl__<Type>(0)); };\
    template<typename Type> struct check_name { constexpr static bool value = !std::is_same<typename get_name<Type>::type, std::false_type>::value; }

constexpr static std::false_type __typedef_name_impl__(...);
template<typename Type> constexpr static typename Type::Super __typedef_name_impl__(Type*);
template<typename Type> struct GetBaseType2 { using type = decltype(__typedef_name_impl__(static_cast<Type*>(0))); };
template<typename Type> struct HasBaseType2 { constexpr static bool value = !std::is_same<typename GetBaseType2<Type>::type, std::false_type>::value; };


//DECLARE_NESTED_TYPE_CHECKS_TEMP(GetBaseType2, HasBaseType2, Super);

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "OneStudioPlatform"

//CLASSGEN END REGION
#include <Experimental>
#include "Task.gen.h"
#include "TasksWidget.gen.h"
#include "TasksProgressView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
struct TaskManager : public Serializable, public Core::ApplicationComponent2, public ApplicationComponent, public OneStudioPlatform::TaskContext
{
    ::TaskManager tm;
    
    SharedReference<OneStudio::TasksProgressView> view;
    SharedReference<UI::TextField> logView;

    static TaskManager& getThisInstance() { return getInstanceAs<TaskManager>(); }

    void onLoad() override;
    void onApplicationStart(const AApplication &application) override;

    //ServiceScheduler& getMainWorker() override { return tm.MainWorker; }
    //ThreadPoolScheduler& getAsyncWorkers() override { return tm.AsyncWorkers; }
    AEventDispatcher& getEventDispatcher() const override { return UIApplication::getEventDispatcher(); }
    AOperationDispatcher* getOperationDispatcher() const override { return &UIApplication::getOperationDispatcher(); }

    SharedReference<OneStudioPlatform::Task> startTask() override;
    void finishTask(const SharedReference<OneStudioPlatform::Task>& task) override;
    void clearTasks() override;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
