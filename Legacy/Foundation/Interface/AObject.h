#pragma once

#include "AEvent.h"
#include "AMemory.h"
#include "String.h"
#include "AMeta.h"
#include "ALog.h"
#include "Serializable.h"

class AObject;

class AEventListener final
{
    using CallbackMap = Map<size_t, void(*)(AObject &object, AEvent &event)>;

    template<typename ObjectType, typename EventType>
    constexpr static ObjectType &getObject(void(ObjectType::*callback)(EventType &event));

    template<typename ObjectType, typename EventType>
    constexpr static EventType getEvent(void(ObjectType::*callback)(EventType &event));

    template<typename CallbackType, CallbackType callback>
    static void call(AObject &object, AEvent &event)
    {
        using ObjectType = typename std::remove_reference<decltype(getObject(callback))>::type;
        using EventType = decltype(getEvent(callback));
        (static_cast<ObjectType &>(object).*callback)(static_cast<EventType &>(event));
    }

public:
    CallbackMap callbacks;

    template<typename CallbackType, CallbackType callback>
    void registerEventCallback()
    {
        using EventType = decltype(getEvent(callback));
        callbacks.insert({ AMeta::getStaticTypeHash<EventType>(), &call<CallbackType, callback> });
    }

    template<typename CallbackType>
    void unregisterEventCallback()
    {
        using EventType = decltype(getEvent(CallbackType()));
        callbacks.erase(AMeta::getStaticTypeHash<EventType>());
    }

    void processEvent(AObject &object, AEvent &event)
    {
        auto it = callbacks.find(AMeta::getDynamicTypeHash(event));
        if (it == callbacks.end())
        {
            return;
        }
        it->second(object, event);
    }

};

#define ARegisterEventCallback(callback) eventListener.registerEventCallback<decltype(&std::remove_pointer<decltype(this)>::type::callback), &std::remove_pointer<decltype(this)>::type::callback>()
#define AUnregisterEventCallback(callback) eventListener.unregisterEventCallback<decltype(&std::remove_pointer<decltype(this)>::type::callback)>()

class AEventObserver
{
public:

    virtual ~AEventObserver() {}
    virtual void sendEvent(AEvent &event) = 0;

};

class AObject : public AEventObserver, public Serializable
{
protected:

    AEventListener eventListener;

public:

    virtual String getObjectDescription() const
    {
#if !AReleaseBuild
        return fmt::format("{}({})", (!name.empty() ? name : AMeta::getDynamicTypeName(*this)), fmt::ptr(this));
#else
        return fmt::format("{}({})", AMeta::getDynamicTypeName(*this), fmt::ptr(this));
#endif
    }

    void sendEvent(AEvent &event) override
    {
        eventListener.processEvent(*this, event);
    }
#if !AReleaseBuild
private:
    String name;
public:
    const String &getName() const { return name; }
#endif
    void setName(const String &name)
    {
        if constexpr(!AReleaseBuild)
        {
            this->name = name;
        }
    }
};

class AEventChannel : public AEventObserver
{

    template<typename ReturnType, typename ...Arguments>
    static std::tuple<Arguments...> GetFunctionArguments(ReturnType(*)(Arguments...));

    template<typename ObjectType, typename ReturnType, typename ...Arguments>
    static std::tuple<Arguments...> GetFunctionArguments(ReturnType(ObjectType::*)(Arguments...));

    template<typename ReturnType, typename ...Arguments>
    static ReturnType GetFunctionReturnType(ReturnType(*)(Arguments...));

    template<typename ObjectType, typename ReturnType, typename ...Arguments>
    static ReturnType GetFunctionReturnType(ReturnType(ObjectType::*)(Arguments...));

    template<typename ObjectType, typename ReturnType, typename ...Arguments>
    static auto ConvertToNonConstMethod(ReturnType(ObjectType::*)(Arguments...) const)->ReturnType(ObjectType::*)(Arguments...);

    template<typename Functor>
    struct Function;

    template<typename RetType, typename ...ArgumentTypes>
    struct Function<RetType(ArgumentTypes...)>
    {
        using ReturnType = RetType;
        using Arguments = std::tuple<ArgumentTypes...>;
        template<size_t Index>
		using Argument = typename std::tuple_element_t<Index, Arguments>;
    };

    template<typename Functor>
    struct Function
    {
        using ReturnType = decltype(GetFunctionReturnType(ConvertToNonConstMethod(&Functor::operator())));
        using Arguments = decltype(GetFunctionArguments(ConvertToNonConstMethod(&Functor::operator())));
        template<size_t Index>
        using Argument = typename std::tuple_element_t<Index, Arguments>;
    };
protected:
    Array<AEventObserver*> observers;
    Array<ADelegate<void(AEvent &event)>> delegates;

public:

#if AHasAsserts
    bool isRegisteredInObserever(AEventObserver &checkedObserver, AEventObserver &currentObserver) const
    {
        if (&checkedObserver == &currentObserver)
        {
            return true;
        }

        AEventChannel *channel = dynamic_cast<AEventChannel *>(&currentObserver);
        if (channel)
        {
            for (auto observer : channel->observers)
            {
                if (isRegisteredInObserever(checkedObserver, *observer))
                {
                    return true;
                }
            }
        }
        return false;
    }
#endif

    void registerObserver(AEventObserver &observer)
    {
        AAssert(!isRegisteredInObserever(*this, observer), "Channel was registered recursively");
        observers.push_back(&observer);
    }

    void unregisterObserver(AEventObserver &observer)
    {
        ArrayUtils::Remove(observers, &observer);
    }

    template<typename DelegateType>
    void registerDelegate(const DelegateType &delegate)
    {
        using EventType = typename Function<DelegateType>::template Argument<0>;
        delegates.push_back([delegate](AEvent &event)
        {
            if (AMeta::getDynamicTypeHash(event) == AMeta::getStaticTypeHash<EventType>())
            {
                delegate(static_cast<EventType &>(event));
            }
        });
    }

    //TODO: remove
    template<typename EventType, typename DelegateType>
    void registerDelegate(const DelegateType &delegate)
    {
        delegates.push_back([delegate](AEvent &event)
        {
            if (AMeta::getDynamicTypeHash(event) == AMeta::getStaticTypeHash<EventType>())
            {
                delegate(static_cast<EventType &>(event));
            }
        });
    }

    void sendEvent(AEvent &event) override
    {
        for (auto &observer : observers)
        {
            if (observer == nullptr)
            {
                continue;
            }

            if (&event.getSender() != observer)
            {
                observer->sendEvent(event);
            }
        }
        for (auto &delegate : delegates)
        {
            delegate(event);
        }
    }

    void sendAcceptableEvent(AAcceptableEvent &event)
    {
        for (auto &observer : observers)
        {
            if (observer == nullptr)
            {
                continue;
            }

            if (&event.getSender() != observer)
            {
                observer->sendEvent(event);
                if (event.isAccepted())
                {
                    return;
                }
            }
        }
        for (auto &delegate : delegates)
        {
            delegate(event);
            if (event.isAccepted())
            {
                return;
            }
        }
    }
};
