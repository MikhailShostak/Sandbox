#pragma once

#include "Utils/HirerachyComponent.hpp"

inline void RemoveFromParent(ECS::Entity &child)
{
    auto &c = child.GetComponent<ECS::HirerachyComponent>();

    if (c.Parent)
    {
        auto &p = c.Parent->GetComponent<ECS::HirerachyComponent>();
        //TODO: remove

        c.Parent.reset();
    }
}

inline void RemoveChildren(ECS::Entity &parent)
{
    auto &p = parent.GetComponent<ECS::HirerachyComponent>();
    p.Children.clear();
}

inline void Add(ECS::Entity &parent, ECS::Entity &child)
{
    RemoveFromParent(child);

    auto &p = parent.GetComponent<ECS::HirerachyComponent>();
    p.Children.push_back(child);

    auto &c = child.GetComponent<ECS::HirerachyComponent>();
    c.Parent = parent;
}

template<typename FunctorType>
inline bool WalkFromParent(ECS::Entity &parent, const FunctorType &functor)
{
    if (functor(parent))
    {
        return true;
    }

    auto &p = parent.GetComponent<ECS::HirerachyComponent>();
    for (auto &child : p.Children)
    {
        if (WalkFromParent(child, functor))
        {
            return true;
        }
    }

    return false;
}

template<typename FunctorType>
inline bool WalkFromChildren(ECS::Entity &parent, const FunctorType &functor)
{
    auto &p = parent.GetComponent<ECS::HirerachyComponent>();
    for (auto &child : p.Children | ranges::views::reverse)
    {
        if (WalkFromChildren(child, functor))
        {
            return true;
        }
    }
    
    if (functor(parent))
    {
        return true;
    }

    return false;
}
