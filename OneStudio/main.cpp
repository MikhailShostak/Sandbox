#include "main.hpp"
#include <iostream>

#include <numeric>

#include "Memory/References.hpp"

void test()
{
    struct A {
        A() {}
        A(const A &other) { fmt::print("  A(const A &)\n"); }
        A(A &&other) { fmt::print("  A(A &&)\n"); }
        virtual ~A() {}
    };
    struct B { 
        B() {} 
        B(const B &other) { fmt::print("  B(const B &)\n"); }
        B(B &&other) { fmt::print("  B(B &&)\n"); }
    };
    struct C : public A, public B { 
        C() {} 
        C(const C &other) { fmt::print("  C(const C &)\n"); }
        C(C &&other) { fmt::print("  C(C &&)\n"); }
    };
    struct D : public C { 
        D() {} 
        D(const D &other) { fmt::print("  D(const D &)\n"); }
        D(D &&other) { fmt::print("  D(D &&)\n"); }
    };

    A *ap = new C();
    B *bp = new B();
    C *cp = new D();
    D *dp = new D();

    D s;
    const D cs = s;


    C &rs = s;
    C &&rvs = std::move(s);
    C *ps = &s;

    const C &crs = s;
    const C &&crvs = std::move(s);
    const C *cps = &s;

    fmt::print("const_cast\n");
    D &_r1 = const_cast<D &>(cs);
    C &_r2 = const_cast<C &>(crs);
    C &&_r3 = const_cast<C &&>(crvs);
    C *_r4 = const_cast<C *>(cps);

    C &&_c3 = const_cast<C &&>(std::move(crvs));

    fmt::print("reinterpret_cast\n");
    B &_r5 = reinterpret_cast<B &>(s);
    B &_r6 = reinterpret_cast<B &>(rs);
    B &&_r7 = reinterpret_cast<B &&>(rvs);
    B *_r8 = reinterpret_cast<B *>(ps);

    fmt::print("dynamic_cast\n");
    D &_r9 = dynamic_cast<D &>(s);
    D &_r10 = dynamic_cast<D &>(rs);
    D &&_r11 = std::move(dynamic_cast<D &&>(std::move(rvs)));
    D *_r12 = dynamic_cast<D *>(ps);

    fmt::print("auto\n");
    auto &v1 = dynamic_cast<C &>(*ap);
    //auto v2 = dynamic_cast<C &>(*bp);

    char a = 0;
    short b = 0;
    int c = 0;
    long d = 0;

    unsigned char ua = 0;
    unsigned short ub = 0;
    unsigned int uc = 0;
    unsigned long ud = 0;

    float f = 0;
    double fd = 0;

    fmt::print("ConstCast\n");
    C &c1 = ConstCast(cs);
    C &c2 = ConstCast(crs);
    C &&c3 = ConstCast(std::move(crvs));
    C *c4 = ConstCast(cps);

    fmt::print("StaticCast\n");
    int iv = StaticCast<int>(1.0);

    D &_r13 = StaticCast<D>(s);
    D &_r14 = StaticCast<D>(rs);
    D &&_r15 = StaticCast<D>(std::move(rvs));
    D *_r16 = StaticCast<D>(ps);
    const D &_r17 = StaticCast<D>(crs);
    const D *_r18 = StaticCast<D>(cps);

    fmt::print("DynamicCast\n");
    //int iv2 = DynamicCast<int>(1.0);

    D &_r19 = DynamicCast<D>(s);
    D &_r20 = DynamicCast<D>(rs);
    D &&_r21 = DynamicCast<D>(std::move(rvs));
    D *_r22 = DynamicCast<D>(ps);
    const D &_r23 = DynamicCast<D>(crs);
    const D *_r24 = DynamicCast<D>(cps);

    SharedReference<C> sptr_c = std::make_shared<D>();
    SharedReference<D> sptr_d = DynamicCast<D>(sptr_c);

    UniqueReference<C> uptr_c = std::make_unique<C>();
    UniqueReference<D> uptr_d = DynamicCast<D>(uptr_c);
}

using Debug::g_Profiler;

int main()
{
    Debug::ProfilerScopeRecord record{ "int main()" };
    //test();

    g_Profiler.m_Path = "trace.json";

    TaskManager g_TaskManager;
    g_TaskManager.m_TaskBatchSize = 4;
    //g_Profiler.Register(g_TaskManager.m_AsyncWorkers.m_ThreadStates, "Worker Thread");
    //g_TaskManager.m_Tasks.reserve(1024);
    //g_TaskManager.m_AsyncTasks.reserve(1024);

    {
        Debug::ProfilerScopeRecord record{ "Sleep 100ms" };
        Multithreading::Sleep(DateTime::Milliseconds(100));
    }

    g_TaskManager.Dispatch([&]() {

        auto d = DateTime::Milliseconds(1);
        size_t count_tasks = 10000;

        auto wait = [&]() {
            DateTime::System::Time t = DateTime::System::Clock::now() + d;
            while (true)
            {
                if (DateTime::System::Clock::now() > t)
                {
                    break;
                }
            }
        };

        auto job = [&](size_t i)
        {
            size_t event = g_Profiler.Record(fmt::format("Task #{}", i));
            wait();
            g_Profiler.Stop(event);
            return event;
        };

        {
            Debug::ProfilerScopeRecord record{ "std::async" };
            std::vector<std::future<size_t>> futures;
            Multithreading::Mutex mutex;
            for (size_t i = 0; i < count_tasks; ++i)
            {
                futures.push_back(std::move(std::async(std::launch::async, job, i)));
            }
            for (auto &f : futures)
            {
                f.get();
            }
        }

        {
            Debug::ProfilerScopeRecord record{ "Coroutines" };

            std::vector<std::function<size_t(int)>> tasks;
            tasks.reserve(count_tasks);
            for (size_t i = 0; i < count_tasks; ++i)
            {
                tasks.push_back(job);
            }
            auto coro = g_TaskManager.AwaitAsync(std::move(tasks));
            for (auto [i, event] : coro)
            {
                auto t = DateTime::Unix::GetTimestamp();
                //g_Profiler.Stop(event);
            }
        }

        g_TaskManager.m_IsRunning = false;
    });

    /*g_TaskManager.Dispatch([&]() {
        fmt::print("  |_Bar Task #1/4 (Thread ID {})\n", std::this_thread::get_id());
        Task::Suspend();
        fmt::print("  |_Bar Task #2/4 (Thread ID {})\n", std::this_thread::get_id());
        g_TaskManager.Dispatch([&]() {
            fmt::print("  |_Baz Task #1/3 (Thread ID {})\n", std::this_thread::get_id());
            Task::Suspend();

            std::vector<std::function<void(size_t i)>> tasks;
            for (size_t i = 0; i < 100; ++i)
            {
                tasks.push_back([](size_t i) {
                    fmt::print("    |_Foo Task #{} (Started on thread {})\n", i, std::this_thread::get_id());
                });
            }
            auto coro = AwaitAsync(g_TaskManager, tasks);
            for (size_t i : coro)
            {
                fmt::print("    |_Foo Task #{} (Finished on thread {})\n", i, std::this_thread::get_id());
            }

            fmt::print("  |_Baz Task #2/3 (Thread ID {})\n", std::this_thread::get_id());
            Task::Suspend();
            fmt::print("  |_Baz Task #3/3 (Thread ID {})\n", std::this_thread::get_id());

            g_TaskManager.m_IsRunning = false;
        });
        auto v1 = g_TaskManager.AwaitAsync([]() {
            fmt::print("  |_Async Task #1 (Thread ID {})\n", std::this_thread::get_id());
            return 100000;
        });
        auto v2 = g_TaskManager.AwaitAsync([]() {
            fmt::print("  |_Async Task #2 (Thread ID {})\n", std::this_thread::get_id());
            return 500;
        });
        fmt::print("  |_Value: {}\n", v1 + v2);
        Task::Suspend();
        fmt::print("  |_Bar Task #3/4 (Thread ID {})\n", std::this_thread::get_id());
        Task::Suspend();
        fmt::print("  |_Bar Task #4/4 (Thread ID {})\n", std::this_thread::get_id());

    });*/

    size_t i = 0;
    while (g_TaskManager.m_IsRunning)
    {
        Debug::ProfilerScopeRecord record{ "Frame #{}", i++ };
        g_TaskManager.Process();
    }

    return 0;
}







