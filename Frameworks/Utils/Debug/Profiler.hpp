#pragma once

#include "Containers/Array.hpp"
#include "DateTime/Time.hpp"
#include "Multithreading/Thread.hpp"
#include "System/Filesystem.hpp"
#include "Text/String.hpp"

namespace Debug
{

struct ProfilerEvent
{
    String Name;
    DateTime::HighResolution::Time StartTime;
    DateTime::HighResolution::Time EndTime;
    Multithreading::ThreadID ThreadID;
};

struct Profiler
{
    struct ThreadInfo
    {
        String Name;
        Multithreading::ThreadID ID;
    };

    Multithreading::RecursiveMutex m_Mutex;
    System::Path m_Path;
    int m_PID = boost::this_process::get_id();

    Array<ThreadInfo> m_Threads;
    ProfilerEvent m_Session;

    Profiler()
    {
        m_Events.reserve(1024 * 64);
        m_Threads.reserve(64);

        auto id = std::this_thread::get_id();
        m_Threads.push_back({ fmt::format("Main Thread ({})", id), id });

        StartSession();
    }

    ~Profiler()
    {
        StopSession();
    }

    void StartSession()
    {
        m_Session.Name = "Profiler Session";
        m_Session.StartTime = DateTime::HighResolution::Clock::now();
        m_Session.ThreadID = std::this_thread::get_id();
    }

    void StopSession()
    {
        m_Session.EndTime = DateTime::HighResolution::Clock::now();

        if (!m_Path.empty())
        {
            std::ofstream file;
            file.open(m_Path);
            if (file.is_open())
            {
                file << "[\n";
                size_t threadIndex = 0;
                for (auto &t : m_Threads)
                {
                    file << "    " << fmt::format(R"(    {{"name": "thread_name", "ph": "M", "pid": {}, "tid": {}, "args": {{ "name" : "{}" }} }})",
                        m_PID,
                        t.ID,
                        t.Name
                    ) << ",\n";
                    file << "    " << fmt::format(R"(    {{"name": "thread_sort_index", "ph": "M", "pid": {}, "tid": {}, "args": {{ "sort_index" : {} }} }})",
                        m_PID,
                        t.ID,
                        threadIndex
                    ) << ",\n";
                    ++threadIndex;
                }
                for (auto &e : m_Events)
                {
                    PrintEvent(file, e);
                    file << ",\n";
                }
                PrintEvent(file, m_Session);
                file << "\n";
                file << "]\n";
                file.close();
            }
        }
    }

    void RegisterThreads(const Array<std::reference_wrapper<Multithreading::Thread>> &threads, const String &label)
    {
        size_t i = 0;
        for (auto &thread : threads)
        {
            auto id = thread.get().get_id();
            m_Threads.push_back({ fmt::format("{} #{} ({})", label, i, id), id });
            ++i;
        }
    }

    void RegisterThreads(const Array<Multithreading::Thread> &threads, const String &label)
    {
        size_t i = 0;
        for (auto &thread : threads)
        {
            auto id = thread.get_id();
            m_Threads.push_back({ fmt::format("{} #{} ({})", label, i, id), id });
            ++i;
        }
    }

    void PrintEvent(std::ofstream &file, ProfilerEvent &e)
    {
        file << "    " << fmt::format(R"(    {{"name": "{}", "ph": "B", "pid": {}, "tid": {}, "ts": {}}})",
            e.Name,
            m_PID,
            e.ThreadID,
            std::chrono::duration_cast<DateTime::Microseconds>(e.StartTime.time_since_epoch()).count()
        ) << ",\n";
        file << "    " << fmt::format(R"(    {{"name": "{}", "ph": "E", "pid": {}, "tid": {}, "ts": {}}})",
            e.Name,
            m_PID,
            e.ThreadID,
            std::chrono::duration_cast<DateTime::Microseconds>(e.EndTime.time_since_epoch()).count()
        );
    }

    Array<ProfilerEvent> m_Events;

    size_t Record(const String &name)
    {
        Multithreading::RecursiveMutexLock lock{ m_Mutex };
        ProfilerEvent e;
        e.Name = name;
        e.StartTime = DateTime::HighResolution::Clock::now();
        e.ThreadID = std::this_thread::get_id();
        m_Events.push_back(std::move(e));
        return m_Events.size() - 1;
    }

    void Stop(size_t id)
    {
        Multithreading::RecursiveMutexLock lock{ m_Mutex };
        m_Events[id].EndTime = DateTime::HighResolution::Clock::now();
    }
};

inline Profiler g_Profiler;

struct ProfilerScopeRecord
{
    size_t m_EventID = 0;

    template<typename ...Arguments>
    ProfilerScopeRecord(const char *format, Arguments &&...arguments)
    {
        m_EventID = g_Profiler.Record(fmt::format(format, std::forward<Arguments>(arguments)...));
    }

    ~ProfilerScopeRecord()
    {
        g_Profiler.Stop(m_EventID);
    }
};

}
