#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <cstddef>
#include <Data>

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: EnumerationHeader
class TaskStatus
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: EnumerationBody
public:
    enum Enum
    {
        Scheduled,
        Started,
        Paused,
        Canceled,
        Failed,
        Completed,
    };
    Enum value = Scheduled;
    TaskStatus();
    inline TaskStatus(Enum value):value(value) {}
    inline TaskStatus(const TaskStatus &value):value(value.value) {}
    inline operator Enum() const { return value; }
    static constexpr const char *Names[] =
    {
        "Scheduled",
        "Started",
        "Paused",
        "Canceled",
        "Failed",
        "Completed",
    };
    inline TaskStatus(const String &name)
    {
        if (name == "Scheduled") { value = Scheduled; return; }
        if (name == "Started") { value = Started; return; }
        if (name == "Paused") { value = Paused; return; }
        if (name == "Canceled") { value = Canceled; return; }
        if (name == "Failed") { value = Failed; return; }
        if (name == "Completed") { value = Completed; return; }
    }
    inline String toString() const
    {
        switch (value)
        {
        case TaskStatus::Scheduled:
        {
            return Names[0];
        }
        case TaskStatus::Started:
        {
            return Names[1];
        }
        case TaskStatus::Paused:
        {
            return Names[2];
        }
        case TaskStatus::Canceled:
        {
            return Names[3];
        }
        case TaskStatus::Failed:
        {
            return Names[4];
        }
        case TaskStatus::Completed:
        {
            return Names[5];
        }
        }
        return String();
    }
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: Serialization
inline AJSONValue toJSONValue(const ::TaskStatus &value) { return value.toString(); }
inline void fromJSONValue(const AJSONValue &value, ::TaskStatus &output) { output = ::TaskStatus(value.toString()); }
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
