#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioPlatform
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class Task
{
public:
    virtual ~Task() {}

    virtual const String &getTitle() const = 0;
    virtual void setTitle(const String &text) = 0;

    virtual const String &getText() const = 0;
    virtual void setText(const String &text) = 0;

    virtual SharedReference<Task> createSubTask() = 0;
    virtual void setAction(const std::function<void(Task &task)> &action) = 0;
    virtual void Log(const String &line) = 0;
    virtual void start() = 0;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
