#pragma once

#include "AFactoryMap.h"
#include "AMemory.h"

#include "FunctionPointer.h"

class StateMachine;

class State
{
public:
    virtual ~State() {}
    virtual void onEnter(StateMachine &stateMachine) {}
    virtual void onExit(StateMachine &stateMachine) {}
};

class StateMachine : public AObject
{
    AFactoryMap<size_t, State> registeredStates;
    Array<::SharedReference<State>> currentStates;

public:

    template<typename StateType>
    void registerState(size_t identifier) { registeredStates.insert<StateType>(identifier); }

    //TODO
    //void unregisterState(size_t identifier) { stateFactory.remove(identifier); }

    void setState(size_t identifier)
    {
        for (auto it = currentStates.rbegin(); it != currentStates.rend(); ++it)
        {
            (*it)->onExit(*this);
        }
        currentStates.clear();

        pushState(identifier);
    }

    void pushState(size_t identifier)
    {
        ::SharedReference<State> state = registeredStates.createShared(identifier);
        currentStates.push_back(state);
        state->onEnter(*this);
    }

    void popState()
    {
        if (!currentStates.empty())
        {
            currentStates.back()->onExit(*this);
            currentStates.pop_back();
        }
    }
};

struct StaticState
{
    VoidFunctionPointer enter;
    VoidFunctionPointer exit;
};

struct StaticStackState
{
    VoidFunctionPointer create;
    VoidFunctionPointer destroy;
    VoidFunctionPointer enter;
    VoidFunctionPointer exit;
};

struct DynamicState
{
    VoidFunctionPointer update;
    VoidFunctionPointer enter;
    VoidFunctionPointer exit;
};

struct DynamicStackState
{
    VoidFunctionPointer create;
    VoidFunctionPointer destroy;
    VoidFunctionPointer update;
    VoidFunctionPointer enter;
    VoidFunctionPointer exit;
};

namespace Templates
{

template<typename StateType, const StateType states[], size_t size, typename _StatesEnumeration, _StatesEnumeration entryPoint, bool autoEnter = true>
class StateMachine
{
protected:
    StateType instance;
    _StatesEnumeration state = entryPoint;
public:
    constexpr static size_t Size = size;
    using StatesEnumeration = _StatesEnumeration;

    StateMachine()
    {
        instance = states[state];
        if constexpr (autoEnter)
        {
            enter();
        }
    }

    ~StateMachine()
    {
        if constexpr (autoEnter)
        {
            exit();
        }
    }

    void enter()
    {
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.create();
        }
        instance.enter();
    }

    void exit()
    {
        instance.exit();
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.destroy();
        }
    }

    StatesEnumeration getState() const
    {
        return state;
    }

    void setState(StatesEnumeration state)
    {
        exit();
        this->state = state;

        instance = states[state];
        enter();
    }
};

template<typename StateType, const StateType states[], size_t size, typename _StatesEnumeration, _StatesEnumeration entryPoint, bool autoEnter = true>
class StackBasedStateMachine : public StateMachine<StateType, states, size, _StatesEnumeration, entryPoint, autoEnter>
{
protected:
    Array<std::pair<_StatesEnumeration, StateType>> history;
public:
    using Super = StateMachine<StateType, states, size, _StatesEnumeration, entryPoint, autoEnter>;
    using Super::StatesEnumeration;
    using Super::instance;
    using Super::state;

    void pushState(StatesEnumeration state)
    {
        history.emplace_back(this->state, std::move(instance));
        history.back().second.exit();

        this->state = state;

        instance = states[state];
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.create();
        }
        instance.enter();
    }

    void popState()
    {
        instance.exit();
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.destroy();
        }
        state = history.back().first;
        instance = std::move(history.back().second);
        history.pop_back(); //TODO: add pop method to the array
        instance.enter();
    }

    void popStatesUntil(StatesEnumeration state)
    {
        auto it = std::find_if(history.rbegin(), history.rend(), [state](auto &&pair) { return pair.first == state; });
        if (it == history.rend())
        {
            return; //State is not reachable
        }

        instance.exit();
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.destroy();
        }
        for (auto i = history.rbegin(); i != it; ++i)
        {
            i->second.enter();
            i->second.exit();
            if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
            {
                i->second.destroy();
            }
        }

        this->state = it->first;
        instance = std::move(it->second);
        instance.enter();

        history.erase(std::next(it).base(), history.end());
    }

    void popStatesTo(StatesEnumeration state)
    {
        auto it = std::find_if(history.rbegin(), history.rend(), [state](auto &&pair) { return pair.first == state; });
        if (it == history.rend())
        {
            return; //State is not reachable
        }

        instance.exit();
        if constexpr (std::is_base_of<StaticStackState, StateType>::value || std::is_base_of<DynamicStackState, StateType>::value)
        {
            instance.destroy();
        }
        this->state = it->first;
        instance = std::move(it->second);
        instance.enter();

        history.erase(std::next(it).base(), history.end());
    }
};

template<typename StateMachineType>
class DynamicStateMachine : public StateMachineType
{
public:
    using Super = StateMachineType;
    using Super::StatesEnumeration;
    using Super::instance;
    using Super::state;
    void update()
    {
        instance.update();
    }
};

}

template<const StaticState states[], size_t size, typename StatesEnumeration, StatesEnumeration entryPoint, bool autoEnter = true>
using StaticStateMachine = Templates::StateMachine<StaticState, states, size, StatesEnumeration, entryPoint, autoEnter>;

template<const StaticStackState states[], size_t size, typename StatesEnumeration, StatesEnumeration entryPoint, bool autoEnter = true>
using StaticStackBasedStateMachine = Templates::StackBasedStateMachine<StaticStackState, states, size, StatesEnumeration, entryPoint, autoEnter>;

template<const DynamicState states[], size_t size, typename StatesEnumeration, StatesEnumeration entryPoint, bool autoEnter = true>
using DynamicStateMachine = Templates::DynamicStateMachine<Templates::StateMachine<DynamicState, states, size, StatesEnumeration, entryPoint, autoEnter>>;

template<const DynamicStackState states[], size_t size, typename StatesEnumeration, StatesEnumeration entryPoint, bool autoEnter = true>
using DynamicStackBasedStateMachine = Templates::DynamicStateMachine<Templates::StackBasedStateMachine<DynamicStackState, states, size, StatesEnumeration, entryPoint, autoEnter>>;

template<const StaticState states[], size_t size, size_t entryPoint = 0, bool autoEnter = true>
using VariantStaticStateMachine = StaticStateMachine<states, size, size_t, entryPoint, autoEnter>;

template<const StaticStackState states[], size_t size, size_t entryPoint = 0, bool autoEnter = true>
using VariantStaticStackBasedStateMachine = StaticStackBasedStateMachine<states, size, size_t, entryPoint, autoEnter>;

template<const DynamicState states[], size_t size, size_t entryPoint = 0, bool autoEnter = true>
using VariantDynamicStateMachine = DynamicStateMachine<states, size, size_t, entryPoint, autoEnter>;

template<const DynamicStackState states[], size_t size, size_t entryPoint = 0, bool autoEnter = true>
using VariantDynamicStackBasedStateMachine = DynamicStackBasedStateMachine<states, size, size_t, entryPoint, autoEnter>;
