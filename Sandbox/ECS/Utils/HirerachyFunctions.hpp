#pragma once

#include "ECS/Utils/HirerachyComponent.hpp"

inline void RemoveFromParent(ECS::Entity &child)
{
    auto &c = ECS::g_Registry.get<ECS::HirerachyComponent>(child);

    if (c.Parent)
    {
        auto &p = ECS::g_Registry.get<ECS::HirerachyComponent>(c.Parent.value());
        //TODO: remove

        c.Parent.reset();
    }
}

inline void RemoveChildren(ECS::Entity &parent)
{
    auto &p = ECS::g_Registry.get<ECS::HirerachyComponent>(parent);
    p.Children.clear();
}

inline void Add(ECS::Entity &parent, ECS::Entity &child)
{
    RemoveFromParent(child);

    auto &p = ECS::g_Registry.get<ECS::HirerachyComponent>(parent);
    p.Children.push_back(child);

    auto &c = ECS::g_Registry.get<ECS::HirerachyComponent>(child);
    c.Parent = parent;
}

template<typename FunctorType>
inline void WalkFromParent(const ECS::Entity &parent, const FunctorType &functor)
{
    functor(parent);
    auto &p = ECS::g_Registry.get<ECS::HirerachyComponent>(parent);
    for (auto &child : p.Children)
    {
        WalkFromParent(child, functor);
    }
}

template<typename FunctorType>
inline void WalkFromChildren(const ECS::Entity &parent, const FunctorType &functor)
{
    auto &p = ECS::g_Registry.get<ECS::HirerachyComponent>(parent);
    for (auto &child : p.Children | ranges::views::reverse)
    {
        WalkFromChildren(child, functor);
    }
    functor(parent);
}
