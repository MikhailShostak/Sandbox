#pragma once

#include "ARunLoop.h"
#include "AThread.h"
#include "ADelegate.h"
#include "AError.h"

#include <atomic>

enum class AOperationPriority
{
    High,
    Medium,
    Low
};

class AOperation
{
    friend class AOperationDispatcher;

public:

    virtual ~AOperation() {}

protected:

    virtual AError main() = 0;

private:

    virtual AError operator()() final
    {
        return main();
    }

};

using AOperationArray = Array<SharedReference<AOperation>>;

struct AOperationCallbacks
{
    ADelegate<AError()> mainCallback;
    ADelegate<void(AError &&error)> completionCallback;

    AOperationCallbacks() {}

    AOperationCallbacks(const AOperationCallbacks &callbacks) = default;
    AOperationCallbacks(AOperationCallbacks &&callbacks) = default;

    AOperationCallbacks &operator =(const AOperationCallbacks &callbacks) = default;
    AOperationCallbacks &operator =(AOperationCallbacks &&callbacks) = default;

    template<typename MainCallbackType, typename CompletionCallbackType>
    AOperationCallbacks(MainCallbackType &&mainCallback, CompletionCallbackType &&completionCallback):
        mainCallback(std::forward<MainCallbackType>(mainCallback)),
        completionCallback(std::forward<CompletionCallbackType>(completionCallback))
    {

    }

    AError operator ()() const
    {
        AAssert(mainCallback, "Invalid operation");
        AError error = mainCallback();
        if(completionCallback)
        {
            completionCallback(AError(error));
        }
        return error;
    }
};

class AOperationQueue
{

    Queue<AOperationCallbacks> highPriorityQueue;
    Queue<AOperationCallbacks> mediumPriorityQueue;
    Queue<AOperationCallbacks> lowPriorityQueue;
    mutable AMutex mutex;

public:

    bool hasOperations() const
    {
        AMutexLock lock(mutex);
        return !(highPriorityQueue.empty() && mediumPriorityQueue.empty() && lowPriorityQueue.empty());
    }

    template<typename OperationDelegate, typename CompletionDelegate>
    void push(OperationDelegate &&delegate, CompletionDelegate &&completion, AOperationPriority priority)
    {
        AMutexLock lock(mutex);
        switch(priority)
        {
        case AOperationPriority::High:
            highPriorityQueue.emplace_back(std::forward<OperationDelegate>(delegate), std::forward<CompletionDelegate>(completion));
            break;
        case AOperationPriority::Medium:
            mediumPriorityQueue.emplace_back(std::forward<OperationDelegate>(delegate), std::forward<CompletionDelegate>(completion));
            break;
        case AOperationPriority::Low:
            lowPriorityQueue.emplace_back(std::forward<OperationDelegate>(delegate), std::forward<CompletionDelegate>(completion));
            break;
        }
    }

    AOperationCallbacks pop()
    {
        AMutexLock lock(mutex);
        AOperationCallbacks operation;
        if(highPriorityQueue.size() > 0)
        {
            operation = std::move(highPriorityQueue.front());
            highPriorityQueue.pop_front();
        }
        else if(mediumPriorityQueue.size() > 0)
        {
            operation = std::move(mediumPriorityQueue.front());
            mediumPriorityQueue.pop_front();
        }
        else if(lowPriorityQueue.size() > 0)
        {
            operation = std::move(lowPriorityQueue.front());
            lowPriorityQueue.pop_front();
        }
        return operation;
    }

};

class AMultiThreadedLoop : public ARunLoop
{
    Array<AThread> threads;
public:

    using SizeType = decltype(std::thread::hardware_concurrency());

    static SizeType getHardwareConcurrency() { return std::max<SizeType>(std::thread::hardware_concurrency(), 1); }

    AMultiThreadedLoop(ARunnable &runnable, SizeType countThreads = getHardwareConcurrency()):
        ARunLoop(runnable)
    {
        for(SizeType i = 0; i < countThreads; ++i)
        {
            threads.emplace_back(&AMultiThreadedLoop::execute, this);
        }
    }

    virtual ~AMultiThreadedLoop()
    {
        AAssert(threads.empty(), "AOperationDispatcher has joinable threads");
    }

    void join()
    {
        for(auto &thread : threads)
        {
            thread.join();
        }
        threads.clear();
    }

    void detach()
    {
        for(auto &thread : threads)
        {
            thread.detach();
        }
        threads.clear();
    }

};

class AOperationDispatcher : public ARunnable
{
public:

    using Super = ARunLoop;

private:

    AOperationQueue mainThreadQueue;
    AOperationQueue multiThreadedQueue;
    AMultiThreadedLoop multiTherededLoop;
    bool exitAfterLastOperation = false;

public:

    AOperationDispatcher():
        multiTherededLoop(static_cast<ARunnable &>(*this))
    {

    }

    AOperationDispatcher(std::size_t countThreads):
        multiTherededLoop(static_cast<ARunnable &>(*this), countThreads)
    {

    }

public:

    template<template<typename Type> class Operations, typename Type>
    void addOperations(const Operations<Type> &operations, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);

    template<template<typename Type> class Operations, typename Type>
    void addOperations(const Operations<Type> &operations, const ADelegate<void(AError &&error)> &completion, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);

    void addOperation(const SharedReference<AOperation> &operation, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);
    void addOperation(const SharedReference<AOperation> &operation, const ADelegate<void(AError &&error)> &completion, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);

    template<typename DelegateType>
    void addDelegate(DelegateType &&delegate, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);
    template<typename DelegateType, typename CompletionType>
    void addDelegate(DelegateType &&delegate, CompletionType &&completion, bool mainThread = false, AOperationPriority priority = AOperationPriority::Medium);

    template<template<typename Type> class Operations, typename Type>
    AError performOperations(const Operations<Type> &operations, AOperationPriority priority = AOperationPriority::Medium);

    AError performOperation(const SharedReference<AOperation> &operation, AOperationPriority priority = AOperationPriority::Medium);

    template<typename DelegateType>
    AError performDelegate(DelegateType &&delegate, AOperationPriority priority = AOperationPriority::Medium);

    bool shouldExitAfterLastOperation() const
    {
        return this->exitAfterLastOperation;
    }

    void setExitAfterLastOperation(bool exitAfterLastOperation)
    {
        this->exitAfterLastOperation = exitAfterLastOperation;
    }

    void join()
    {
        exitIfNeeded();
        multiTherededLoop.join();
    }

    void detach()
    {
        multiTherededLoop.detach();
    }

    void exit()
    {
        multiTherededLoop.exit();
    }

    void execute()
    {
        //TODO: wtf is going on here?
        while(shouldExitAfterLastOperation())
        {
            executeMainThreadOperations();
        }
        multiTherededLoop.execute();
        join();
    }

    void executeMainThreadOperations()
    {
        while(mainThreadQueue.hasOperations())
        {
            mainThreadQueue.pop()();
        }
    }

    void executeMainThreadOperation()
    {
        if(mainThreadQueue.hasOperations())
        {
            mainThreadQueue.pop()();
        }
    }

    void onExecute() override
    {
        if(multiThreadedQueue.hasOperations())
        {
            multiThreadedQueue.pop()();
        }
        exitIfNeeded();
    }

private:

    void exitIfNeeded()
    {
        if(shouldExitAfterLastOperation() && !multiThreadedQueue.hasOperations())
        {
            multiTherededLoop.exit();
        }
    }

};

template<template<typename Type> class Operations, typename Type>
inline void AOperationDispatcher::addOperations(const Operations<Type> &operations, bool mainThread, AOperationPriority priority)
{
    for(auto operation : operations)
    {
        addDelegate(ADelegate<AError()>(operation, &AOperation::main), nullptr, mainThread, priority);
    }
}

template<template<typename Type> class Operations, typename Type>
inline void AOperationDispatcher::addOperations(const Operations<Type> &operations, const ADelegate<void(AError &&error)> &completion, bool mainThread, AOperationPriority priority)
{
    struct OperationBatch
    {
        OperationBatch(const AOperationArray &batchOperations, const ADelegate<void(AError &&error)> &batchCompletion):
            operations(batchOperations),
            iterator(operations.rbegin()),
            completion(batchCompletion)
        {}

        Array<SharedReference<AOperation>> operations;
        Array<SharedReference<AOperation>>::reverse_iterator iterator;
        ADelegate<void(AError &&error)> completion;
        AMutex mutex;
        bool failed = false;
    } *batch = new OperationBatch(operations, completion);

    auto batchIterator = [batch]()
    {
        SharedReference<AOperation> operation;
        batch->mutex.lock();
        if(batch->failed)
        {
            batch->mutex.unlock();
            return AError(1, "Operations were failed");
        }

        operation = *batch->iterator;
        batch->iterator++;
        batch->mutex.unlock();
        return operation->main();
    };

    auto batchCompletion = [batch](AError &&error)
    {
        batch->mutex.lock();
        if(batch->failed)
        {
            batch->mutex.unlock();
            return;
        }

        if(error)
        {
            batch->failed = true;
            batch->completion(std::move(error));
        }

        batch->operations.removeLast();
        if(batch->operations.isEmpty())
        {
            if(!batch->failed)
            {
                batch->completion(AError());
            }
            batch->mutex.unlock();
            delete batch;
        }
        else
        {
            batch->mutex.unlock();
        }
    };

    for(auto it = operations.begin(); it != operations.end(); ++it)
    {
        addDelegate(ADelegate<AError()>(batchIterator), ADelegate<void(AError &&error)>(batchCompletion), mainThread, priority);
    }
}

inline void AOperationDispatcher::addOperation(const SharedReference<AOperation> &operation, bool mainThread, AOperationPriority priority)
{
    addDelegate(ADelegate<AError()>(operation, &AOperation::main), nullptr, mainThread, priority);
}

inline void AOperationDispatcher::addOperation(const SharedReference<AOperation> &operation, const ADelegate<void(AError &&error)> &completion, bool mainThread, AOperationPriority priority)
{
    addDelegate(ADelegate<AError()>(operation, &AOperation::main), completion, mainThread, priority);
}

template<typename DelegateType>
inline void AOperationDispatcher::addDelegate(DelegateType &&delegate, bool mainThread, AOperationPriority priority)
{
    if(mainThread)
    {
        mainThreadQueue.push(std::forward<DelegateType>(delegate), nullptr, priority);
    }
    else
    {
        multiThreadedQueue.push(std::forward<DelegateType>(delegate), nullptr, priority);
        multiTherededLoop.resume();
    }
}

template<typename DelegateType, typename CompletionType>
inline void AOperationDispatcher::addDelegate(DelegateType &&delegate, CompletionType &&completion, bool mainThread, AOperationPriority priority)
{
    if(mainThread)
    {
        mainThreadQueue.push(std::forward<DelegateType>(delegate), std::forward<CompletionType>(completion), priority);
    }
    else
    {
        multiThreadedQueue.push(std::forward<DelegateType>(delegate), std::forward<CompletionType>(completion), priority);
        multiTherededLoop.resume();
    }
}

template<template<typename Type> class Operations, typename Type>
inline AError AOperationDispatcher::performOperations(const Operations<Type> &operations, AOperationPriority priority)
{
    AAssert(operations, "Operations list is empty");

    AError resultError;
    std::atomic<bool> finished(false);
    addOperations(operations, [&finished, &resultError](AError &&error){
        resultError = std::move(error);
        finished = true;
    }, false, priority);
    while(!finished)
    {
        onExecute();
    }
    return resultError;
}


inline AError AOperationDispatcher::performOperation(const SharedReference<AOperation> &operation, AOperationPriority priority)
{
    AAssert(operation, "Operation is null");

    AError resultError;
    std::atomic<bool> finished(false);
    addOperation(operation, [&finished, &resultError](AError &&error){
        resultError = std::move(error);
        finished = true;
    }, false, priority);
    while(!finished)
    {
        onExecute();
    }
    return resultError;
}


template<typename DelegateType>
inline AError AOperationDispatcher::performDelegate(DelegateType &&delegate, AOperationPriority priority)
{
    AError resultError;
    std::atomic<bool> finished(false);
    addDelegate(delegate, [&finished, &resultError](AError &&error){
        resultError = error;
        finished = true;
    }, false, priority);
    while(!finished)
    {
        onExecute();
    }
    return resultError;
}
