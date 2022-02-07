#pragma once

#include <entt/entt.hpp>

namespace ECS
{

using Entity = entt::entity;

inline entt::registry g_Registry;

struct System
{
    Graphics::GraphicsContext *m_GraphicsContext = nullptr;
    Int2 m_Resolution;
    virtual ~System() {}

    virtual void OnLoad() {}
    virtual void OnUnload() {}
    virtual void OnUpdate() {}
};

inline Array<UniqueReference<System>> g_Systems;

template<typename Type>
inline Type *FindSystem()
{
    for (auto &s : g_Systems)
    {
        if (Type *system = DynamicCast<Type>(s.get()))
        {
            return system;
        }
    }

    return nullptr;
}

template<typename ...Components>
inline std::tuple<Entity, Components &...> CreateEntity(entt::registry &registry = ECS::g_Registry)
{
    const auto entity = registry.create();
    return { entity, registry.emplace<Components>(entity)... };
}

template<typename ...Components>
inline std::tuple<Components &...> CreateComponents(entt::registry &registry = ECS::g_Registry)
{
    const auto entity = registry.create();
    return { registry.emplace<Components>(entity)... };
}

}
